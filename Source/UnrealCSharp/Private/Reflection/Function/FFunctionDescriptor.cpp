#include "Reflection/Function/FFunctionDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
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

	const auto IsNativeClass = Function->GetOuter()->IsNative();

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

	const auto CSharpParams = FCSharpEnvironment::GetEnvironment().GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment().GetDomain()->Get_Object_Class(), PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		void* Object = nullptr;

		PropertyDescriptors[Index]->Get(PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams),
		                                &Object);

		ARRAY_SET(CSharpParams, MonoObject*, Index, static_cast<MonoObject*>(Object));
	}

	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(Stack.Object))
	{
		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
			Stack.Object->GetClass())->GetMonoClass())
		{
			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Parent_Class_Get_Method_From_Name(FoundMonoClass,
				                                  TCHAR_TO_UTF8(
					                                  *FUnrealCSharpFunctionLibrary::Encode(Stack.Node->GetName())),
				                                  PropertyDescriptors.Num()))
			{
				const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke_Array(
					FoundMonoMethod, FoundMonoObject, CSharpParams);

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

				auto OutParams = Stack.OutParms;

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
									ARRAY_GET(CSharpParams, MonoObject*, Index), OutParams->PropAddr);
							}
						}
					}
				}
			}
		}
	}

	return true;
}

MonoObject* FFunctionDescriptor::CallUnreal(UObject* InObject, MonoObject** OutValue, MonoArray* InValue)
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

		if (!OutPropertyIndexes.IsEmpty())
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

		if (ReturnPropertyDescriptor != nullptr)
		{
			MonoObject* ReturnValue{};

			ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params),
			                              reinterpret_cast<void**>(&ReturnValue));

			return ReturnValue;
		}
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), Params, nullptr, nullptr);
	}

	return nullptr;
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
