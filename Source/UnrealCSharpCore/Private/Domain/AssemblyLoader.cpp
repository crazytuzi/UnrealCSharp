#include "Domain/AssemblyLoader.h"
#include "CoreMacro/Macro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Misc/FileHelper.h"

TArray<uint8> UAssemblyLoader::Load(const FString& InAssemblyName)
{
#if WITH_EDITOR
	const auto Path = FString::Printf(TEXT(
		"%s/Source/ThirdParty/Mono/lib/%s/%s/net"),
	                                  *FUnrealCSharpFunctionLibrary::GetPluginDirectory(),
	                                  MONO_CONFIGURATION,
#if PLATFORM_WINDOWS
	                                  TEXT("Win64")
#elif PLATFORM_MAC_X86
	                                  TEXT("macOS_x86_64")
#elif PLATFORM_MAC_ARM64
	                                  TEXT("macOS_arm64")
#endif
	);
#else
	const auto Path = FString::Printf(TEXT(
		"%s/Binaries/%s/Mono/lib/%s/%s/net"),
	                                  *FPaths::ProjectDir(),
#if PLATFORM_WINDOWS
	                                  TEXT("Win64"),
	                                  MONO_CONFIGURATION,
	                                  TEXT("Win64"));
#elif PLATFORM_ANDROID
	                                  TEXT("Android"),
	                                  MONO_CONFIGURATION,
	                                  TEXT("Android"));
#elif PLATFORM_IOS
	                                  TEXT("IOS"),
	                                  MONO_CONFIGURATION,
	                                  TEXT("IOS"));
#elif PLATFORM_LINUX
	                                  TEXT("Linux"),
	                                  MONO_CONFIGURATION,
	                                  TEXT("Linux_x86_64"));
#elif PLATFORM_MAC_X86
	                                  TEXT("macOS_x86_64"),
	                                  MONO_CONFIGURATION,
	                                  TEXT("macOS_x86_64"));
#elif PLATFORM_MAC_ARM64
	                                  TEXT("Mac"),
	                                  MONO_CONFIGURATION,
	                                  TEXT("macOS_arm64"));
#endif
#endif

	const auto File = FPaths::Combine(Path, InAssemblyName) + DLL_SUFFIX;

	TArray<uint8> Data;

	FFileHelper::LoadFileToArray(Data, *File);

	return Data;
}
