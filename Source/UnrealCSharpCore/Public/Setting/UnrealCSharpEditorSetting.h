#pragma once

#include "CoreMinimal.h"
#include "UnrealCSharpEditorSetting.generated.h"

USTRUCT()
struct FProjectDirectoryPath : public FDirectoryPath
{
	GENERATED_BODY()

	FProjectDirectoryPath() = default;

	explicit FProjectDirectoryPath(const FString& InPath):
		FDirectoryPath()
	{
		Path = InPath;
	}

	operator FString() const
	{
		return Path;
	}
};

UCLASS(config = UnrealCSharpEditorSetting, defaultconfig, meta = (DisplayName = "UnrealCSharpEditorSetting"))
class UNREALCSHARPCORE_API UUnrealCSharpEditorSetting : public UObject
{
	GENERATED_BODY()

public:
	explicit UUnrealCSharpEditorSetting(const FObjectInitializer& ObjectInitializer);

public:
#if WITH_EDITOR
	static void RegisterSettings();

	static void UnregisterSettings();
#endif

public:
#if WITH_EDITOR
	const FString& GetDotNetPath() const;

	UFUNCTION()
	TArray<FString> GetDotNetPathArray() const;

	const FProjectDirectoryPath& GetScriptDirectory() const;

	bool EnableCompiled() const;

	bool EnableAssetChanged() const;

	bool EnableDirectoryChanged() const;

	bool IsSkipGenerateEngineModules() const;

	bool IsGenerateAllModules() const;

	const TArray<FString>& GetSupportedModule() const;

	bool IsGenerateAsset() const;

	const TArray<FString>& GetSupportedAssetPath() const;

	const TArray<TSubclassOf<UObject>>& GetSupportedAssetClass() const;

	bool IsGenerateFunctionComment() const;

	UFUNCTION()
	TArray<FString> GetModuleList();
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(Config, EditAnywhere, Category = DotNet, meta = (GetOptions = "GetDotNetPathArray"))
	FString DotNetPath = TEXT("");

	UPROPERTY(Config, EditAnywhere, Category = Generator, meta = (RelativePath))
	FProjectDirectoryPath ScriptDirectory;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableCompiled;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableAssetChanged;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableDirectoryChanged;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bIsSkipGenerateEngineModules;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bIsGenerateAllModules;

	UPROPERTY(Config, EditAnywhere, Category = Generator,
		meta = (GetOptions = "GetModuleList", EditCondition = "!bIsGenerateAllModules"))
	TArray<FString> SupportedModule;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bIsGenerateAsset;

	UPROPERTY(Config, EditAnywhere, Category = Generator,
		meta = (GetOptions = "GetModuleList", EditCondition = "bIsGenerateAsset"))
	TArray<FString> SupportedAssetPath;

	UPROPERTY(Config, EditAnywhere, Category = Generator, meta = (EditCondition = "bIsGenerateAsset"))
	TArray<TSubclassOf<UObject>> SupportedAssetClass;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bIsGenerateFunctionComment;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableExport;

	UPROPERTY(Config, EditAnywhere, Category = Generator,
		meta = (GetOptions = "GetModuleList", EditCondition = "bEnableExport"))
	TArray<FString> ExportModule;
#endif
};
