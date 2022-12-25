#include "Registry/FClassRegistry.h"
#include "Bridge/FTypeBridge.h"
#include "Domain/FMonoDomain.h"

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
}

FClassDescriptor* FClassRegistry::GetClassDescriptor(const UStruct* InStruct)
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct);

	return FoundClassDescriptor != nullptr ? *FoundClassDescriptor : nullptr;
}

FClassDescriptor* FClassRegistry::GetClassDescriptor(const FName& InClassName)
{
	const auto InClass = LoadObject<UStruct>(nullptr, *InClassName.ToString());

	return InClass != nullptr ? GetClassDescriptor(InClass) : nullptr;
}

FClassDescriptor* FClassRegistry::NewClassDescriptor(const FMonoDomain* InMonoDomain, UStruct* InStruct)
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct);

	if (FoundClassDescriptor != nullptr)
	{
		return *FoundClassDescriptor;
	}

	const auto FoundMonoClass = InMonoDomain->Class_From_Name(
		FTypeBridge::GetClassNameSpace(InStruct), FTypeBridge::GetFullClass(InStruct));

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
