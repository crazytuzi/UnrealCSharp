#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FCSharpFunctionDescriptor::FCSharpFunctionDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InFunction)),
	OriginalFunctionFlags(EFunctionFlags::FUNC_None),
	OriginalNativeFuncPtr(nullptr),
	Method(FCSharpEnvironment::GetEnvironment().GetDomain()->Parent_Class_Get_Method_From_Name(
		FCSharpEnvironment::GetEnvironment().GetClassDescriptor(InFunction->GetOwnerClass())->GetMonoClass(),
		TCHAR_TO_UTF8(
			InFunction->HasAnyFunctionFlags(FUNC_Net)
			? *FString::Printf(TEXT(
					"%s_Implementation"
				),
				*FUnrealCSharpFunctionLibrary::Encode(InFunction))

			: *FUnrealCSharpFunctionLibrary::Encode(InFunction)
		),
		PropertyDescriptors.Num()))
{
}

FCSharpFunctionDescriptor::~FCSharpFunctionDescriptor()
{
	FCSharpFunctionDescriptor::Deinitialize();
}

void FCSharpFunctionDescriptor::Deinitialize()
{
	const auto InOriginalFunction = OriginalFunction.Get(true);

	const auto InCallCSharpFunction = Function.Get(true);

	if (InOriginalFunction != nullptr && InCallCSharpFunction != nullptr)
	{
		UFunction* FunctionRemove;

		if (InOriginalFunction->GetOuter() == InCallCSharpFunction->GetOuter())
		{
			InCallCSharpFunction->FunctionFlags = OriginalFunctionFlags;

			InCallCSharpFunction->SetNativeFunc(OriginalNativeFuncPtr);

			FunctionRemove = InOriginalFunction;
		}
		else
		{
			FunctionRemove = InCallCSharpFunction;
		}

		if (FunctionRemove != nullptr)
		{
			if (const auto Class = Cast<UClass>(FunctionRemove->GetOuter()))
			{
				Class->RemoveFunctionFromFunctionMap(FunctionRemove);
			}

			if (FunctionRemove->IsRooted())
			{
				FunctionRemove->RemoveFromRoot();
			}
			else
			{
				FunctionRemove->MarkAsGarbage();
			}
		}
	}

	OriginalFunction = nullptr;
}

bool FCSharpFunctionDescriptor::CallCSharp(UObject* InContext, FFrame& InStack, RESULT_DECL)
{
	void* Params = InStack.Locals;

	FOutParmRec* NewOutParams{};

	if (InStack.Node != InStack.CurrentNativeFunction)
	{
		Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		if (Params != nullptr)
		{
			auto LastOutParam = &NewOutParams;

			for (auto Property = static_cast<FProperty*>(Function->ChildProperties);
			     *InStack.Code != EX_EndFunctionParms;
			     Property = static_cast<FProperty*>(Property->Next))
			{
				Property->InitializeValue_InContainer(Params);

				InStack.MostRecentPropertyAddress = nullptr;

				if (Property->HasAnyPropertyFlags(CPF_OutParm))
				{
					InStack.Step(InStack.Object, Property->ContainerPtrToValuePtr<uint8>(Params));

					if (LastOutParam != nullptr)
					{
						CA_SUPPRESS(6263)

						const auto OutParam = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));

						OutParam->PropAddr = InStack.MostRecentPropertyAddress != nullptr
							                     ? InStack.MostRecentPropertyAddress
							                     : Property->ContainerPtrToValuePtr<uint8>(Params);

						OutParam->Property = Property;

						if (*LastOutParam != nullptr)
						{
							(*LastOutParam)->NextOutParm = OutParam;

							LastOutParam = &(*LastOutParam)->NextOutParm;
						}
						else
						{
							*LastOutParam = OutParam;
						}
					}
				}
				else
				{
					InStack.Step(InStack.Object, Property->ContainerPtrToValuePtr<uint8>(Params));
				}
			}
		}

		if (InStack.Code != nullptr)
		{
			InStack.SkipCode(1);
		}
	}

	auto OutParams = NewOutParams != nullptr ? NewOutParams : InStack.OutParms;

	const auto CSharpParams = FCSharpEnvironment::GetEnvironment().GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment().GetDomain()->Get_Object_Class(), PropertyDescriptors.Num());

	auto ReferenceParam = OutParams;

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		void* PropertyAddress{};

		if (ReferencePropertyIndexes.Contains(Index))
		{
			if (const auto ReferencePropertyDescriptor = PropertyDescriptors[Index])
			{
				ReferenceParam = FindOutParmRec(ReferenceParam, ReferencePropertyDescriptor->GetProperty());

				if (ReferenceParam != nullptr)
				{
					PropertyAddress = ReferenceParam->PropAddr;
				}
			}
		}
		else
		{
			PropertyAddress = PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(Params);
		}

		void* Object = nullptr;

		PropertyDescriptors[Index]->Get<std::false_type>(PropertyAddress, &Object);

		ARRAY_SET(CSharpParams, MonoObject*, Index, static_cast<MonoObject*>(Object));
	}

	const auto FoundMonoObject = OriginalFunctionFlags & FUNC_Static
		                             ? nullptr
		                             : FCSharpEnvironment::GetEnvironment().GetObject(InContext);

	if (const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke_Array(
			Method, FoundMonoObject, CSharpParams);
		ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Object_Unbox(ReturnValue))
			{
				ReturnPropertyDescriptor->Set(UnBoxResultValue, RESULT_PARAM);
			}
		}
		else
		{
			ReturnPropertyDescriptor->Set(
				FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(ReturnValue),
				RESULT_PARAM);
		}
	}

	for (const auto& Index : OutPropertyIndexes)
	{
		if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
		{
			OutParams = FindOutParmRec(OutParams, OutPropertyDescriptor->GetProperty());

			if (OutParams != nullptr)
			{
				if (OutPropertyDescriptor->IsPrimitiveProperty())
				{
					if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
						Object_Unbox(ARRAY_GET(CSharpParams, MonoObject*, Index)))
					{
						OutPropertyDescriptor->Set(UnBoxResultValue, OutParams->PropAddr);
					}
				}
				else
				{
					OutPropertyDescriptor->Set(
						FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(
							ARRAY_GET(CSharpParams, MonoObject*, Index)),
						OutParams->PropAddr);
				}
			}
		}
	}

	if (Params != nullptr && Params != InStack.Locals)
	{
		for (auto DestructorLink = Function->DestructorLink;
		     DestructorLink != nullptr;
		     DestructorLink = DestructorLink->DestructorLinkNext)
		{
			if (!DestructorLink->HasAnyPropertyFlags(CPF_OutParm))
			{
				DestructorLink->DestroyValue_InContainer(Params);
			}
		}

		BufferAllocator->Free(Params);
	}

	return true;
}

FOutParmRec* FCSharpFunctionDescriptor::FindOutParmRec(FOutParmRec* OutParam, const FProperty* OutProperty)
{
	while (OutParam != nullptr)
	{
		if (OutParam->Property == OutProperty)
		{
			return OutParam;
		}

		OutParam = OutParam->NextOutParm;
	}

	return nullptr;
}
