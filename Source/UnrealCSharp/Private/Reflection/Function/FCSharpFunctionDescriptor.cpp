#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/FReflectionRegistry.h"

FCSharpFunctionDescriptor::FCSharpFunctionDescriptor(UFunction* InFunction,
                                                     FCSharpFunctionRegister&& InFunctionRegister):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InFunction)),
	FunctionRegister(std::move(InFunctionRegister)),
	Method(FDomain::Parent_Class_Get_Method_From_Name(InFunction->GetOwnerClass(),InFunction->GetName(), PropertyDescriptors.Num()))
{
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

	const auto CSharpParams = FDomain::Array_New(FReflectionRegistry::Get().Get_Object_Class(), PropertyDescriptors.Num());

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

		FDomain::Array_Set(CSharpParams, Index, static_cast<MonoObject*>(Object));
	}

	const auto FoundMonoObject = FunctionRegister.GetOriginalFunctionFlags() & FUNC_Static
		                             ? nullptr
		                             : FCSharpEnvironment::GetEnvironment().GetObject(InContext);

	if (const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke_Array(
			Method, FoundMonoObject, CSharpParams);
		ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FDomain::Object_Unbox(ReturnValue))
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
					if (const auto UnBoxResultValue = FDomain::Object_Unbox(FDomain::Array_Get<MonoObject*>(CSharpParams, Index)))
					{
						OutPropertyDescriptor->Set(UnBoxResultValue, OutParams->PropAddr);
					}
				}
				else
				{
					OutPropertyDescriptor->Set(
						FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(
							FDomain::Array_Get<MonoObject*>(CSharpParams, Index)),
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

const TWeakObjectPtr<UFunction>& FCSharpFunctionDescriptor::GetOriginalFunction() const
{
	return FunctionRegister.GetOriginalFunction();
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
