#include "Binding/Class/FBindingClass.h"
#include "Binding/FBinding.h"

FBindingClass::FBindingClass(const FString& InBaseClass,
                             const FString& InClass,
                             const FString& InImplementationNameSpace,
                             const bool InIsProjectClass,
                             const bool InIsReflectionClass,
                             const FBindingTypeInfo& InTypeInfo,
                             const FBindingSubscript& InSubscript,
                             const TArray<FBindingProperty>& InProperties,
                             const TArray<FBindingFunction>& InFunctions,
                             const TArray<FBindingMethod>& InMethods):
	BaseClass(InBaseClass),
	Class(InClass),
	ImplementationNameSpace(InImplementationNameSpace),
	bIsProjectClass(InIsProjectClass),
	bIsReflectionClass(InIsReflectionClass),
	TypeInfo(InTypeInfo),
	Subscript(InSubscript),
	Properties(InProperties),
	Functions(InFunctions),
	Methods(InMethods)
{
}

TSet<FString> FBindingClass::GetPropertyNames(const FString& InClass)
{
	TSet<FString> PropertyNames;

	for (const auto& Class : FBinding::Get().Register().GetClasses())
	{
		if (Class->GetClass() == InClass)
		{
			for (const auto& Property : Class->GetProperties())
			{
				PropertyNames.Add(Property.GetPropertyName());
			}
		}
	}

	return PropertyNames;
}

TSet<FString> FBindingClass::GetFunctionNames(const FString& InClass)
{
	TSet<FString> FunctionNames;

	for (const auto& Class : FBinding::Get().Register().GetClasses())
	{
		if (Class->GetClass() == InClass)
		{
			for (const auto& Function : Class->GetFunctions())
			{
				FunctionNames.Add(Function.GetFunctionName());
			}
		}
	}

	return FunctionNames;
}

const FString& FBindingClass::GetBaseClass() const
{
	return BaseClass;
}

const FString& FBindingClass::GetClass() const
{
	return Class;
}

const FString& FBindingClass::GetImplementationNameSpace() const
{
	return ImplementationNameSpace;
}

bool FBindingClass::IsProjectClass() const
{
	return bIsProjectClass;
}

bool FBindingClass::IsReflectionClass() const
{
	return bIsReflectionClass;
}

bool FBindingClass::IsSet() const
{
	return TypeInfo.IsSet();
}

const FBindingTypeInfo& FBindingClass::GetTypeInfo() const
{
	return TypeInfo;
}

const FBindingSubscript& FBindingClass::GetSubscript() const
{
	return Subscript;
}

const TArray<FBindingProperty>& FBindingClass::GetProperties() const
{
	return Properties;
}

const TArray<FBindingFunction>& FBindingClass::GetFunctions() const
{
	return Functions;
}

const TArray<FBindingMethod>& FBindingClass::GetMethods() const
{
	return Methods;
}
