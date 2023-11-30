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
}

void FClassDescriptor::Deinitialize()
{
	if (const auto Class = Cast<UClass>(Struct))
	{
		Class->ClearFunctionMapsCaches();
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

FFunctionDescriptor* FClassDescriptor::AddFunctionDescriptor(const FName& InFunctionName)
{
	if (auto InClass = Cast<UClass>(Struct))
	{
		while (InClass != nullptr)
		{
			if (const auto FoundFunction = InClass->FindFunctionByName(InFunctionName, EIncludeSuperFlag::ExcludeSuper))
			{
				const auto NewFunctionDescriptor = new FFunctionDescriptor(FoundFunction);

				FunctionHashSet.Add(GetTypeHash(FoundFunction));

				return NewFunctionDescriptor;
			}

			for (const auto& Interface : InClass->Interfaces)
			{
				if (const auto FoundFunction = Interface.Class->FindFunctionByName(
					InFunctionName, EIncludeSuperFlag::IncludeSuper))
				{
					const auto NewFunctionDescriptor = new FFunctionDescriptor(FoundFunction);

					FunctionHashSet.Add(GetTypeHash(FoundFunction));

					return NewFunctionDescriptor;
				}
			}

			InClass = InClass->GetSuperClass();
		}
	}

	return nullptr;
}

FFunctionDescriptor* FClassDescriptor::GetOrAddFunctionDescriptor(const FName& InFunctionName)
{
	for (const auto FunctionHash : FunctionHashSet)
	{
		if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor(FunctionHash))
		{
			if (FunctionDescriptor->GetFName() == InFunctionName)
			{
				return FunctionDescriptor;
			}
		}
	}

	return AddFunctionDescriptor(InFunctionName);
}

FPropertyDescriptor* FClassDescriptor::AddPropertyDescriptor(const FName& InPropertyName)
{
	if (const auto FoundProperty = Struct->FindPropertyByName(InPropertyName))
	{
		const auto NewPropertyDescriptor = FPropertyDescriptor::Factory(FoundProperty);

		PropertyHashSet.Add(GetTypeHash(FoundProperty));

		return NewPropertyDescriptor;
	}

	return nullptr;
}

bool FClassDescriptor::HasFunctionDescriptor(const uint32 InFunctionHash) const
{
	return FunctionHashSet.Contains(InFunctionHash);
}

bool FClassDescriptor::HasPropertyDescriptor(const FName& InPropertyName)
{
	for (const auto PropertyHash : PropertyHashSet)
	{
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
			GetOrAddPropertyDescriptor(PropertyHash))
		{
			if (PropertyDescriptor->GetFName() == InPropertyName)
			{
				return true;
			}
		}
	}

	return false;
}
