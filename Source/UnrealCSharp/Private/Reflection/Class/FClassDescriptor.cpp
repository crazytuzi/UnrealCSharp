#include "Reflection/Class/FClassDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FClassDescriptor::FClassDescriptor(UStruct* InStruct, MonoClass* InBindMonoClass):
	Struct(InStruct),
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
	if (const auto Class = Cast<UClass>(Struct))
	{
		Class->ClearFunctionMapsCaches();
	}

	FMonoDomain::Class_Constructor(BindMonoClass);
}

void FClassDescriptor::Deinitialize()
{
	if (const auto Class = Cast<UClass>(Struct))
	{
		Class->ClearFunctionMapsCaches();

		FDomain::StaticClassSingleton_Reset(BindMonoClass);
	}
	else if (Cast<UScriptStruct>(Struct))
	{
		FDomain::StaticStructSingleton_Reset(BindMonoClass);
	}

	for (const auto& FunctionHash : FunctionHashSet)
	{
		FCSharpEnvironment::GetEnvironment().RemoveFunctionDescriptor(FunctionHash);
	}

	FunctionHashSet.Empty();

	for (const auto& PropertyHash : PropertyHashSet)
	{
		FCSharpEnvironment::GetEnvironment().RemovePropertyDescriptor(PropertyHash);
	}

	PropertyHashSet.Empty();
}

MonoClass* FClassDescriptor::GetMonoClass() const
{
	return BindMonoClass;
}

FFunctionDescriptor* FClassDescriptor::GetFunctionDescriptor(const FString& InFunctionName)
{
	for (const auto FunctionHash : FunctionHashSet)
	{
		if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor<
			FCSharpFunctionDescriptor>(FunctionHash))
		{
			if (FunctionDescriptor->GetName() == InFunctionName)
			{
				return FunctionDescriptor;
			}
		}
	}

	return nullptr;
}

FPropertyDescriptor* FClassDescriptor::AddPropertyDescriptor(FProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto NewPropertyDescriptor = FPropertyDescriptor::Factory(InProperty);

		PropertyHashSet.Add(GetTypeHash(InProperty));

		return NewPropertyDescriptor;
	}

	return nullptr;
}

bool FClassDescriptor::HasFunctionDescriptor(const uint32 InFunctionHash) const
{
	return FunctionHashSet.Contains(InFunctionHash);
}
