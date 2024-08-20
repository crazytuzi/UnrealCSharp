#pragma once

#include "Class/FBindingClass.h"
#include "Class/FBindingClassRegister.h"
#include "Enum/FBindingEnum.h"
#include "Enum/FBindingEnumRegister.h"

class UNREALCSHARPCORE_API FBinding
{
private:
	FBinding() = default;

public:
	static FBinding& Get();

	FBinding& Register();

	FBindingClassRegister*& Register(const TFunction<FString()>& InClassFunction,
	                                 const FString& InImplementationNameSpace,
	                                 const TFunction<bool()>& InIsProjectClassFunction,
	                                 bool InIsReflectionClass,
	                                 const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction);

	FBindingEnumRegister*& Register(const TFunction<FString()>& InEnumFunction,
	                                const FString& InUnderlyingType,
	                                bool InIsProjectEnum,
	                                const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

	const TArray<FBindingClass*>& GetClasses() const;

	const TArray<FBindingEnum*>& GetEnums() const;

	bool IsProjectClass(const FString& InClass) const;

	bool IsProjectEnum(const FString& InEnum) const;

private:
	bool bIsRegister;

	TArray<FBindingClass*> Classes;

	TArray<FBindingEnum*> Enums;

	TArray<FBindingClassRegister*> ClassRegisters;

	TArray<FBindingEnumRegister*> EnumRegisters;
};
