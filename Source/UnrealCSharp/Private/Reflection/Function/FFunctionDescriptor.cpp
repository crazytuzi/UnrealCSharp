#include "Reflection/Function/FFunctionDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FFunctionDescriptor::FFunctionDescriptor(UFunction* InFunction):
	Function(InFunction),
	OriginalFunction(nullptr),
	ReturnPropertyDescriptor(nullptr),
	Params(nullptr)
{
	FFunctionDescriptor::Initialize();
}

FFunctionDescriptor::~FFunctionDescriptor()
{
	FFunctionDescriptor::Deinitialize();
}

void FFunctionDescriptor::Initialize()
{
	if (!Function.IsValid())
	{
		return;
	}

	const auto IsNativeClass = Function->GetOwnerClass()->IsNative();

	PropertyDescriptors.Reserve(Function->ReturnValueOffset != MAX_uint16
		                            ? (Function->NumParms > 0
			                               ? Function->NumParms - 1
			                               : 0)
		                            : Function->NumParms);

	for (TFieldIterator<FProperty> It(Function.Get()); It && (It->PropertyFlags & CPF_Parm); ++It)
	{
		if (const auto Property = *It)
		{
			auto PropertyDescriptor = FPropertyDescriptor::Factory(Property);

			if (Property->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				ReturnPropertyDescriptor = PropertyDescriptor;

				continue;
			}

			const auto Index = PropertyDescriptors.Add(PropertyDescriptor);

			if (Property->HasAnyPropertyFlags(CPF_OutParm) && !Property->HasAnyPropertyFlags(CPF_ConstParm))
			{
				if (IsNativeClass || Property->HasAnyPropertyFlags(CPF_ReferenceParm))
				{
					ReferencePropertyIndexes.Emplace(Index);
				}

				OutPropertyIndexes.Emplace(Index);
			}
		}
	}

	Params = Function->ParmsSize > 0 ? FMemory::Malloc(Function->ParmsSize, 16) : nullptr;
}

void FFunctionDescriptor::Deinitialize()
{
	for (auto& PropertyDescriptorPair : PropertyDescriptors)
	{
		delete PropertyDescriptorPair;

		PropertyDescriptorPair = nullptr;
	}

	PropertyDescriptors.Empty();

	if (ReturnPropertyDescriptor != nullptr)
	{
		delete ReturnPropertyDescriptor;

		ReturnPropertyDescriptor = nullptr;
	}

	OutPropertyIndexes.Empty();

	if (Params != nullptr)
	{
		FMemory::Free(Params);

		Params = nullptr;
	}
}

FName FFunctionDescriptor::GetFName() const
{
	return Function.IsValid() ? Function->GetFName() : NAME_None;
}

bool FFunctionDescriptor::CallCSharp(FFrame& Stack, void* const Z_Param__Result)
{
	const auto InParams = Stack.Locals;

	auto OutParams = Stack.OutParms;

	TArray<void*> CSharpParams;

	CSharpParams.Reserve(PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		if (PropertyDescriptors[Index]->IsPrimitiveProperty())
		{
			if (OutPropertyIndexes.Contains(Index))
			{
				OutParams = FindOutParmRec(OutParams, PropertyDescriptors[Index]->GetProperty());

				CSharpParams.Add(OutParams->PropAddr);
			}
			else
			{
				CSharpParams.Add(PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams));

				PropertyDescriptors[Index]->Get(PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams),
				                                CSharpParams[Index]);
			}
		}
		else
		{
			CSharpParams.AddZeroed();

			PropertyDescriptors[Index]->Get(PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams),
			                                &CSharpParams[Index]);
		}
	}

	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(Stack.Object))
	{
		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
			Stack.Object->GetClass())->GetMonoClass())
		{
			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Parent_Class_Get_Method_From_Name(FoundMonoClass, TCHAR_TO_UTF8(*Stack.Node->GetName()),
				                                  PropertyDescriptors.Num()))
			{
				const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke(
					FoundMonoMethod, FoundMonoObject, CSharpParams.GetData());

				if (ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
				{
					if (ReturnPropertyDescriptor->IsPrimitiveProperty())
					{
						if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
							Object_Unbox(ReturnValue))
						{
							ReturnPropertyDescriptor->Set(UnBoxResultValue, Z_Param__Result);
						}
					}
					else
					{
						ReturnPropertyDescriptor->Set(ReturnValue, Z_Param__Result);
					}
				}

				if (OutPropertyIndexes.Num() > 0)
				{
					OutParams = Stack.OutParms;

					for (const auto& Index : OutPropertyIndexes)
					{
						if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
						{
							if (!OutPropertyDescriptor->IsPrimitiveProperty())
							{
								OutParams = FindOutParmRec(OutParams, OutPropertyDescriptor->GetProperty());

								if (OutParams != nullptr)
								{
									OutPropertyDescriptor->Set(CSharpParams[Index], OutParams->PropAddr);
								}
							}
						}
					}
				}
			}
		}
	}

	CSharpParams.Empty();

	return true;
}

bool FFunctionDescriptor::CallUnreal(UObject* InObject, MonoObject** ReturnValue, MonoObject** OutValue,
                                     MonoArray* InValue)
{
	auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	auto ParamIndex = 0;

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		const auto& PropertyDescriptor = PropertyDescriptors[Index];

		PropertyDescriptor->InitializeValue_InContainer(Params);

		if (ReferencePropertyIndexes.Contains(Index) || !OutPropertyIndexes.Contains(Index))
		{
			if (PropertyDescriptor->IsPrimitiveProperty())
			{
				if (const auto UnBoxValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
					ARRAY_GET(InValue, MonoObject*, ParamIndex++)))
				{
					PropertyDescriptor->Set(UnBoxValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
				}
			}
			else
			{
				PropertyDescriptor->Set(
					ARRAY_GET(InValue, MonoObject*, ParamIndex++),
					PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
			}
		}
	}

	if (ReturnPropertyDescriptor != nullptr)
	{
		ReturnPropertyDescriptor->InitializeValue_InContainer(Params);
	}

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), Params);

		if (ReturnPropertyDescriptor != nullptr)
		{
			ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params),
			                              reinterpret_cast<void**>(ReturnValue));
		}

		if (OutPropertyIndexes.Num() > 0)
		{
			const auto MonoObjectArray = FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(),
			                                                    OutPropertyIndexes.Num());

			for (auto Index = 0; Index < OutPropertyIndexes.Num(); ++Index)
			{
				if (const auto OutPropertyDescriptor = PropertyDescriptors[OutPropertyIndexes[Index]])
				{
					MonoObject* Value = nullptr;

					OutPropertyDescriptor->Get(OutPropertyDescriptor->ContainerPtrToValuePtr<void>(Params),
					                           reinterpret_cast<void**>(&Value));

					ARRAY_SET(MonoObjectArray, MonoObject*, Index, Value);
				}
			}

			*OutValue = (MonoObject*)MonoObjectArray;
		}
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), Params, nullptr, nullptr);
	}

	return true;
}

FOutParmRec* FFunctionDescriptor::FindOutParmRec(FOutParmRec* OutParam, const FProperty* OutProperty)
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
