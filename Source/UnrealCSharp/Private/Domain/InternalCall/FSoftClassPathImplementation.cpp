#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftClassPath
{
	FRegisterSoftClassPath()
	{
		TReflectionClassBuilder<FSoftClassPath>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FSoftClassPath, FSoftClassPath const&),
			             {"Other"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftClassPath, const FString&),
			             {"PathString"})
			.Constructor(BINDING_CONSTRUCTOR(FSoftClassPath, const UClass*),
			             {"InClass"})
			.Function("ResolveClass", BINDING_FUNCTION(&FSoftClassPath::ResolveClass))
			.Function("GetOrCreateIDForClass", BINDING_FUNCTION(&FSoftClassPath::GetOrCreateIDForClass),
			          {"InClass"})
			.Register();
	}
};

static FRegisterSoftClassPath RegisterSoftClassPath;
