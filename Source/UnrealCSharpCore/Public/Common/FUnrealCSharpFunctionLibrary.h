#pragma once

#include "CoreMinimal.h"

class UNREALCSHARPCORE_API FUnrealCSharpFunctionLibrary
{
public:
	static FString GetDotNet();

public:
	static FString GetModuleName(const UField* InField);

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetFullInterface(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetFullClass(const UEnum* InEnum);

	static FString GetClassNameSpace(const UEnum* InStruct);

	static FString GetFullClass(const FDelegateProperty* InDelegateProperty);

	static FString GetClassNameSpace(const FDelegateProperty* InDelegateProperty);

	static FString GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetFileName(const UField* InField);

	static FString GetOldFileName(const UField* InField, const FString& OldName);

	static FString GetBaseName();

	static FString GetBasePath();

	static FString GetUEProjectName();

	static FString GetUEPath();

	static FString GetUEProxyPath();

	static FString GetGameProjectName();

	static FString GetGamePath();

	static FString GetGameProxyPath();

	static FString GetBindingPath();

	static FString GetAssemblyUtilProjectName();

	static FString GetAssemblyUtilPath();

	static FString GetGenerationPath(const UField* InField);

	static FString GetGenerationPath(const FString& InScriptPath);

	static FString GetScriptPath();

	static FString GetCodeAnalysisPath();

	static TArray<FString> GetChangedDirectories();

	static FString Encode(const FString& InName, bool bEncodeWideString = false);

	static TArray<FString>& GetEngineModuleList();

private:
	static TArray<FString>& GetGameModuleList();
};
