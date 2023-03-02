#pragma once
#include "CoreMinimal.h"
#include "UnrealCSharpSettings.generated.h"
UCLASS(Config=UnrealCSharp, DefaultConfig, Meta=(DisplayName="UnrealCSharp"))
class UNREALCSHARPEDITOR_API UnrealCSharpSettings : public UObject
{
	GENERATED_BODY()

public:
	UnrealCSharpSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, Category = "Debug", DisplayName="Address")
	FString IP = TEXT("127.0.0.1");

	UPROPERTY(Config, EditAnywhere, Category = "Debug", DisplayName="Debug")
	bool bDebug = true;
	
	UPROPERTY(Config, EditAnywhere, Category = "Debug", DisplayName="Port")
	uint16 uPort = 55556;
};
