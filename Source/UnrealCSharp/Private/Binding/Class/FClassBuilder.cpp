﻿#include "Binding/Class/FClassBuilder.h"
#include "Binding/FBinding.h"
#include "Kismet/KismetStringLibrary.h"

FClassBuilder::FClassBuilder(const FString& InClass, const FString& InImplementationNameSpace):
	Class(InClass),
	TypeInfo(nullptr),
	ImplementationNameSpace(InImplementationNameSpace)
{
}

#if WITH_PROPERTY_INFO
FClassBuilder::FClassBuilder(const FString& InClass, const FString& InImplementationNameSpace,
                             const FString& InFullClass, FTypeInfo* InTypeInfo):
	Class(InClass),
	FullClass(InFullClass),
	TypeInfo(InTypeInfo),
	ImplementationNameSpace(InImplementationNameSpace)
{
}
#endif

void FClassBuilder::Register()
{
	for (const auto& Iterator : Functions)
	{
		FBinding::Get().RegisterBinding(Iterator.Key.GetFunctionImplementationName(), Iterator.Value);
	}
}

#if WITH_FUNCTION_INFO
FClassBuilder& FClassBuilder::Function(const FString& InName, const FString& InImplementationName,
                                       const void* InMethod, FFunctionInfo* InFunctionInfo,
                                       const TArray<FString>& InParamNames)
#else
FClassBuilder& FClassBuilder::Function(const FString& InName, const FString& InImplementationName,
                                       const void* InMethod, const TArray<FString>& InParamNames)
#endif
{
#if WITH_FUNCTION_INFO
	if (InFunctionInfo != nullptr)
	{
		GetBindingClass()->BindingFunction(InName, InImplementationName, InFunctionInfo, InParamNames);
	}
#endif

	Functions.Emplace(FBindingFunctionBase{
		                  InName,
		                  COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace),
		                                BINDING_CLASS_IMPLEMENTATION(Class)) +
		                  COMBINE_FUNCTION(BINDING_COMBINE_FUNCTION(Class, InImplementationName))
	                  }, InMethod);

	return *this;
}

bool FClassBuilder::IsReflection() const
{
	return false;
}

FBindingClass* FClassBuilder::GetBindingClass() const
{
	return FBindingClass::GetClass(IsReflection(),
	                               Class,
	                               FullClass,
	                               COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace),
	                               TypeInfo);
}

FString FClassBuilder::GetFunctionImplementationName(const FString& InName) const
{
	const auto Count = GetFunctionCount(InName);

	return FString::Printf(TEXT(
		"%s%s"),
	                       *InName,
	                       Count == 0 ? TEXT("") : *UKismetStringLibrary::Conv_IntToString(Count)
	);
}

int32 FClassBuilder::GetFunctionCount(const FString& InName) const
{
	auto Count = 0;

	for (const auto& Function : Functions)
	{
		if (Function.Key.GetFunctionName() == InName)
		{
			++Count;
		}
	}

	return Count;
}
