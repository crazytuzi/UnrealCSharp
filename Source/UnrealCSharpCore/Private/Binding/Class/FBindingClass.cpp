#include "Binding/Class/FBindingClass.h"

TMap<FString, FBindingClass> FBindingClass::Classes;

FBindingClass* FBindingClass::GetClass(const bool InIsReflection, const FString& InClass,
                                       const FString& InFullClass, const FString& InImplementationNameSpace,
                                       FTypeInfo* InTypeInfo)
{
	if (!Classes.Contains(InClass))
	{
		Classes.Add(InClass, {InIsReflection, InClass, InFullClass, InImplementationNameSpace, InTypeInfo});
	}

	return Classes.Find(InClass);
}

const TMap<FString, FBindingClass>& FBindingClass::GetClasses()
{
	return Classes;
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

const FString& FBindingClass::GetFullClass() const
{
	return FullClass;
}

const FBindingTypeInfo& FBindingClass::GetTypeInfo() const
{
	return TypeInfo;
}

const TArray<FBindingProperty>& FBindingClass::GetProperties() const
{
	return Properties;
}

const TArray<FBindingFunction>& FBindingClass::GetFunctions() const
{
	return Functions;
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
                                    FFunctionInfo* InTypeInfo, const TArray<FString>& InParamNames)
{
	Functions.Emplace(
		InTypeInfo,
		InName,
		InImplementationName,
		InParamNames
	);
}

void FBindingClass::Inheritance(const FString& InClass, const FString& InFullClass,
                                const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo)
{
	Base = InFullClass;

	GetClass(IsReflection(), InClass, InFullClass, InImplementationNameSpace, InTypeInfo);
}
