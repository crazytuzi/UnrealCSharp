#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "CoreMacro/BindingMacro.h"
#include "Macro/BindingMacro.h"
#include "Binding/Class/FBindingClassRegister.h"

class UNREALCSHARP_API FClassBuilder
{
public:
	explicit FClassBuilder(const TFunction<FString()>& InClassFunction,
	                       const FString& InImplementationNameSpace,
	                       const TFunction<bool()>& InIsProjectClassFunction,
	                       bool InIsReflectionClass,
	                       const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

	explicit FClassBuilder(const FString& InClass,
	                       const FString& InImplementationNameSpace,
	                       bool InIsProjectClass = false,
	                       bool InIsReflectionClass = false,
	                       const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

	template <typename T>
	auto Function(const FString& InName,
	              T InMethod
#if WITH_FUNCTION_INFO
	              , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction = {}
#endif
	) -> FClassBuilder&;

	template <typename T, typename U>
	auto Property(const FString& InName,
	              T InGetMethod,
	              U InSetMethod
#if WITH_PROPERTY_INFO
	              , const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {}
#endif
	) -> FClassBuilder&;

	FClassBuilder& Function(const FString& InName,
#if WITH_FUNCTION_INFO
	                        const TArray<TPair<void*, TFunction<FFunctionInfo*()>>>& InMethod
#else
	                        const TArray<void*>& InMethod
#endif
	);

	FClassBuilder& Function(const FString& InName,
	                        const FString& InImplementationName,
	                        const void* InMethod
#if WITH_FUNCTION_INFO
	                        , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction = {}
#endif
	);

protected:
	template <typename T>
	auto Function(const FString& InImplementationName, const TFunctionPointer<T>& InMethod);

private:
	FString GetFunctionImplementationName(const FString& InName, const FString& InImplementationName) const;

protected:
	FBindingClassRegister*& ClassRegister;

private:
	TArray<FString> Functions;
};

#include "FClassBuilder.inl"
