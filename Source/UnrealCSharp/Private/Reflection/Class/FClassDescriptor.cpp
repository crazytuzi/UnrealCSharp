#include "Reflection/Class/FClassDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FClassDescriptor::FClassDescriptor(UClass* InClass, MonoClass* InBindMonoClass):
	Class(InClass),
	BindMonoClass(InBindMonoClass)
{
	Initialize();
}

FClassDescriptor::~FClassDescriptor()
{
	Deinitialize();
}

void FClassDescriptor::Initialize()
{
}

void FClassDescriptor::Deinitialize()
{
	for (auto& FunctionDescriptorPair : FunctionDescriptorMap)
	{
		delete FunctionDescriptorPair.Value;

		FunctionDescriptorPair.Value = nullptr;
	}

	FunctionDescriptorMap.Empty();

	for (auto& PropertyDescriptorPair : PropertyDescriptorMap)
	{
		delete PropertyDescriptorPair.Value;

		PropertyDescriptorPair.Value = nullptr;
	}

	PropertyDescriptorMap.Empty();
}

MonoClass* FClassDescriptor::GetMonoClass() const
{
	return BindMonoClass;
}

FFunctionDescriptor* FClassDescriptor::GetFunctionDescriptor(const FName& InFunctionName)
{
	if (const auto FoundFunctionDescriptor = FunctionDescriptorMap.Find(InFunctionName))
	{
		return *FoundFunctionDescriptor;
	}

	while (Class != nullptr)
	{
		if (const auto FoundFunction = Class->FindFunctionByName(InFunctionName, EIncludeSuperFlag::ExcludeSuper))
		{
			const auto NewFunctionDescriptor = new FFunctionDescriptor(FoundFunction);

			FunctionDescriptorMap.Add(InFunctionName, NewFunctionDescriptor);

			return NewFunctionDescriptor;
		}

		Class = Class->GetSuperClass();
	}

	return nullptr;
}

FPropertyDescriptor* FClassDescriptor::GetPropertyDescriptor(const FName& InPropertyName) const
{
	if (const auto FoundFunctionDescriptor = PropertyDescriptorMap.Find(InPropertyName))
	{
		return *FoundFunctionDescriptor;
	}

	if (Class != nullptr)
	{
		if (const auto FoundClassDescriptor = FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(
			Class->GetSuperClass()))
		{
			return FoundClassDescriptor->GetPropertyDescriptor(InPropertyName);
		}
	}

	return nullptr;
}
