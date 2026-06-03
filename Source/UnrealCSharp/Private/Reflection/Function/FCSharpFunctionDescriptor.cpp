#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/FReflectionRegistry.h"
#include "Macro/FunctionMacro.h"

FCSharpFunctionDescriptor::FCSharpFunctionDescriptor(UFunction* InFunction,
                                                     FCSharpFunctionRegister&& InFunctionRegister):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InFunction)),
	FunctionRegister(std::move(InFunctionRegister))
{
	if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InFunction->GetOwnerClass()))
	{
		Method = FoundClass->GetParentMethod(InFunction->HasAnyFunctionFlags(FUNC_Net)
			                                     ? FString::Printf(TEXT(
				                                     "%s%s"
			                                     ),
			                                                       *InFunction->GetName(),
			                                                       *FUNCTION_IMPLEMENTATION_SUFFIX
			                                     )
			                                     : InFunction->GetName(),
		                                     PropertyDescriptors.Num());
	}
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

	auto ReferenceParam = OutParams;

	Invoke(
		Method,
		FunctionRegister.GetOriginalFunctionFlags() & FUNC_Static
			? InvalidManagedHandle
			: FCSharpEnvironment::GetEnvironment().GetObject(InContext),
		[this, Params, &ReferenceParam](const int32 Index) -> void*
		{
			if (ReferencePropertyIndexes.Contains(Index))
			{
				if (const auto ReferencePropertyDescriptor = PropertyDescriptors[Index])
				{
					ReferenceParam = FindOutParmRec(ReferenceParam, ReferencePropertyDescriptor->GetProperty());

					if (ReferenceParam != nullptr)
					{
						return ReferenceParam->PropAddr;
					}
				}

				return nullptr;
			}

			return PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(Params);
		},
		RESULT_PARAM,
		[this, &OutParams](const FPropertyDescriptor* InPropertyDescriptor) -> void*
		{
			OutParams = FindOutParmRec(OutParams, InPropertyDescriptor->GetProperty());

			return OutParams != nullptr ? OutParams->PropAddr : nullptr;
		}
	);

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
