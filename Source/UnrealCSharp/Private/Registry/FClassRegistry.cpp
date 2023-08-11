#include "Registry/FClassRegistry.h"
#include "Domain/FDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

FClassRegistry::FClassRegistry()
{
	Initialize();
}

FClassRegistry::~FClassRegistry()
{
	Deinitialize();
}

void FClassRegistry::Initialize()
{
}

void FClassRegistry::Deinitialize()
{
	for (auto& ClassDescriptorPair : ClassDescriptorMap)
	{
		delete ClassDescriptorPair.Value;

		ClassDescriptorPair.Value = nullptr;
	}

	ClassDescriptorMap.Empty();

	PropertyDescriptorMap.Empty();

	FunctionDescriptorMap.Empty();
}

FClassDescriptor* FClassRegistry::GetClassDescriptor(const UStruct* InStruct) const
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct);

	return FoundClassDescriptor != nullptr ? *FoundClassDescriptor : nullptr;
}

FClassDescriptor* FClassRegistry::GetClassDescriptor(const FName& InClassName) const
{
	const auto InClass = LoadObject<UStruct>(nullptr, *InClassName.ToString());

	return InClass != nullptr ? GetClassDescriptor(InClass) : nullptr;
}

FClassDescriptor* FClassRegistry::NewClassDescriptor(const FDomain* InDomain, UStruct* InStruct)
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct);

	if (FoundClassDescriptor != nullptr)
	{
		return *FoundClassDescriptor;
	}

	const auto FoundMonoClass = InDomain->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(InStruct),
		FUnrealCSharpFunctionLibrary::GetFullClass(InStruct));

	if (FoundMonoClass == nullptr)
	{
		return nullptr;
	}

	const auto ClassDescriptor = new FClassDescriptor(InStruct, FoundMonoClass);

	ClassDescriptorMap.Add(InStruct, ClassDescriptor);

	return ClassDescriptor;
}

void FClassRegistry::DeleteClassDescriptor(const UStruct* InStruct)
{
	if (const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct))
	{
		delete FoundClassDescriptor;

		ClassDescriptorMap.Remove(InStruct);
	}
}

FPropertyDescriptor* FClassRegistry::GetPropertyDescriptor(const FDomain* InDomain, const UStruct* InStruct,
                                                           MonoString* InPropertyName)
{
	if (const auto FoundPropertyDescriptor = PropertyDescriptorMap.Find(InPropertyName))
	{
		return *FoundPropertyDescriptor;
	}

	if (const auto FoundClassDescriptor = GetClassDescriptor(InStruct))
	{
		const auto PropertyName = FName(UTF8_TO_TCHAR(InDomain->String_To_UTF8(InPropertyName)));

		if (const auto FoundPropertyDescriptor = FoundClassDescriptor->GetPropertyDescriptor(PropertyName))
		{
			PropertyDescriptorMap.Add(InPropertyName, FoundPropertyDescriptor);

			return FoundPropertyDescriptor;
		}
	}

	return nullptr;
}

FFunctionDescriptor* FClassRegistry::GetFunctionDescriptor(const FDomain* InDomain, const UStruct* InStruct,
                                                           MonoString* InFunctionName)
{
	if (const auto FoundFunctionDescriptor = FunctionDescriptorMap.Find(InFunctionName))
	{
		return *FoundFunctionDescriptor;
	}

	if (const auto FoundClassDescriptor = GetClassDescriptor(InStruct))
	{
		const auto FunctionName = FName(UTF8_TO_TCHAR(InDomain->String_To_UTF8(InFunctionName)));

		if (const auto FoundFunctionDescriptor = FoundClassDescriptor->GetFunctionDescriptor(FunctionName))
		{
			FunctionDescriptorMap.Add(InFunctionName, FoundFunctionDescriptor);

			return FoundFunctionDescriptor;
		}
	}

	return nullptr;
}
