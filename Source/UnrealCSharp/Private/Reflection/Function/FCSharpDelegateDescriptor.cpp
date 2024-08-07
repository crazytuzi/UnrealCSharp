#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FCSharpDelegateDescriptor::FCSharpDelegateDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPersistentBufferAllocator>(InFunction))
{
}

bool FCSharpDelegateDescriptor::CallDelegate(const UObject* InObject, MonoMethod* InMethod, void* InParams)
{
	const auto CSharpParams = FCSharpEnvironment::GetEnvironment().GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment().GetDomain()->Get_Object_Class(), PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		if (const auto PropertyDescriptor = PropertyDescriptors[Index])
		{
			void* Object = nullptr;

			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(InParams), &Object, false);

			ARRAY_SET(CSharpParams, MonoObject*, Index, static_cast<MonoObject*>(Object));
		}
	}

	const auto FoundMonoObject = InObject != nullptr
		                             ? FCSharpEnvironment::GetEnvironment().GetObject(InObject)
		                             : (MonoObject*)InMethod;

	if (const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke_Array(
			InMethod, FoundMonoObject, CSharpParams);
		ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
				ReturnValue))
			{
				ReturnPropertyDescriptor->Set(UnBoxResultValue,
				                              ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
			}
		}
		else
		{
			ReturnPropertyDescriptor->Set(FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(ReturnValue),
			                              ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
		}
	}

	if (!OutPropertyIndexes.IsEmpty())
	{
		for (const auto& Index : OutPropertyIndexes)
		{
			if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
			{
				if (OutPropertyDescriptor->IsPrimitiveProperty())
				{
					if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
						Object_Unbox(ARRAY_GET(CSharpParams, MonoObject*, Index)))
					{
						OutPropertyDescriptor->Set(UnBoxResultValue,
						                           OutPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
					}
				}
				else
				{
					OutPropertyDescriptor->Set(
						FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(
							ARRAY_GET(CSharpParams, MonoObject*, Index)),
						OutPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
				}
			}
		}
	}

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
