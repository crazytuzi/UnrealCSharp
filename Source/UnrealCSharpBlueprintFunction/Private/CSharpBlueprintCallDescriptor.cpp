#include "CSharpBlueprintCallDescriptor.h"

#include "Environment/FCSharpEnvironment.h"
#include "Log/UnrealCSharpLog.h"
#include "Reflection/FReflectionRegistry.h"
#include "UObject/FieldPath.h"
#include "UObject/SoftObjectPtr.h"

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
	while (InStack.Code != nullptr && *InStack.Code != EX_EndFunctionParms)
	{
		InStack.MostRecentPropertyAddress = nullptr;

		switch (*InStack.Code)
		{
		case EX_StructConst:
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

				break;
			}

		case EX_StringConst:
		case EX_UnicodeStringConst:
			{
				FString Temp;

				InStack.Step(InStack.Object, &Temp);

				break;
			}

		case EX_TextConst:
			{
				FText Temp;

				InStack.Step(InStack.Object, &Temp);

				break;
			}

		case EX_SoftObjectConst:
			{
				FSoftObjectPtr Temp;

				InStack.Step(InStack.Object, &Temp);

				break;
			}

		case EX_FieldPathConst:
			{
				FFieldPath Temp;

				InStack.Step(InStack.Object, &Temp);

				break;
			}

		case EX_IntConst:
		case EX_Int64Const:
		case EX_UInt64Const:
		case EX_FloatConst:
		case EX_DoubleConst:
		case EX_ByteConst:
		case EX_IntConstByte:
		case EX_IntZero:
		case EX_IntOne:
		case EX_True:
		case EX_False:
		case EX_NameConst:
		case EX_ObjectConst:
		case EX_NoObject:
		case EX_NoInterface:
		case EX_Self:
		case EX_SkipOffsetConst:
		case EX_PropertyConst:
		case EX_BitFieldConst:
		case EX_InstanceDelegate:
		case EX_RotationConst:
		case EX_VectorConst:
		case EX_Vector3fConst:
		case EX_TransformConst:
			{
				alignas(16) uint8 Scratch[128] = {};

				InStack.Step(InStack.Object, Scratch);

				break;
			}

		default:
			{
				InStack.Step(InStack.Object, nullptr);

				break;
			}
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
		       TEXT("CSharpBlueprintCall: argument count of %s does not match the C# signature, recompile the Blueprint (%s)"),
		       *FoundFunction->GetName(), *GetPathNameSafe(InStack.Node));
	}
	else if (const auto ManagedHandle = FCSharpEnvironment::GetEnvironment().Bind(InTarget);
		!IManagedHandleIsValid(ManagedHandle))
	{
		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpBlueprintCall: failed to bind %s to a C# object (%s)"),
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
			if (!DestructorLink->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				DestructorLink->DestroyValue_InContainer(Params);
			}
		}

		BufferAllocator->Free(Params);
	}
}

void FCSharpBlueprintCallDescriptor::CallWithParams(UObject* InTarget, void* InParams)
{
	if (Method == nullptr || !Function.IsValid())
	{
		return;
	}

	const auto ManagedHandle = FCSharpEnvironment::GetEnvironment().Bind(InTarget);

	if (!IManagedHandleIsValid(ManagedHandle))
	{
		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpBlueprintCall: failed to bind %s to a C# object (%s)"),
		       *GetPathNameSafe(InTarget), *Function->GetName());

		return;
	}

	Invoke(
		Method,
		ManagedHandle,
		[this, InParams](const int32 Index) -> void*
		{
			return InParams != nullptr ? PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams) : nullptr;
		},
		ReturnPropertyDescriptor != nullptr && InParams != nullptr
			? ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams)
			: nullptr,
		[InParams](const FPropertyDescriptor* InPropertyDescriptor) -> void*
		{
			return InParams != nullptr ? InPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams) : nullptr;
		}
	);
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

	if (!PostGarbageCollectHandle.IsValid())
	{
		PostGarbageCollectHandle = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(
			this, &FCSharpBlueprintCallCache::Prune);
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
		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpBlueprintCall: %s.%s (Kind=%d, ParamCount=%d) could not be resolved to a C# member"),
		       *InClass->GetName(), *InName.ToString(), static_cast<int32>(InKind), InParamCount);
	}

	return Descriptors.Add(Key, MoveTemp(Descriptor)).Get();
}

void FCSharpBlueprintCallCache::Reset()
{
	Descriptors.Empty();

	if (PostGarbageCollectHandle.IsValid())
	{
		FCoreUObjectDelegates::GetPostGarbageCollect().Remove(PostGarbageCollectHandle);

		PostGarbageCollectHandle.Reset();
	}
}

void FCSharpBlueprintCallCache::Prune()
{
	for (auto It = Descriptors.CreateIterator(); It; ++It)
	{
		if (!It.Key().Class.IsValid())
		{
			It.RemoveCurrent();
		}
	}
}
