#include "Reflection/Class/FClassDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

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

FFunctionDescriptor* FClassDescriptor::AddFunctionDescriptor(const FString& InFunctionName)
{
	if (auto InClass = Cast<UClass>(Struct))
	{
		while (InClass != nullptr)
		{
			if (const auto FoundFunction = InClass->
				FindFunctionByName(*InFunctionName, EIncludeSuperFlag::ExcludeSuper))
			{
				const auto NewFunctionDescriptor = new FUnrealFunctionDescriptor(FoundFunction);

				FunctionHashSet.Add(GetTypeHash(FoundFunction));

				return NewFunctionDescriptor;
			}

			for (const auto& Interface : InClass->Interfaces)
			{
				if (const auto FoundFunction = Interface.Class->FindFunctionByName(
					*InFunctionName, EIncludeSuperFlag::IncludeSuper))
				{
					const auto NewFunctionDescriptor = new FUnrealFunctionDescriptor(FoundFunction);

					FunctionHashSet.Add(GetTypeHash(FoundFunction));

					return NewFunctionDescriptor;
				}
			}

			InClass = InClass->GetSuperClass();
		}
	}

	return nullptr;
}

FFunctionDescriptor* FClassDescriptor::GetOrAddFunctionDescriptor(const FString& InFunctionName)
{
	for (const auto FunctionHash : FunctionHashSet)
	{
		if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor(FunctionHash))
		{
			if (FunctionDescriptor->GetName() == InFunctionName)
			{
				return FunctionDescriptor;
			}
		}
	}

	return AddFunctionDescriptor(InFunctionName);
}

FPropertyDescriptor* FClassDescriptor::AddPropertyDescriptor(const FString& InPropertyName)
{
	if (const auto FoundProperty = Struct->FindPropertyByName(*InPropertyName))
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

bool FClassDescriptor::HasPropertyDescriptor(const FString& InPropertyName)
{
	for (const auto PropertyHash : PropertyHashSet)
	{
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
			GetOrAddPropertyDescriptor(PropertyHash))
		{
			if (PropertyDescriptor->GetName() == InPropertyName)
			{
				return true;
			}
		}
	}

	return false;
}
