#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"

bool FCSharpDelegateDescriptor::CallCSharp(MonoObject* InDelegateMonoObject, void* InParams)
{
	TArray<void*> CSharpParams;

	TArray<uint32> MallocMemoryIndexes;

	CSharpParams.Reserve(PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		if (PropertyDescriptors[Index]->IsPrimitiveProperty())
		{
			if (OutPropertyIndexes.Contains(Index))
			{
				CSharpParams.Add(static_cast<uint8*>(InParams) + PropertyDescriptors[Index]->GetProperty()->GetSize());
			}
			else
			{
				CSharpParams.Add(nullptr);

				PropertyDescriptors[Index]->Get(PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams),
				                                &CSharpParams[Index]);
			}
		}
		else
		{
			CSharpParams.Add(FMemory::Malloc(PropertyDescriptors[Index]->GetProperty()->GetSize()));

			PropertyDescriptors[Index]->Get(PropertyDescriptors[Index]->ContainerPtrToValuePtr<void>(InParams),
			                                &CSharpParams[Index]);

			MallocMemoryIndexes.Add(Index);
		}
	}


	const auto ReturnValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Delegate_Invoke(
		InDelegateMonoObject, CSharpParams.GetData(), nullptr);

	if (ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(
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

	if (OutPropertyIndexes.Num() > 0)
	{
		for (const auto& Index : OutPropertyIndexes)
		{
			if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
			{
				if (!OutPropertyDescriptor->IsPrimitiveProperty())
				{
					OutPropertyDescriptor->Set(CSharpParams[Index],
					                           static_cast<uint8*>(InParams) + OutPropertyDescriptor->GetProperty()->
					                           GetSize());
				}
			}
		}
	}

	for (const auto& Index : MallocMemoryIndexes)
	{
		FMemory::Free(CSharpParams[Index]);

		CSharpParams[Index] = nullptr;
	}

	MallocMemoryIndexes.Empty();

	CSharpParams.Empty();

	return true;
}

bool FCSharpDelegateDescriptor::CallUnreal(const FScriptDelegate* InScriptDelegate, MonoObject** ReturnValue,
                                           MonoObject** OutValue, MonoArray* InValue)
{
	void* Params = Function->ParmsSize > 0 ? FMemory::Malloc(Function->ParmsSize, 16) : nullptr;

	auto ParamIndex = 0;

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		const auto& PropertyDescriptor = PropertyDescriptors[Index];

		PropertyDescriptor->GetProperty()->InitializeValue_InContainer(Params);

		if (!OutPropertyIndexes.Contains(Index))
		{
			if (PropertyDescriptor->IsPrimitiveProperty())
			{
				if (const auto UnBoxValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(
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
		ReturnPropertyDescriptor->GetProperty()->InitializeValue_InContainer(Params);
	}

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	if (ReturnPropertyDescriptor != nullptr)
	{
		ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params), ReturnValue);
	}

	if (OutPropertyIndexes.Num() > 0)
	{
		const auto FoundObjectListClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_FUNCTION), CLASS_OBJECT_LIST);

		const auto FoundIntPtrClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_FUNCTION), CLASS_INT_PTR);

		const auto FoundAddMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
			FoundObjectListClass, FUNCTION_ADD, 1);

		const auto NewObjectList = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundObjectListClass);

		for (const auto Index : OutPropertyIndexes)
		{
			if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
			{
				auto Value = static_cast<void**>(FMemory_Alloca(sizeof(void*)));

				OutPropertyDescriptor->Get(OutPropertyDescriptor->ContainerPtrToValuePtr<void>(Params), Value);

				if (OutPropertyDescriptor->IsPrimitiveProperty())
				{
					auto NewIntPtr = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
						FoundIntPtrClass, 1, Value));

					Value = &NewIntPtr;
				}

				FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
					FoundAddMethod, NewObjectList, Value, nullptr);
			}
		}

		*OutValue = NewObjectList;
	}

	return true;
}
