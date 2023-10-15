#pragma once

#include "CoreMinimal.h"
#include "UnrealCSharpEditorSetting.generated.h"

UCLASS(config = UnrealCSharpEditorSetting, defaultconfig, meta=(DisplayName="UnrealCSharpEditorSetting"))
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
	const TArray<FString>& GetGeneratorModules();

	UFUNCTION()
	TArray<FString> GetModuleArray();
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(Config, EditAnywhere, meta=(GetOptions="GetDotNetPathArray"))
	FString DotNetPath = TEXT("");

	UPROPERTY(Config, EditAnywhere,
		meta = (GetOptions="GetModuleArray", DisplayName = "List of Module to Generator Code"))
	TArray<FString> GeneratorModules;
#endif
};
