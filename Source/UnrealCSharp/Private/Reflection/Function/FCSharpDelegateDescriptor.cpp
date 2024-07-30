#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FCSharpDelegateDescriptor::FCSharpDelegateDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPersistentBufferAllocator>(InFunction))
{
}

bool FCSharpDelegateDescriptor::CallDelegate(MonoObject* InDelegate, void* InParams)
{
	TArray<void*> CSharpParams;

	CSharpParams.Reserve(PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		if (PropertyDescriptors[Index]->IsPrimitiveProperty())
		{
			if (OutPropertyIndexes.Contains(Index))
			{
				CSharpParams.Add(static_cast<uint8*>(InParams) + PropertyDescriptors[Index]->GetSize());
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

	const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Delegate_Invoke(
		InDelegate, CSharpParams.GetData());

	if (ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
				ReturnValue))
			{
				ReturnPropertyDescriptor->Set(UnBoxResultValue,
				                              static_cast<uint8*>(InParams) + Function->ReturnValueOffset);
			}
		}
		else
		{
			ReturnPropertyDescriptor->Set(ReturnValue, static_cast<uint8*>(InParams) + Function->ReturnValueOffset);
		}
	}

	if (!OutPropertyIndexes.IsEmpty())
	{
		for (const auto& Index : OutPropertyIndexes)
		{
			if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
			{
				if (!OutPropertyDescriptor->IsPrimitiveProperty())
				{
					OutPropertyDescriptor->Set(CSharpParams[Index],
					                           static_cast<uint8*>(InParams) + OutPropertyDescriptor->GetSize());
				}
			}
		}
	}

	CSharpParams.Empty();

	return true;
}

MonoObject* FCSharpDelegateDescriptor::ProcessDelegate(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue,
                                                       MonoArray* InValue)
{
	auto ParamIndex = 0;

	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		const auto& PropertyDescriptor = PropertyDescriptors[Index];

		PropertyDescriptor->InitializeValue_InContainer(Params);

		if (!OutPropertyIndexes.Contains(Index))
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
					*static_cast<FGarbageCollectionHandle*>(
						FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
							ARRAY_GET(InValue, MonoObject*, ParamIndex++))),
					PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
			}
		}
	}

	if (ReturnPropertyDescriptor != nullptr)
	{
		ReturnPropertyDescriptor->InitializeValue_InContainer(Params);
	}

	InScriptDelegate->ProcessDelegate<UObject>(Params);

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
				                           reinterpret_cast<void**>(&Value), true);

				ARRAY_SET(MonoObjectArray, MonoObject*, Index, Value);
			}
		}

		*OutValue = (MonoObject*)MonoObjectArray;
	}

	if (ReturnPropertyDescriptor != nullptr)
	{
		MonoObject* ReturnValue{};

		ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params),
		                              reinterpret_cast<void**>(&ReturnValue), true);

		if (Params != nullptr)
		{
			BufferAllocator->Free(Params);
		}

		return ReturnValue;
	}

	if (Params != nullptr)
	{
		BufferAllocator->Free(Params);
	}

	return nullptr;
}

MonoObject* FCSharpDelegateDescriptor::ProcessMulticastDelegate(
	const FMulticastScriptDelegate* InMulticastScriptDelegate, MonoObject** OutValue, MonoArray* InValue)
{
	auto ParamIndex = 0;

	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		const auto& PropertyDescriptor = PropertyDescriptors[Index];

		PropertyDescriptor->InitializeValue_InContainer(Params);

		if (!OutPropertyIndexes.Contains(Index))
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
					*static_cast<FGarbageCollectionHandle*>(
						FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
							ARRAY_GET(InValue, MonoObject*, ParamIndex++))),
					PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
			}
		}
	}

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

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
				                           reinterpret_cast<void**>(&Value), true);

				ARRAY_SET(MonoObjectArray, MonoObject*, Index, Value);
			}
		}

		*OutValue = (MonoObject*)MonoObjectArray;
	}

	if (Params != nullptr)
	{
		BufferAllocator->Free(Params);
	}

	return nullptr;
}
