#pragma once

#include "CoreMinimal.h"
#include "Blueprint/BlueprintExtension.h"
#include "DynamicBlueprintExtension.generated.h"

UCLASS()
class UNREALCSHARPCORE_API UDynamicBlueprintExtension : public UBlueprintExtension
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext) override final;
#endif
};
