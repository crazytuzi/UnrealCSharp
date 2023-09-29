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
                                                          const FGarbageCollectionHandle InClass,
                                                          const MonoObject* InTransform,
                                                          const FGarbageCollectionHandle InOwner,
                                                          const FGarbageCollectionHandle InInstigator,
                                                          uint8 InCollisionHandlingOverride, MonoObject** OutValue)
{
	if (const auto FoundWorld = FCSharpEnvironment::GetEnvironment().GetObject<UWorld>(InGarbageCollectionHandle))
	{
		const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

		const auto FoundTransform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
			InTransform);

		const auto FoundOwner = FCSharpEnvironment::GetEnvironment().GetObject<AActor>(InOwner);

		const auto FoundInstigator = FCSharpEnvironment::GetEnvironment().GetObject<APawn>(InInstigator);

		const auto SpawnActorCollisionHandlingMethod = static_cast<ESpawnActorCollisionHandlingMethod>(
			InCollisionHandlingOverride);

		FActorSpawnParameters ActorSpawnParameters;

		ActorSpawnParameters.Owner = FoundOwner;

		ActorSpawnParameters.Instigator = FoundInstigator;

		ActorSpawnParameters.SpawnCollisionHandlingOverride = SpawnActorCollisionHandlingMethod;

		const auto Actor = FoundWorld->SpawnActor<AActor>(FoundClass, *FoundTransform, ActorSpawnParameters);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Actor);
	}
}
