#include "Binding/Class/FBindingClassBuilder.h"
#include "Binding/FBinding.h"
#include "Binding/Class/FBindingClass.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/ClassMacro.h"

FBindingClassBuilder::FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace):
	Class(InClass),
	TypeInfo(nullptr),
	ImplementationNameSpace(InImplementationNameSpace)
{
}

#if WITH_PROPERTY_INFO
FBindingClassBuilder::FBindingClassBuilder(const FString& InClass, FTypeInfo* InTypeInfo,
                                           const FString& InImplementationNameSpace):
	Class(InClass),
	TypeInfo(InTypeInfo),
	ImplementationNameSpace(InImplementationNameSpace)
{
}
#endif

#if WITH_PROPERTY_INFO
FBindingClassBuilder& FBindingClassBuilder::Property(const FString& InName, const void* InGetMethod,
                                                     const void* InSetMethod, FTypeInfo* InTypeInfo)
#else
FBindingClassBuilder& FBindingClassBuilder::Property(const FString& InName, const void* InGetMethod,
													 const void* InSetMethod)
#endif
{
#if WITH_PROPERTY_INFO
	if (InTypeInfo != nullptr)
	{
		FBindingClass::GetClass(Class, COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace), TypeInfo)->
			BindingProperty(InName, InTypeInfo, InGetMethod, InSetMethod);
	}
#endif

	return Function(BINDING_PROPERTY_GET + InName, InGetMethod).Function(BINDING_PROPERTY_SET + InName, InSetMethod);
}

#if WITH_FUNCTION_INFO
FBindingClassBuilder& FBindingClassBuilder::Function(const FString& InName, const void* InMethod,
                                                     FFunctionInfo* InFunctionInfo)
#else
FBindingClassBuilder& FBindingClassBuilder::Function(const FString& InName, const void* InMethod)
#endif
{
#if WITH_FUNCTION_INFO
	if (InFunctionInfo != nullptr)
	{
		FBindingClass::GetClass(Class, COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace), TypeInfo)->
			BindingFunction(InName, InFunctionInfo);
	}
#endif

	Functions.Emplace(
		COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace), BINDING_CLASS_IMPLEMENTATION(Class)) +
		COMBINE_FUNCTION(BINDING_COMBINE_FUNCTION(Class, InName)), InMethod);

	return *this;
}

void FBindingClassBuilder::Register()
{
	for (const auto& Iterator : Functions)
	{
		FBinding::Get().RegisterBinding(Iterator.Key, Iterator.Value);
	}
}
