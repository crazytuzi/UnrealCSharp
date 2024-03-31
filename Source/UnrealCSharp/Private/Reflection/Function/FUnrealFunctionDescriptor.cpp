#include "Reflection/Function/FUnrealFunctionDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FUnrealFunctionDescriptor::FUnrealFunctionDescriptor(UFunction* InFunction):
	Super(InFunction),
	BufferAllocator(FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InFunction))
{
}

MonoObject* FUnrealFunctionDescriptor::CallUnreal(UObject* InObject, MonoObject** OutValue, MonoArray* InValue)
{
	auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	auto ParamIndex = 0;

	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

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

			if (Params != nullptr)
			{
				BufferAllocator->Free(Params);
			}

			return ReturnValue;
		}
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), Params, nullptr, nullptr);
	}

	if (Params != nullptr)
	{
		BufferAllocator->Free(Params);
	}

	return nullptr;
}
