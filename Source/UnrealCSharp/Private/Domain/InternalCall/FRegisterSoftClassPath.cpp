#include "Binding/Class/TBindingClassBuilder.inl"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"
#if !UE_U_STRUCT_F_SOFT_CLASS_PATH
#include "Binding/ScriptStruct/TScriptStruct.inl"
#endif

#if UE_U_STRUCT_F_SOFT_CLASS_PATH
BINDING_STRUCT(FSoftClassPath)
#endif

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

	[[maybe_unused]] FRegisterSoftClassPath RegisterSoftClassPath;
}
