#include "Binding/Class/FBindingClass.h"

TMap<FString, FBindingClass> FBindingClass::Classes;

FBindingClass* FBindingClass::GetClass(const FString& InClass, const FString& InImplementationNameSpace,
                                       FTypeInfo* InTypeInfo)
{
	if (!Classes.Contains(InClass))
	{
		Classes.Add(InClass, {InImplementationNameSpace, InTypeInfo});
	}

	return Classes.Find(InClass);
}

const TMap<FString, FBindingClass>& FBindingClass::GetClasses()
{
	return Classes;
}

const FString& FBindingClass::GetImplementationNameSpace() const
{
	return ImplementationNameSpace;
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

void FBindingClass::BindingFunction(const FString& InName, FFunctionInfo* InTypeInfo)
{
	Functions.Emplace(
		InTypeInfo,
		InName
	);
}
