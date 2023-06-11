#include "Binding/Class/FBindingClassBuilder.h"
#include "Binding/FBinding.h"
#include "Binding/FBindingClass.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/BindingMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/ClassMacro.h"

FBindingClassBuilder::FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace):
	Class(InClass),
	TypeInfo(nullptr),
	ImplementationNameSpace(InImplementationNameSpace)
{
}

FBindingClassBuilder::FBindingClassBuilder(const FString& InClass, FTypeInfo* InTypeInfo,
                                           const FString& InImplementationNameSpace):
	Class(InClass),
	TypeInfo(InTypeInfo),
	ImplementationNameSpace(InImplementationNameSpace)
{
}

FBindingClassBuilder& FBindingClassBuilder::Property(const FString& InName, const void* InGetMethod,
                                                     const void* InSetMethod, FTypeInfo* InTypeInfo)
{
	if (InTypeInfo != nullptr)
	{
		FBindingClass::GetClass(Class, COMBINE_NAMESPACE(NAMESPACE_ROOT, ImplementationNameSpace), TypeInfo)->
			BindingProperty(InName, InTypeInfo, InGetMethod, InSetMethod);
	}

	return Function(BINDING_PROPERTY_GET + InName, InGetMethod).Function(BINDING_PROPERTY_SET + InName, InSetMethod);
}

FBindingClassBuilder& FBindingClassBuilder::Function(const FString& InName, const void* InMethod)
{
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
