#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FCSharpFunctionDescriptor::FCSharpFunctionDescriptor(const FString& InName, UFunction* InFunction):
	Super(InFunction),
	Name(InName),
	OriginalFunctionFlags(EFunctionFlags::FUNC_None),
	OriginalNativeFuncPtr(nullptr)
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

			if (!OriginalScript.IsEmpty())
			{
				InCallCSharpFunction->Script.Empty();

				InCallCSharpFunction->Script = OriginalScript;
			}
			else
			{
				InCallCSharpFunction->Script.Empty();
			}

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

bool FCSharpFunctionDescriptor::CallCSharp(const FFrame& InStack)
{
	const auto InParams = InStack.Locals;

	const auto CSharpParams = FCSharpEnvironment::GetEnvironment().GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment().GetDomain()->Get_Object_Class(), PropertyDescriptors.Num());

	auto ReferenceParam = InStack.OutParms;

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
			PropertyAddress = PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams);
		}

		void* Object = nullptr;

		PropertyDescriptors[Index]->Get(PropertyAddress, &Object);

		ARRAY_SET(CSharpParams, MonoObject*, Index, static_cast<MonoObject*>(Object));
	}

	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(InStack.Object))
	{
		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
			InStack.Object->GetClass())->GetMonoClass())
		{
			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Parent_Class_Get_Method_From_Name(FoundMonoClass,
				                                  TCHAR_TO_UTF8(
					                                  *FUnrealCSharpFunctionLibrary::Encode(Name)),
				                                  PropertyDescriptors.Num()))
			{
				const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke_Array(
					FoundMonoMethod, FoundMonoObject, CSharpParams);

				if (ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
				{
					if (const auto ReturnParam =
						FindOutParmRec(InStack.OutParms, ReturnPropertyDescriptor->GetProperty()))
					{
						if (ReturnPropertyDescriptor->IsPrimitiveProperty())
						{
							if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
								Object_Unbox(ReturnValue))
							{
								ReturnPropertyDescriptor->Set(UnBoxResultValue, ReturnParam->PropAddr);
							}
						}
						else
						{
							ReturnPropertyDescriptor->Set(FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(ReturnValue), ReturnParam->PropAddr);
						}
					}
				}

				auto OutParam = InStack.OutParms;

				for (const auto& Index : OutPropertyIndexes)
				{
					if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
					{
						OutParam = FindOutParmRec(OutParam, OutPropertyDescriptor->GetProperty());

						if (OutParam != nullptr)
						{
							if (OutPropertyDescriptor->IsPrimitiveProperty())
							{
								if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
									Object_Unbox(ARRAY_GET(CSharpParams, MonoObject*, Index)))
								{
									OutPropertyDescriptor->Set(UnBoxResultValue, OutParam->PropAddr);
								}
							}
							else
							{
								OutPropertyDescriptor->Set(
									FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(ARRAY_GET(CSharpParams, MonoObject*, Index)), OutParam->PropAddr);
							}
						}
					}
				}
			}
		}
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
