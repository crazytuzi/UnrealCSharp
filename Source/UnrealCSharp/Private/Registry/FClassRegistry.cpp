#include "Registry/FClassRegistry.h"
#include "Domain/FMonoDomain.h"
#include "Macro/NamespaceMacro.h"

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

FClassDescriptor* FClassRegistry::GetClassDescriptor(const UClass* InClass)
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InClass);

	return FoundClassDescriptor != nullptr ? *FoundClassDescriptor : nullptr;
}

FClassDescriptor* FClassRegistry::NewClassDescriptor(const FMonoDomain* InMonoDomain, UClass* InClass)
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InClass);

	if (FoundClassDescriptor != nullptr)
	{
		return *FoundClassDescriptor;
	}

	auto FoundMonoClass = InMonoDomain->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME), InClass->GetPrefixCPP() + InClass->GetName());

	if (FoundMonoClass == nullptr)
	{
		FoundMonoClass = InMonoDomain->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE), InClass->GetPrefixCPP() + InClass->GetName());
	}

	const auto ClassDescriptor = new FClassDescriptor(InClass, FoundMonoClass);

	ClassDescriptorMap.Add(InClass, ClassDescriptor);

	return ClassDescriptor;
}

void FClassRegistry::DeleteClassDescriptor(const UClass* InClass)
{
	if (const auto FoundClassDescriptor = ClassDescriptorMap.Find(InClass))
	{
		delete FoundClassDescriptor;

		ClassDescriptorMap.Remove(InClass);
	}
}
