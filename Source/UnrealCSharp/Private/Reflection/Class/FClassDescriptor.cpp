#include "Reflection/Class/FClassDescriptor.h"
#include "CoreMacro/PropertyMacro.h"
#include "Domain/Script/IScriptDomain.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/FReflectionRegistry.h"

FClassDescriptor::FClassDescriptor(UStruct* InStruct):
	Struct(InStruct)
{
	Initialize();
}

FClassDescriptor::~FClassDescriptor()
{
	Deinitialize();
}

void FClassDescriptor::Initialize()
{
	if (const auto FoundClass = Cast<UClass>(Struct))
	{
		FoundClass->ClearFunctionMapsCaches();
	}

	Class = FReflectionRegistry::Get().GetClass(Struct);

	Class->ConstructorClass();
}

void FClassDescriptor::Deinitialize()
{
	const auto FoundClass = Cast<UClass>(Struct);

	if (FoundClass != nullptr)
	{
		FoundClass->ClearFunctionMapsCaches();
	}

	if (Class != nullptr && IManagedHandleIsValid(Class->GetManagedClass()))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			uint32 Value{};

			ScriptDomain->SetFieldStaticValue(Class->GetManagedClass(),
			                                  FoundClass != nullptr
				                                  ? PROPERTY_STATIC_CLASS_SINGLETON_BACKING_FIELD
				                                  : PROPERTY_STATIC_STRUCT_SINGLETON_BACKING_FIELD,
			                                  &Value);
		}
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

FClassReflection* FClassDescriptor::GetClass() const
{
	return Class;
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
