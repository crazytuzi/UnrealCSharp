#pragma once
#include "CoreMinimal.h"
#include "UnrealCSharpSetting.generated.h"


UCLASS(config = UnrealCSharpEditorSetting, defaultconfig, meta=(DisplayName="UnrealCSharpEditorSetting"))
class UUnrealCSharp_Settings : public UObject
{
	GENERATED_BODY()

public:
	UUnrealCSharp_Settings(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer){};
	
	UPROPERTY(Config, EditAnywhere, Category = "Path",meta=(GetOptions="GetDotNetPath"))
	FString DotNetPath = TEXT("");

	UPROPERTY(config, EditAnywhere, meta=(RelativeToGameContentDir ))
	TArray<FDirectoryPath> GenSourcePath;
	
	UFUNCTION()
	TArray<FString> GetDotNetPath() const;

#if WITH_EDITOR
	//virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	
};


class FUnrealCSharpSettingsHelper
{
public:
	static TArray<FString> LogOutPutMessage;

	static void RegisterSettings();
	static void UnregisterSettings();
	

	static void OnStatusOutput(FString Message)
	{
		LogOutPutMessage.Add(Message);
	}

	static void GetAllAdditionAssetsPaths(TArray<FName>& PathArray);
	
};