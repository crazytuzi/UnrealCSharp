#include "Domain/InternalCall/FWorldImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"

BINDING_REFLECTION_CLASS(UWorld);

struct FRegisterWorld
{
	FRegisterWorld()
	{
		TReflectionClassBuilder<UWorld>(NAMESPACE_LIBRARY)
			.Function("SpawnActor", FWorldImplementation::World_SpawnActorImplementation)
			.Register();
	}
};

static FRegisterWorld RegisterWorld;

void FWorldImplementation::World_SpawnActorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const FGarbageCollectionHandle Class,
                                                          const MonoObject* Transform, MonoObject** OutValue)
{
	if (const auto FoundWorld = FCSharpEnvironment::GetEnvironment().GetObject<UWorld>(InGarbageCollectionHandle))
	{
		const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(Class);

		const auto FoundTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
			UScriptStruct, FTransform>(Transform);

		const auto Actor = FoundWorld->SpawnActor(FoundClass, FoundTransform);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Actor);
	}
}
