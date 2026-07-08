#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "GeneratorScriptCodeCommandlet.generated.h"

UCLASS()
class UGeneratorScriptCodeCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	virtual int32 Main(const FString& Params) override;
};
