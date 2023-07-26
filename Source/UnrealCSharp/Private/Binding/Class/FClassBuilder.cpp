#include "Binding/Class/FClassBuilder.h"
#include "Binding/FBinding.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/ClassMacro.h"
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

#if WITH_PROPERTY_INFO
FClassBuilder& FClassBuilder::Property(const FString& InName, const void* InGetMethod,
                                       const void* InSetMethod, FTypeInfo* InTypeInfo)
#else
FClassBuilder& FClassBuilder::Property(const FString& InName, const void* InGetMethod,
													 const void* InSetMethod)
#endif
{
#if WITH_PROPERTY_INFO
	if (InTypeInfo != nullptr)
	{
		GetBindingClass()->BindingProperty(InName, InTypeInfo, InGetMethod, InSetMethod);
	}
#endif

	return Function(BINDING_PROPERTY_GET + InName, InGetMethod).Function(BINDING_PROPERTY_SET + InName, InSetMethod);
}

#if WITH_FUNCTION_INFO
FClassBuilder& FClassBuilder::Function(const FString& InName, const void* InMethod,
                                       FFunctionInfo* InFunctionInfo, const TArray<FString>& InParamNames)
#else
FClassBuilder& FClassBuilder::Function(const FString& InName, const void* InMethod, const TArray<FString>& InParamNames)
#endif
{
#if WITH_FUNCTION_INFO
	return Function(InName, GetFunctionImplementationName(InName), InMethod, InFunctionInfo, InParamNames);
#else
	return Function(InName, GetFunctionImplementationName(InName), InMethod);
#endif
}

#if WITH_FUNCTION_INFO
FClassBuilder& FClassBuilder::Function(const FString& InName, const TArray<TPair<void*, FFunctionInfo*>>& InMethod)
#else
FClassBuilder& FClassBuilder::Function(const FString& InName, const TArray<void*>& InMethod)
#endif
{
	for (auto i = 0; i < InMethod.Num(); ++i)
	{
#if WITH_EDITOR
		Function(InName, InMethod[i].Key, InMethod[i].Value);
#else
		Function(InName, InMethod[i]);
#endif
	}

	return *this;
}

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
