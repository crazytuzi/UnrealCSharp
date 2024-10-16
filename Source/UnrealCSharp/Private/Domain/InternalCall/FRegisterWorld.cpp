#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"
#include "FRegisterObjectFlags.h"

BINDING_ENUM(FActorSpawnParameters::ESpawnActorNameMode, false)

BINDING_CLASS(FActorSpawnParameters)

namespace
{
	struct FRegisterSpawnActorNameMode
	{
		FRegisterSpawnActorNameMode()
		{
			TBindingEnumBuilder<FActorSpawnParameters::ESpawnActorNameMode, false>()
				.Enumerator("Required_Fatal", FActorSpawnParameters::ESpawnActorNameMode::Required_Fatal)
				.Enumerator("Required_ErrorAndReturnNull",
				            FActorSpawnParameters::ESpawnActorNameMode::Required_ErrorAndReturnNull)
				.Enumerator("Required_ReturnNull", FActorSpawnParameters::ESpawnActorNameMode::Required_ReturnNull)
				.Enumerator("Requested", FActorSpawnParameters::ESpawnActorNameMode::Requested);
		}
	};

	[[maybe_unused]] FRegisterSpawnActorNameMode RegisterSpawnActorNameMode;

	struct FRegisterActorSpawnParameters
	{
		static bool GetbNoFailImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InGarbageCollectionHandle))
			{
				return FoundActorSpawnParameters->bNoFail;
			}

			return false;
		}

		static void SetbNoFailImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                     const bool InValue)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InGarbageCollectionHandle))
			{
				FoundActorSpawnParameters->bNoFail = InValue;
			}
		}

		static bool GetbDeferConstructionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InGarbageCollectionHandle))
			{
				return FoundActorSpawnParameters->bDeferConstruction;
			}

			return false;
		}

		static void SetbDeferConstructionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                                const bool InValue)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InGarbageCollectionHandle))
			{
				FoundActorSpawnParameters->bDeferConstruction = InValue;
			}
		}

		static bool GetbAllowDuringConstructionScriptImplementation(
			const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InGarbageCollectionHandle))
			{
				return FoundActorSpawnParameters->bAllowDuringConstructionScript;
			}

			return false;
		}

		static void SetbAllowDuringConstructionScriptImplementation(
			const FGarbageCollectionHandle InGarbageCollectionHandle,
			const bool InValue)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InGarbageCollectionHandle))
			{
				FoundActorSpawnParameters->bAllowDuringConstructionScript = InValue;
			}
		}

		FRegisterActorSpawnParameters()
		{
			TBindingClassBuilder<FActorSpawnParameters, false>(NAMESPACE_LIBRARY)
				.Property("Name", BINDING_PROPERTY(&FActorSpawnParameters::Name))
				.Property("Template", BINDING_PROPERTY(&FActorSpawnParameters::Template))
				.Property("Owner", BINDING_PROPERTY(&FActorSpawnParameters::Owner))
				.Property("Instigator", BINDING_PROPERTY(&FActorSpawnParameters::Instigator))
				.Property("OverrideLevel", BINDING_PROPERTY(&FActorSpawnParameters::OverrideLevel))
				.Property("OverrideParentComponent", BINDING_PROPERTY(&FActorSpawnParameters::OverrideParentComponent))
				.Property("SpawnCollisionHandlingOverride",
				          BINDING_PROPERTY(&FActorSpawnParameters::SpawnCollisionHandlingOverride))
				.Property("NameMode", BINDING_PROPERTY(&FActorSpawnParameters::NameMode))
				.Property("ObjectFlags", BINDING_PROPERTY(&FActorSpawnParameters::ObjectFlags))
				.Function("GetbNoFail", GetbNoFailImplementation)
				.Function("SetbNoFail", SetbNoFailImplementation)
				.Function("GetbDeferConstruction", GetbDeferConstructionImplementation)
				.Function("SetbDeferConstruction", SetbDeferConstructionImplementation)
				.Function("GetbAllowDuringConstructionScript", GetbAllowDuringConstructionScriptImplementation)
				.Function("SetbAllowDuringConstructionScript", SetbAllowDuringConstructionScriptImplementation);
		}
	};

	[[maybe_unused]] FRegisterActorSpawnParameters RegisterActorSpawnParameters;

	struct FRegisterWorld
	{
		static MonoObject* SpawnActorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const FGarbageCollectionHandle InClass,
		                                            const FGarbageCollectionHandle InTransform,
		                                            const FGarbageCollectionHandle InActorSpawnParameters)
		{
			if (const auto FoundWorld = FCSharpEnvironment::GetEnvironment().GetObject<UWorld>(
				InGarbageCollectionHandle))
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

	[[maybe_unused]] FRegisterWorld RegisterWorld;
}
