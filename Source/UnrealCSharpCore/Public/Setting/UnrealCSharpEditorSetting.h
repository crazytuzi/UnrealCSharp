#pragma once

#include "CoreMinimal.h"
#include "UnrealCSharpEditorSetting.generated.h"

UCLASS(config = UnrealCSharpEditorSetting, defaultconfig, meta = (DisplayName = "UnrealCSharpEditorSetting"))
class UNREALCSHARPCORE_API UUnrealCSharpEditorSetting : public UObject
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	static void RegisterSettings();

	static void UnregisterSettings();
#endif

public:
#if WITH_EDITOR
	UFUNCTION()
	const FString& GetDotNetPath() const;

	UFUNCTION()
	TArray<FString> GetDotNetPathArray() const;

	UFUNCTION()
	const TArray<FString>& GetSupportedModule();

	UFUNCTION()
	const TArray<FString>& GetSupportedAssetsPath();

	UFUNCTION()
	TArray<FString> GetModuleList();
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(Config, EditAnywhere, meta = (GetOptions = "GetDotNetPathArray"))
	FString DotNetPath = TEXT("");

	UPROPERTY(Config, EditAnywhere, meta = (GetOptions = "GetModuleList"))
	TArray<FString> SupportedModule;

	UPROPERTY(Config, EditAnywhere, meta = (GetOptions = "GetModuleList"))
	TArray<FString> SupportedAssetsPath;
#endif
};
