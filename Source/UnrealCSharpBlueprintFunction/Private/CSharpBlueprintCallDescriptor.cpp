#include "CSharpBlueprintCallDescriptor.h"

#include "Environment/FCSharpEnvironment.h"
#include "Log/UnrealCSharpLog.h"
#include "Reflection/FReflectionRegistry.h"

FCSharpBlueprintCallDescriptor::FCSharpBlueprintCallDescriptor(const FCSharpBlueprintMemberInfo& InInfo,
                                                               UFunction* InSignature,
                                                               TUniquePtr<FMethodReflection>&& InAccessorMethod) :
	Super(InSignature, FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InSignature)),
	Signature(InSignature),
	SignatureHash(FCSharpBlueprintMemberLibrary::ComputeSignatureHash(InSignature)),
	Method(InInfo.Kind == ECSharpBlueprintMemberKind::Function ? InInfo.Method : InAccessorMethod.Get()),
	AccessorMethod(MoveTemp(InAccessorMethod))
{
	Signature->AddToRoot();
}

FCSharpBlueprintCallDescriptor::~FCSharpBlueprintCallDescriptor()
{
	Deinitialize();

	FCSharpBlueprintMemberLibrary::DestroySignature(Signature);

	Signature = nullptr;
}

UFunction* FCSharpBlueprintCallDescriptor::GetSignature() const
{
	return Signature;
}

uint32 FCSharpBlueprintCallDescriptor::GetSignatureHash() const
{
	return SignatureHash;
}

static FOutParmRec* FindOutParmRec(FOutParmRec* InOutParm, const FProperty* InProperty)
{
	while (InOutParm != nullptr)
	{
		if (InOutParm->Property == InProperty)
		{
			return InOutParm;
		}

		InOutParm = InOutParm->NextOutParm;
	}

	return nullptr;
}

void FCSharpBlueprintCallDescriptor::SkipParams(FFrame& InStack)
{
	// 变量项只写 MostRecentPropertyAddress；常量项会把值写进结果地址，给足够大的临时空间
	alignas(16) uint8 Scratch[256];

	while (InStack.Code != nullptr && *InStack.Code != EX_EndFunctionParms)
	{
		InStack.MostRecentPropertyAddress = nullptr;

		if (*InStack.Code == EX_StructConst)
		{
			const auto SavedCode = InStack.Code;

			++InStack.Code;

			const auto ScriptStruct = Cast<UScriptStruct>(InStack.ReadObject());

			const auto StructSize = InStack.ReadInt<int32>();

			InStack.Code = SavedCode;

			TArray<uint8, TAlignedHeapAllocator<16>> Buffer;

			Buffer.AddZeroed(FMath::Max(StructSize, 1));

			if (ScriptStruct != nullptr)
			{
				ScriptStruct->InitializeStruct(Buffer.GetData());
			}

			InStack.Step(InStack.Object, Buffer.GetData());

			if (ScriptStruct != nullptr)
			{
				ScriptStruct->DestroyStruct(Buffer.GetData());
			}
		}
		else
		{
			FMemory::Memzero(Scratch);

			InStack.Step(InStack.Object, Scratch);
		}
	}
}

void FCSharpBlueprintCallDescriptor::Call(UObject* InTarget, FFrame& InStack)
{
	const auto FoundFunction = Function.Get();

	if (FoundFunction == nullptr || InStack.Code == nullptr || Method == nullptr)
	{
		SkipParams(InStack);

		return;
	}

	void* Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	TArray<FOutParmRec> OutParmRecs;

	OutParmRecs.Reserve(OutPropertyIndexes.Num());

	FOutParmRec* OutParms = nullptr;

	auto LastOutParmLink = &OutParms;

	void* ReturnAddress = nullptr;

	auto bArgumentMismatch = false;

	for (TFieldIterator<FProperty> It(FoundFunction); It && (It->PropertyFlags & CPF_Parm); ++It)
	{
		const auto Property = *It;

		const auto bHasArgument = *InStack.Code != EX_EndFunctionParms;

		bArgumentMismatch |= !bHasArgument;

		InStack.MostRecentPropertyAddress = nullptr;

		if (Property->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			// 返回值项一定是调用方的局部变量，只取地址不拷贝
			if (bHasArgument)
			{
				InStack.StepCompiledIn<FProperty>(nullptr);

				ReturnAddress = InStack.MostRecentPropertyAddress;
			}

			continue;
		}

		const auto ParamAddress = Params != nullptr ? Property->ContainerPtrToValuePtr<void>(Params) : nullptr;

		if (ParamAddress != nullptr)
		{
			Property->InitializeValue(ParamAddress);
		}

		if (bHasArgument)
		{
			InStack.StepCompiledIn<FProperty>(ParamAddress);
		}

		if (Property->HasAnyPropertyFlags(CPF_OutParm))
		{
			auto& OutParmRec = OutParmRecs.AddDefaulted_GetRef();

			OutParmRec.Property = Property;

			OutParmRec.PropAddr = InStack.MostRecentPropertyAddress != nullptr
				                      ? InStack.MostRecentPropertyAddress
				                      : static_cast<uint8*>(ParamAddress);

			OutParmRec.NextOutParm = nullptr;

			*LastOutParmLink = &OutParmRec;

			LastOutParmLink = &OutParmRec.NextOutParm;
		}
	}

	if (*InStack.Code != EX_EndFunctionParms)
	{
		bArgumentMismatch = true;

		SkipParams(InStack);
	}

	if (bArgumentMismatch)
	{
		UE_LOG(LogUnrealCSharp, Error,
		       TEXT("CSharpBlueprintCall: %s 的蓝图调用参数个数与 C# 签名不一致，请重新编译蓝图 (%s)"),
		       *FoundFunction->GetName(), *GetPathNameSafe(InStack.Node));
	}
	else if (const auto ManagedHandle = FCSharpEnvironment::GetEnvironment().Bind(InTarget);
		!IManagedHandleIsValid(ManagedHandle))
	{
		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpBlueprintCall: %s 无法绑定到 C# 对象 (%s)"),
		       *GetPathNameSafe(InTarget), *FoundFunction->GetName());
	}
	else
	{
		auto ReferenceParam = OutParms;

		auto OutParam = OutParms;

		Invoke(
			Method,
			ManagedHandle,
			[this, Params, &ReferenceParam](const int32 Index) -> void*
			{
				if (ReferencePropertyIndexes.Contains(Index))
				{
					if (const auto PropertyDescriptor = PropertyDescriptors[Index])
					{
						ReferenceParam = FindOutParmRec(ReferenceParam, PropertyDescriptor->GetProperty());

						if (ReferenceParam != nullptr)
						{
							return ReferenceParam->PropAddr;
						}
					}

					return nullptr;
				}

				return Params != nullptr ? PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(Params) : nullptr;
			},
			ReturnAddress,
			[&OutParam](const FPropertyDescriptor* InPropertyDescriptor) -> void*
			{
				OutParam = FindOutParmRec(OutParam, InPropertyDescriptor->GetProperty());

				return OutParam != nullptr ? OutParam->PropAddr : nullptr;
			}
		);
	}

	if (Params != nullptr)
	{
		for (auto DestructorLink = FoundFunction->DestructorLink;
		     DestructorLink != nullptr;
		     DestructorLink = DestructorLink->DestructorLinkNext)
		{
			// 返回值槽位从未初始化，不能析构
			if (!DestructorLink->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				DestructorLink->DestroyValue_InContainer(Params);
			}
		}

		BufferAllocator->Free(Params);
	}
}

FCSharpBlueprintCallCache& FCSharpBlueprintCallCache::Get()
{
	static FCSharpBlueprintCallCache Cache;

	return Cache;
}

FCSharpBlueprintCallDescriptor* FCSharpBlueprintCallCache::Resolve(UClass* InClass,
                                                                   const ECSharpBlueprintMemberKind InKind,
                                                                   const FName& InName, const int32 InParamCount)
{
	if (InClass == nullptr)
	{
		return nullptr;
	}

	const FKey Key{InClass, InKind, InName, InParamCount};

	if (const auto Found = Descriptors.Find(Key))
	{
		return Found->Get();
	}

	TUniquePtr<FCSharpBlueprintCallDescriptor> Descriptor;

	if (FCSharpBlueprintMemberInfo Info;
		FCSharpBlueprintMemberLibrary::Resolve(InClass, InKind, InName, InParamCount, Info))
	{
		auto AccessorMethod = InKind != ECSharpBlueprintMemberKind::Function
			                      ? FCSharpBlueprintMemberLibrary::MakeAccessorMethod(Info)
			                      : nullptr;

		if (InKind == ECSharpBlueprintMemberKind::Function || AccessorMethod.IsValid())
		{
			if (const auto Signature = FCSharpBlueprintMemberLibrary::BuildSignature(
				Info, *FString::Printf(TEXT("CSharpBlueprintCall_%s_%s"), *InClass->GetName(), *InName.ToString())))
			{
				Descriptor = MakeUnique<FCSharpBlueprintCallDescriptor>(Info, Signature, MoveTemp(AccessorMethod));
			}
		}
	}

	if (!Descriptor.IsValid())
	{
		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpBlueprintCall: %s.%s (Kind=%d, ParamCount=%d) 无法解析为 C# 成员"),
		       *InClass->GetName(), *InName.ToString(), static_cast<int32>(InKind), InParamCount);
	}

	return Descriptors.Add(Key, MoveTemp(Descriptor)).Get();
}

void FCSharpBlueprintCallCache::Reset()
{
	Descriptors.Empty();
}
