#include "Binding/Class/FBindingClassBuilder.h"
#include "Binding/FBinding.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/ClassMacro.h"

FBindingClassBuilder::FBindingClassBuilder(const FString& InClass, const FString& InNameSpace):
	Class(InClass),
	NameSpace(InNameSpace)
{
}

FBindingClassBuilder& FBindingClassBuilder::Property(const FString& InName, const void* InGetMethod,
                                                     const void* InSetMethod)
{
	return Function(BINDING_PROPERTY_GET + InName, InGetMethod).Function(BINDING_PROPERTY_SET + InName, InSetMethod);
}

FBindingClassBuilder& FBindingClassBuilder::Function(const FString& InName, const void* InMethod)
{
	Functions.Emplace(
		COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NameSpace), BINDING_CLASS_IMPLEMENTATION(Class)) +
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
