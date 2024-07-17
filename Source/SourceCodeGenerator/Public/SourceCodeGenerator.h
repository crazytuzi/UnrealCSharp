#pragma once

#include "CoreMinimal.h"
#include "IScriptGeneratorPluginInterface.h"

class FSourceCodeGeneratorModule : public IScriptGeneratorPluginInterface
{
private:
	static constexpr auto LargeInitialBufferSizes = 256 * 1024;

	static constexpr auto SmallInitialBufferSizes = 1 * 1024;

	typedef TStringBuilder<LargeInitialBufferSizes> FBigStringBuilder;

	typedef TStringBuilder<SmallInitialBufferSizes> FSmallStringBuilder;

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

public:
	/** IScriptGeneratorPluginInterface implementation */
	virtual FString GetGeneratedCodeModuleName() const override;

	virtual bool SupportsTarget(const FString& TargetName) const override;

	virtual bool ShouldExportClassesForModule(const FString& ModuleName, EBuildModuleType::Type ModuleType,
	                                          const FString& ModuleGeneratedIncludeDirectory) const override;

	virtual void Initialize(const FString& RootLocalPath, const FString& RootBuildPath,
	                        const FString& OutputDirectory, const FString& IncludeBase) override;

	virtual void ExportClass(UClass* Class, const FString& SourceHeaderFilename,
	                         const FString& GeneratedHeaderFilename, bool bHasChanged) override;

	virtual void FinishExport() override;

	virtual FString GetGeneratorName() const override;

private:
	static bool CanExportClass(const UClass* Class);

	static bool CanExportFunction(const UFunction* Function);

	static bool CanExportProperty(const FProperty* Property);

	static void ExportFunction(FBigStringBuilder& StringBuilder, const UClass* Class, const UFunction* Function);

	static void ExportProperty(FBigStringBuilder& StringBuilder, const UClass* Class, const FProperty* Property);

	static bool IsClassTypeSupported(const UClass* Class);

	static bool IsPropertyTypeSupported(const FProperty* Property);

	static FString GetReturnPropertySignature(const FProperty* Property);

	static FString GetParamPropertySignature(const FProperty* Property);

	static FString GetFunctionSignature(const UClass* Class, const UFunction* Function);

	static FString GetFunctionParamName(const UFunction* Function);

	static FString GetFunctionDefaultValue(const UFunction* Function);

	static bool FindDefaultValue(const TMap<FName, FString>* MetaMap, const FProperty* Param, FString& String);

	static void GetPropertySignature(const FProperty* Property, FString& String);

	static void GetDependencyClasses(const FProperty* Property, TSet<UClass*>& DependencyClasses);

	static void SaveIfChanged(const FString& FileName, const FString& String);

	FString GetHeaderFile(UClass* Class);

	static FString GenerateInclude(const FString& FileName);

	FString GetInclude(UClass* Class);

	static void GetPlugins(const FString& InPathName, TMap<FString, FString>& Plugins);

	static void GetModules(const FString& InPathName, TMap<FString, FString>& Modules);

	static void GetModules(const FString& InPathName, TSet<FString>& Modules);

private:
	FString OutputPath;

	TArray<FString> ExportModules;

	TSet<FString> Project;

	TMap<FString, FString> HeaderPath;

	TArray<UClass*> ExportClasses;

	const FString BindingSuffix = FString(TEXT(".binding.inl"));

	const FString HeaderSuffix = FString(TEXT(".header.inl"));
};
