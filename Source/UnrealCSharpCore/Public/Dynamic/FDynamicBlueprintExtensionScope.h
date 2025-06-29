#pragma once

#if WITH_EDITOR
#include "Dynamic/DynamicBlueprintExtension.h"
#endif
#include "UEVersion.h"

class FDynamicBlueprintExtensionScope
{
public:
	explicit FDynamicBlueprintExtensionScope(UBlueprint* InBlueprint):
		Blueprint(InBlueprint)
	{
		if (Blueprint != nullptr)
		{
			DynamicBlueprintExtension = NewObject<UDynamicBlueprintExtension>(Blueprint);

#if UE_U_BLUEPRINT_ADD_EXTENSION
			Blueprint->AddExtension(DynamicBlueprintExtension);
#else
			Blueprint->Extensions.Add(DynamicBlueprintExtension);
#endif

			DynamicBlueprintExtension->AddToRoot();
		}
	}

	~FDynamicBlueprintExtensionScope()
	{
		if (Blueprint != nullptr)
		{
#if	UE_U_BLUEPRINT_REMOVE_EXTENSION
			Blueprint->RemoveExtension(DynamicBlueprintExtension);
#else
			Blueprint->Extensions.RemoveSingleSwap(DynamicBlueprintExtension);
#endif

			Blueprint = nullptr;
		}

		if (DynamicBlueprintExtension != nullptr)
		{
			DynamicBlueprintExtension->RemoveFromRoot();

			DynamicBlueprintExtension = nullptr;
		}
	}

private:
	UBlueprint* Blueprint = nullptr;

	UDynamicBlueprintExtension* DynamicBlueprintExtension = nullptr;
};
