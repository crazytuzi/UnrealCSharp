#include "Domain/FMonoFunctionLibrary.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

FString FMonoFunctionLibrary::GetMonoDirectory()
{
#if WITH_EDITOR
	return FString::Printf(TEXT(
		"%s/Source/ThirdParty/Mono"),
	                       *FUnrealCSharpFunctionLibrary::GetPluginDirectory()
	);
#else
	return FString::Printf(TEXT(
		"%s/Binaries/%s/Mono"),
	                       *FPaths::ProjectDir(),
#if PLATFORM_WINDOWS
	                       TEXT("Win64")
#elif PLATFORM_ANDROID
	                       TEXT("Android")
#elif PLATFORM_IOS
	                       TEXT("IOS")
#elif PLATFORM_LINUX
	                       TEXT("Linux")
#elif PLATFORM_MAC_X86
	                       TEXT("macOS_x86_64")
#elif PLATFORM_MAC_ARM64
	                       TEXT("Mac")
#endif
	);
#endif
}

FString FMonoFunctionLibrary::GetLibDirectory()
{
	return FString::Printf(TEXT(
		"%s/lib/%s/%s"),
	                       *GetMonoDirectory(),
#if PLATFORM_WINDOWS
	                       MONO_CONFIGURATION,
	                       TEXT("Win64")
#elif PLATFORM_ANDROID
	                       MONO_CONFIGURATION,
	                       TEXT("Android")
#elif PLATFORM_IOS
	                       MONO_CONFIGURATION,
	                       TEXT("IOS")
#elif PLATFORM_LINUX
	                       MONO_CONFIGURATION,
	                       TEXT("Linux_x86_64")
#elif PLATFORM_MAC_X86
	                       MONO_CONFIGURATION,
	                       TEXT("macOS_x86_64")
#elif PLATFORM_MAC_ARM64
	                       MONO_CONFIGURATION,
	                       TEXT("macOS_arm64")
#endif
	);
}

FString FMonoFunctionLibrary::GetNetDirectory()
{
	return FString::Printf(TEXT(
		"%s/net"),
	                       *GetLibDirectory()
	);
}
