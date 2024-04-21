#include "Binding/Class/FBindingClass.h"

TMap<FString, FBindingClass> FBindingClass::Classes;

FBindingClass::~FBindingClass()
{
	if (Subscript != nullptr)
	{
		delete Subscript;

		Subscript = nullptr;
	}
}

FBindingClass* FBindingClass::GetClass(const bool InIsReflection, const FString& InClass,
                                       const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo)
{
	if (!Classes.Contains(InClass))
	{
		Classes.Add(InClass, {InIsReflection, InClass, InImplementationNameSpace, InTypeInfo});
	}

	return Classes.Find(InClass);
}

const TMap<FString, FBindingClass>& FBindingClass::GetClasses()
{
	return Classes;
}

TSet<FString> FBindingClass::GetPropertyNames(const FString& InClass)
{
	TSet<FString> PropertyNames;

	if (const auto Class = Classes.Find(InClass))
	{
		for (const auto& Property : Class->Properties)
		{
			PropertyNames.Add(Property.GetPropertyName());
		}
	}

	return PropertyNames;
}

TSet<FString> FBindingClass::GetFunctionNames(const FString& InClass)
{
	TSet<FString> FunctionNames;

	if (const auto Class = Classes.Find(InClass))
	{
		for (const auto& Function : Class->Functions)
		{
			FunctionNames.Add(Function.GetFunctionName());
		}
	}

	return FunctionNames;
}

bool FBindingClass::IsReflection() const
{
	return bIsReflection;
}

const FString& FBindingClass::GetImplementationNameSpace() const
{
	return ImplementationNameSpace;
}

const FString& FBindingClass::GetBase() const
{
	return Base;
}

const FString& FBindingClass::GetClass() const
{
	return Class;
}

const FBindingTypeInfo& FBindingClass::GetTypeInfo() const
{
	return TypeInfo;
}

const FBindingSubscript* FBindingClass::GetSubscript() const
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

void FBindingClass::BindingSubscript(const FString& InName, const FString& InGetImplementationName,
                                     const FString& InSetImplementationName, FFunctionInfo* InTypeInfo)
{
	if (Subscript == nullptr)
	{
		Subscript = new FBindingSubscript(InTypeInfo,
		                                  InName,
		                                  InName,
		                                  InGetImplementationName,
		                                  InSetImplementationName);
	}
}

void FBindingClass::BindingProperty(const FString& InName, FTypeInfo* InTypeInfo,
                                    const void* InGetMethod, const void* InSetMethod)
{
	Properties.Emplace(
		InTypeInfo,
		InName,
		static_cast<EBindingPropertyAccess>(
			static_cast<int32>((InGetMethod != nullptr
				                    ? EBindingPropertyAccess::OnlyRead
				                    : EBindingPropertyAccess::None)) +
			static_cast<int32>(InSetMethod != nullptr
				                   ? EBindingPropertyAccess::OnlyWrite
				                   : EBindingPropertyAccess::None))
	);
}

void FBindingClass::BindingFunction(const FString& InName, const FString& InImplementationName,
                                    FFunctionInfo* InTypeInfo)
{
	Functions.Emplace(
		InTypeInfo,
		InName,
		InImplementationName
	);
}

void FBindingClass::Inheritance(const FString& InClass, const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo)
{
	Base = InClass;

	GetClass(IsReflection(), InClass, InImplementationNameSpace, InTypeInfo);
}
