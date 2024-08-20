// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Domain/AssemblyLoader.h"
#include "UnrealCSharpSetting.generated.h"

USTRUCT()
struct FGameContentDirectoryPath : public FDirectoryPath
{
	GENERATED_BODY()

	FGameContentDirectoryPath() = default;

	explicit FGameContentDirectoryPath(const FString& InPath):
		FDirectoryPath()
	{
		Path = InPath;
	}
};

USTRUCT()
struct FBindClass
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObject> Class;

	UPROPERTY(EditAnywhere)
	bool bNeedMonoClass = true;
};

/**
 * 
 */
UCLASS(config = UnrealCSharpSetting, defaultconfig, meta = (DisplayName = "UnrealCSharpSetting"))
class UNREALCSHARPCORE_API UUnrealCSharpSetting : public UObject
{
	GENERATED_UCLASS_BODY()

public:
#if WITH_EDITOR
	static void RegisterSettings();

	static void UnregisterSettings();
#endif

public:
	const FGameContentDirectoryPath& GetPublishDirectory() const;

	const FString& GetUEName() const;

	const FString& GetGameName() const;

	UAssemblyLoader* GetAssemblyLoader() const;

	const TArray<FBindClass>& GetBindClass() const;

	bool IsEnableDebug() const;

	const FString& GetHost() const;

	int32 GetPort() const;

private:
	UPROPERTY(Config, EditAnywhere, Category = Publish, meta = (RelativePath))
	FGameContentDirectoryPath PublishDirectory;

	UPROPERTY(Config, EditAnywhere, Category = Publish, meta = (DisplayName = "UE Name"))
	FString UEName;

	UPROPERTY(Config, EditAnywhere, Category = Publish, meta = (DisplayName = "Game Name"))
	FString GameName;

	UPROPERTY(Config, EditAnywhere, Category = Domain)
	TSubclassOf<UAssemblyLoader> AssemblyLoader;

	UPROPERTY(Config, EditAnywhere, Category = Bind)
	TArray<FBindClass> BindClass;

	UPROPERTY(Config, EditAnywhere, Category = Debug)
	bool bEnableDebug;

	UPROPERTY(Config, EditAnywhere, Category = Debug)
	FString Host;

	UPROPERTY(Config, EditAnywhere, Category = Debug)
	int32 Port;
};
