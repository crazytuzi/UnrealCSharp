#pragma once

#include "CoreMinimal.h"
#include "UnrealCSharpEditorSetting.generated.h"

UENUM()
enum ESolutionConfiguration
{
	Debug,
	Release
};

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

	bool EnableDeleteProxyDirectory() const;

	bool EnableDeleteBindingDirectory() const;

	bool EnableCompiled() const;

	bool EnableAssetChanged() const;

	bool EnableDirectoryChanged() const;

	bool IsSkipGenerateEngineModules() const;

	bool IsGenerateAllModules() const;

	const TArray<FString>& GetSupportedModule() const;

	bool IsGenerateAsset() const;

	const TArray<FDirectoryPath>& GetSupportedAssetPath() const;

	const TArray<TSubclassOf<UObject>>& GetSupportedAssetClass() const;

	bool IsGenerateFunctionComment() const;

	UFUNCTION()
	TArray<FString> GetModuleList();

	UFUNCTION()
	TArray<FString> GetClassList();

	const TArray<FString>& GetClassBlacklist() const;

	ESolutionConfiguration GetEditorConfiguration() const;

	ESolutionConfiguration GetRuntimeConfiguration() const;
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(Config, EditAnywhere, Category = DotNet, meta = (GetOptions = "GetDotNetPathArray"))
	FString DotNetPath = TEXT("");

	UPROPERTY(Config, EditAnywhere, Category = Generator, meta = (RelativePath))
	FProjectDirectoryPath ScriptDirectory;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableDeleteProxyDirectory;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableDeleteBindingDirectory;

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
		meta = (LongPackageName, EditCondition = "bIsGenerateAsset"))
	TArray<FDirectoryPath> SupportedAssetPath;

	UPROPERTY(Config, EditAnywhere, Category = Generator, meta = (EditCondition = "bIsGenerateAsset"))
	TArray<TSubclassOf<UObject>> SupportedAssetClass;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bIsGenerateFunctionComment;

	UPROPERTY(Config, EditAnywhere, Category = Generator)
	bool bEnableExport;

	UPROPERTY(Config, EditAnywhere, Category = Generator,
		meta = (GetOptions = "GetModuleList", EditCondition = "bEnableExport"))
	TArray<FString> ExportModule;

	UPROPERTY(Config, EditAnywhere, Category = Generator,
		meta = (GetOptions = "GetClassList", EditCondition = "bEnableExport"))
	TArray<FString> ClassBlacklist;

	UPROPERTY(Config, EditAnywhere, Category = Solution)
	TEnumAsByte<ESolutionConfiguration> EditorConfiguration;

	UPROPERTY(Config, EditAnywhere, Category = Solution)
	TEnumAsByte<ESolutionConfiguration> RuntimeConfiguration;
#endif
};
