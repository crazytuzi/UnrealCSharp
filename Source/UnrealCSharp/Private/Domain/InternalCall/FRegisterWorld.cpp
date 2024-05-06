#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FRegisterObjectFlags.h"

BINDING_ENUM(FActorSpawnParameters::ESpawnActorNameMode)

BINDING_CLASS(FActorSpawnParameters)

struct FRegisterSpawnActorNameMode
{
	FRegisterSpawnActorNameMode()
	{
		TBindingEnumBuilder<FActorSpawnParameters::ESpawnActorNameMode, true>()
			.Enumerator("Required_Fatal", FActorSpawnParameters::ESpawnActorNameMode::Required_Fatal)
			.Enumerator("Required_ErrorAndReturnNull",
			            FActorSpawnParameters::ESpawnActorNameMode::Required_ErrorAndReturnNull)
			.Enumerator("Required_ReturnNull", FActorSpawnParameters::ESpawnActorNameMode::Required_ReturnNull)
			.Enumerator("Requested", FActorSpawnParameters::ESpawnActorNameMode::Requested);
	}
};

static FRegisterSpawnActorNameMode RegisterSpawnActorNameMode;

struct FRegisterActorSpawnParameters
{
	FRegisterActorSpawnParameters()
	{
		TBindingClassBuilder<FActorSpawnParameters, true>(NAMESPACE_BINDING)
			.Property("Name", BINDING_PROPERTY(&FActorSpawnParameters::Name))
			.Property("Template", BINDING_PROPERTY(&FActorSpawnParameters::Template))
			.Property("Owner", BINDING_PROPERTY(&FActorSpawnParameters::Owner))
			.Property("Instigator", BINDING_PROPERTY(&FActorSpawnParameters::Instigator))
			.Property("OverrideLevel", BINDING_PROPERTY(&FActorSpawnParameters::OverrideLevel))
			.Property("OverrideParentComponent", BINDING_PROPERTY(&FActorSpawnParameters::OverrideParentComponent))
			.Property("SpawnCollisionHandlingOverride",
			          BINDING_PROPERTY(&FActorSpawnParameters::SpawnCollisionHandlingOverride))
			// @TODO
			// bNoFail
			// bDeferConstruction
			// bAllowDuringConstructionScript
			.Property("NameMode", BINDING_PROPERTY(&FActorSpawnParameters::NameMode))
			.Property("ObjectFlags", BINDING_PROPERTY(&FActorSpawnParameters::ObjectFlags));
	}
};

FRegisterActorSpawnParameters RegisterActorSpawnParameters;

struct FRegisterWorld
{
	static MonoObject* SpawnActorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const FGarbageCollectionHandle InClass,
	                                            const FGarbageCollectionHandle InTransform,
	                                            const FGarbageCollectionHandle InActorSpawnParameters)
	{
		if (const auto FoundWorld = FCSharpEnvironment::GetEnvironment().GetObject<UWorld>(InGarbageCollectionHandle))
		{
			const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

			const auto FoundTransform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
				InTransform);

			const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InActorSpawnParameters);

			const auto Actor = FoundWorld->SpawnActor<AActor>(FoundClass,
			                                                  *FoundTransform,
			                                                  FoundActorSpawnParameters != nullptr
				                                                  ? *FoundActorSpawnParameters
				                                                  : FActorSpawnParameters());

			return FCSharpEnvironment::GetEnvironment().Bind(Actor);
		}

		return nullptr;
	}

	FRegisterWorld()
	{
		TBindingClassBuilder<UWorld>(NAMESPACE_LIBRARY)
			.Function("SpawnActor", SpawnActorImplementation);
	}
};

static FRegisterWorld RegisterWorld;
