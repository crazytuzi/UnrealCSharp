#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "CoreMacro/BindingMacro.h"
#include "Macro/BindingMacro.h"
#include "Binding/Class/FBindingClass.h"
#include "Binding/Function/FBindingFunctionBase.inl"
#include "Binding/Function/EFunctionInteract.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"

class UNREALCSHARP_API FClassBuilder
{
public:
	explicit FClassBuilder(const FString& InClass, const FString& InImplementationNameSpace);

#if WITH_PROPERTY_INFO
	explicit FClassBuilder(const FString& InClass, const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo);
#endif

	virtual ~FClassBuilder() = default;

	template <typename T>
#if WITH_FUNCTION_INFO
	FClassBuilder& Function(const FString& InName, T InMethod,
	                        FFunctionInfo* InFunctionInfo = nullptr, const TArray<FString>& InParamNames = {},
	                        const EFunctionInteract InFunctionInteract = EFunctionInteract::None);
#else
	FClassBuilder& Function(const FString& InName, T InMethod, const TArray<FString>& InParamNames = {},
	                        const EFunctionInteract InFunctionInteract = EFunctionInteract::None);
#endif

	template <typename T, typename U>
#if WITH_PROPERTY_INFO
	FClassBuilder& Property(const FString& InName, T InGetMethod,
	                        U InSetMethod, FTypeInfo* InTypeInfo = nullptr);
#else
	FClassBuilder& Property(const FString& InName, T InGetMethod, U InSetMethod);
#endif

#if WITH_FUNCTION_INFO
	FClassBuilder& Function(const FString& InName, const TArray<TPair<void*, FFunctionInfo*>>& InMethod);
#else
	FClassBuilder& Function(const FString& InName, const TArray<void*>& InMethod);
#endif

#if WITH_FUNCTION_INFO
	FClassBuilder& Function(const FString& InName, const FString& InImplementationName,
	                        const void* InMethod, FFunctionInfo* InFunctionInfo = nullptr,
	                        const TArray<FString>& InParamNames = {},
	                        const EFunctionInteract InFunctionInteract = EFunctionInteract::None);
#else
	FClassBuilder& Function(const FString& InName, const FString& InImplementationName,
	                        const void* InMethod, const TArray<FString>& InParamNames = {},
	                        const EFunctionInteract InFunctionInteract = EFunctionInteract::None);
#endif

	void Register();

protected:
	template <typename T>
	void Function(const FString& InName, const FString& InImplementationName, const TFunctionPointer<T>& InMethod)
	{
		Functions.Emplace(FBindingFunctionBase{
			                  InName,
			                  COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace),
			                                BINDING_CLASS_IMPLEMENTATION(Class)) +
			                  COMBINE_FUNCTION(BINDING_COMBINE_FUNCTION(Class, InImplementationName))
		                  }, InMethod.Value.Pointer);
	}

	virtual bool IsReflection() const;

	FBindingClass* GetBindingClass() const;

private:
	FString GetFunctionImplementationName(const FString& InName, const FString& InImplementationName) const;

	int32 GetFunctionCount(const FString& InName) const;

private:
	FString Class;

	FTypeInfo* TypeInfo;

	FString ImplementationNameSpace;

	TMap<FBindingFunctionBase, const void*> Functions;
};

template <typename T>
#if WITH_FUNCTION_INFO
FClassBuilder& FClassBuilder::Function(const FString& InName, T InMethod,
                                       FFunctionInfo* InFunctionInfo, const TArray<FString>& InParamNames,
                                       const EFunctionInteract InFunctionInteract)
#else
FClassBuilder& FClassBuilder::Function(const FString& InName, T InMethod, const TArray<FString>& InParamNames,
                                       const EFunctionInteract InFunctionInteract)
#endif
{
	auto FunctionPointer = TFunctionPointer<decltype(InMethod)>(InMethod);

#if WITH_FUNCTION_INFO
	return Function(InName,
	                InName,
	                FunctionPointer.Value.Pointer,
	                InFunctionInfo,
	                InParamNames,
	                InFunctionInteract);
#else
	return Function(InName,
		InName,
		FunctionPointer.Value.Pointer,
		InParamNames,
		InFunctionInteract);
#endif
}

template <typename T, typename U>
#if WITH_PROPERTY_INFO
FClassBuilder& FClassBuilder::Property(const FString& InName, T InGetMethod,
                                       U InSetMethod, FTypeInfo* InTypeInfo)
#else
FClassBuilder& FClassBuilder::Property(const FString& InName, T InGetMethod, U InSetMethod)
#endif
{
	auto GetFunctionPointer = TFunctionPointer<decltype(InGetMethod)>(InGetMethod);

	auto SetFunctionPointer = TFunctionPointer<decltype(InSetMethod)>(InSetMethod);

#if WITH_PROPERTY_INFO
	if (InTypeInfo != nullptr)
	{
		GetBindingClass()->BindingProperty(InName,
		                                   InTypeInfo,
		                                   GetFunctionPointer.Value.Pointer,
		                                   SetFunctionPointer.Value.Pointer
		);
	}
#endif

	return Function(BINDING_PROPERTY_GET + InName, GetFunctionPointer.Value.Pointer).
		Function(BINDING_PROPERTY_SET + InName, SetFunctionPointer.Value.Pointer);
}
