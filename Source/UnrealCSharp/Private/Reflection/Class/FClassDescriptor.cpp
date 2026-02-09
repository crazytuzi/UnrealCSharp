#include "Reflection/Class/FClassDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/FReflectionRegistry.h"
#include "Template/TGetArrayLength.inl"

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
	if (const auto Class = Cast<UClass>(Struct))
	{
		Class->ClearFunctionMapsCaches();
	}
	
	ClassReflection = FReflectionRegistry::Get().GetClassReflection(Struct);
	
	FMonoDomain::Class_Constructor(ClassReflection->GetClass());
}

void FClassDescriptor::Deinitialize()
{
	if (const auto Class = Cast<UClass>(Struct))
	{
		Class->ClearFunctionMapsCaches();
		
		ClassReflection->Property_Set_Value(PROPERTY_STATIC_CLASS_SINGLETON, nullptr, {nullptr}, nullptr);
	}
	else
	{
		ClassReflection->Property_Set_Value(PROPERTY_STATIC_STRUCT_SINGLETON, nullptr, {nullptr}, nullptr);
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
	
	// if (ClassReflection != nullptr)
	// {
	// 	delete ClassReflection;
	// }
	// @TOOD
}

MonoClass* FClassDescriptor::GetMonoClass() const
{
	return ClassReflection != nullptr ? ClassReflection->GetClass() : nullptr;
}

MonoVTable* FClassDescriptor::GetVTable() const
{
	return ClassReflection != nullptr ? ClassReflection->GetVTable() : nullptr;
}

const TMap<FString, FPropertyReflection*>& FClassDescriptor::GetProperties() const
{
	static TMap<FString, FPropertyReflection*> Default;
	
	return ClassReflection != nullptr ? ClassReflection->GetProperties() : Default;
}

const TMap<FString, FFieldReflection*>& FClassDescriptor::GetField() const
{
	static TMap<FString, FFieldReflection*> Default;
	
	return ClassReflection != nullptr ? ClassReflection->GetFields() : Default;
}

const TMap<TPair<FString,int32>, FMethodReflection*>& FClassDescriptor::GetMethods() const
{
	static TMap<TPair<FString, int32>, FMethodReflection*> Default;
	
	return ClassReflection != nullptr ? ClassReflection->GetMethods() : Default;
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
