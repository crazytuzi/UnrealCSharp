#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterSoftClassPath
	{
		FRegisterSoftClassPath()
		{
			TBindingClassBuilder<FSoftClassPath>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FSoftClassPath, FSoftClassPath const&),
				             TArray<FString>{"Other", "x"})
				.Constructor(BINDING_CONSTRUCTOR(FSoftClassPath, const FString&),
				             TArray<FString>{"PathString"})
				.Constructor(BINDING_CONSTRUCTOR(FSoftClassPath, const UClass*),
				             TArray<FString>{"InClass"})
				.Function("ResolveClass", BINDING_FUNCTION(&FSoftClassPath::ResolveClass))
				.Function("GetOrCreateIDForClass", BINDING_FUNCTION(&FSoftClassPath::GetOrCreateIDForClass,
				                                                    TArray<FString>{"InClass"}));
		}
	};

	FRegisterSoftClassPath RegisterSoftClassPath;
}
