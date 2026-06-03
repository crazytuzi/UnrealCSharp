#include "Engine/Level.h"
#include "GameFramework/Pawn.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IUnmanagedBool.h"
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
		static IUnmanagedBool GetbNoFailImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InManagedHandle))
			{
				return BoolToIUnmanagedBool(FoundActorSpawnParameters->bNoFail);
			}

			return IUnmanagedFalse;
		}

		static void SetbNoFailImplementation(const IManagedHandle InManagedHandle,
		                                     const bool InValue)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InManagedHandle))
			{
				FoundActorSpawnParameters->bNoFail = InValue;
			}
		}

		static IUnmanagedBool GetbDeferConstructionImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InManagedHandle))
			{
				return BoolToIUnmanagedBool(FoundActorSpawnParameters->bDeferConstruction);
			}

			return IUnmanagedFalse;
		}

		static void SetbDeferConstructionImplementation(const IManagedHandle InManagedHandle,
		                                                const bool InValue)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InManagedHandle))
			{
				FoundActorSpawnParameters->bDeferConstruction = InValue;
			}
		}

		static IUnmanagedBool GetbAllowDuringConstructionScriptImplementation(
			const IManagedHandle InManagedHandle)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InManagedHandle))
			{
				return BoolToIUnmanagedBool(FoundActorSpawnParameters->bAllowDuringConstructionScript);
			}

			return IUnmanagedFalse;
		}

		static void SetbAllowDuringConstructionScriptImplementation(
			const IManagedHandle InManagedHandle,
			const bool InValue)
		{
			if (const auto FoundActorSpawnParameters = FCSharpEnvironment::GetEnvironment().GetBinding<
				FActorSpawnParameters>(InManagedHandle))
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
		static IManagedObject SpawnActorImplementation(const IManagedHandle InManagedHandle,
		                                               const IManagedHandle InClass,
		                                               const IManagedHandle InTransform,
		                                               const IManagedHandle InActorSpawnParameters)
		{
			if (const auto FoundWorld = FCSharpEnvironment::GetEnvironment().GetObject<UWorld>(
				InManagedHandle))
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

			return INVALID_MANAGED;
		}

		FRegisterWorld()
		{
			TBindingClassBuilder<UWorld>(NAMESPACE_LIBRARY)
				.Function("SpawnActor", SpawnActorImplementation);
		}
	};

	[[maybe_unused]] FRegisterWorld RegisterWorld;
}
