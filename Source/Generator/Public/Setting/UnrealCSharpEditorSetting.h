#pragma once
#include "CoreMinimal.h"
#include "UnrealCSharpEditorSetting.generated.h"


UCLASS(config = UnrealCSharpEditorSetting, defaultconfig, meta=(DisplayName="UnrealCSharpEditorSetting"))
class GENERATOR_API UUnrealCSharpEditorSetting : public UObject
{
	GENERATED_BODY()

public:
	UUnrealCSharpEditorSetting(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, meta=(GetOptions="GetDotNetPath"))
	FString DotNetPath = TEXT("");

	UPROPERTY(Config, EditAnywhere,
		meta = (GetOptions="GenModulesList", DisplayName = "List of Modules to Generator Code"))
	TArray<FString> GeneratorModules;

	UFUNCTION()
	TArray<FString> GetDotNetPath() const;

	UFUNCTION()
	TArray<FString> GenModulesList();

	#if WITH_EDITOR
    virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	#endif

};


class GENERATOR_API FUnrealCSharpEditorSettingsHelper
{
public:
	static TArray<FString> LogOutPutMessage;

	static void RegisterSettings();
	static void UnregisterSettings();


	static void OnStatusOutput(FString Message)
	{
		LogOutPutMessage.Add(Message);
	}
};
