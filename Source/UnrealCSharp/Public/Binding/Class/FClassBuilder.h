#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "Macro/BindingMacro.h"
#include "Binding/Class/FBindingClass.h"
#include "Binding/Function/FBindingFunctionBase.inl"

class UNREALCSHARP_API FClassBuilder
{
public:
	explicit FClassBuilder(const FString& InClass, const FString& InImplementationNameSpace);

#if WITH_PROPERTY_INFO
	explicit FClassBuilder(const FString& InClass, const FString& InImplementationNameSpace,
	                       const FString& InFullClass, FTypeInfo* InTypeInfo);
#endif

	virtual ~FClassBuilder() = default;

	template <typename T>
	struct TFunctionPointer
	{
		explicit TFunctionPointer(T InFunction)
		{
			Value.Function = InFunction;
		}

		union
		{
			T Function;

			void* Pointer;
		} Value;
	};

	template <typename T>
#if WITH_FUNCTION_INFO
	FClassBuilder& Function(const FString& InName, T InMethod,
	                        FFunctionInfo* InFunctionInfo = nullptr, const TArray<FString>& InParamNames = {});
#else
	FClassBuilder& Function(const FString& InName, T InMethod, const TArray<FString>& InParamNames = {});
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

	void Register();

protected:
#if WITH_FUNCTION_INFO
	FClassBuilder& Function(const FString& InName, const FString& InImplementationName,
	                        const void* InMethod, FFunctionInfo* InFunctionInfo = nullptr,
	                        const TArray<FString>& InParamNames = {});
#else
	FClassBuilder& Function(const FString& InName, const FString& InImplementationName,
	                               const void* InMethod, const TArray<FString>& InParamNames = {});
#endif

	virtual bool IsReflection() const;

	FBindingClass* GetBindingClass() const;

private:
	FString GetFunctionImplementationName(const FString& InName) const;

	int32 GetFunctionCount(const FString& InName) const;

private:
	FString Class;

	FString FullClass;

	FTypeInfo* TypeInfo;

	FString ImplementationNameSpace;

	TMap<FBindingFunctionBase, const void*> Functions;
};

template <typename T>
#if WITH_FUNCTION_INFO
FClassBuilder& FClassBuilder::Function(const FString& InName, T InMethod,
                                       FFunctionInfo* InFunctionInfo, const TArray<FString>& InParamNames)
#else
FClassBuilder& FClassBuilder::Function(const FString& InName, T InMethod, const TArray<FString>& InParamNames)
#endif
{
	auto FunctionPointer = TFunctionPointer(InMethod);

#if WITH_FUNCTION_INFO
	return Function(InName,
	                GetFunctionImplementationName(InName),
	                FunctionPointer.Value.Pointer,
	                InFunctionInfo,
	                InParamNames);
#else
	return Function(InName,
		GetFunctionImplementationName(InName),
		FunctionPointer.Value.Pointer,
		InParamNames);
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
	auto GetFunctionPointer = TFunctionPointer(InGetMethod);

	auto SetFunctionPointer = TFunctionPointer(InSetMethod);

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
