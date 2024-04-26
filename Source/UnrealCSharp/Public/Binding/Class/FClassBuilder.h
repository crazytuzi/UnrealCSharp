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
	                       const TFunction<bool()>& InIsEngineClassFunction,
	                       bool InIsReflectionClass,
	                       const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

	explicit FClassBuilder(const FString& InClass,
	                       const FString& InImplementationNameSpace,
	                       bool InIsEngineClass = false,
	                       bool InIsReflectionClass = false,
	                       const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

	template <typename T>
	FClassBuilder& Function(const FString& InName,
	                        T InMethod
#if WITH_FUNCTION_INFO
	                        , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction = {}
#endif
	);

	template <typename T, typename U>
	FClassBuilder& Property(const FString& InName,
	                        T InGetMethod,
	                        U InSetMethod
#if WITH_PROPERTY_INFO
	                        , const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {}
#endif
	);

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
	void Function(const FString& InImplementationName, const TFunctionPointer<T>& InMethod)
	{
		ClassRegister->BindingMethod(InImplementationName, InMethod.Value.Pointer);
	}

private:
	FString GetFunctionImplementationName(const FString& InName, const FString& InImplementationName) const;

protected:
	FBindingClassRegister*& ClassRegister;

private:
	TArray<FString> Functions;
};

template <typename T>
FClassBuilder& FClassBuilder::Function(const FString& InName,
                                       T InMethod
#if WITH_FUNCTION_INFO
                                       , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction
#endif
)
{
	auto FunctionPointer = TFunctionPointer<decltype(InMethod)>(InMethod);

	return Function(InName,
	                InName,
	                FunctionPointer.Value.Pointer
#if WITH_FUNCTION_INFO
	                , InFunctionInfoFunction
#endif
	);
}

template <typename T, typename U>
FClassBuilder& FClassBuilder::Property(const FString& InName,
                                       T InGetMethod,
                                       U InSetMethod
#if WITH_PROPERTY_INFO
                                       , const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction
#endif
)
{
	auto GetFunctionPointer = TFunctionPointer<decltype(InGetMethod)>(InGetMethod);

	auto SetFunctionPointer = TFunctionPointer<decltype(InSetMethod)>(InSetMethod);

#if WITH_PROPERTY_INFO
	if (InTypeInfoFunction.IsSet())
	{
		ClassRegister->BindingProperty(InName,
		                               GetFunctionPointer.Value.Pointer,
		                               SetFunctionPointer.Value.Pointer,
		                               InTypeInfoFunction
		);
	}
#endif

	return Function(BINDING_PROPERTY_GET + InName, GetFunctionPointer.Value.Pointer).
		Function(BINDING_PROPERTY_SET + InName, SetFunctionPointer.Value.Pointer);
}
