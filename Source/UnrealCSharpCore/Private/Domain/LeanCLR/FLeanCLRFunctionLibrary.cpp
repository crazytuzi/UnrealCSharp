#include "Domain/LeanCLR/FLeanCLRFunctionLibrary.h"
#if WITH_LEANCLR
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

FString FLeanCLRFunctionLibrary::GetLeanCLRDirectory()
{
#if WITH_EDITOR
	return FString::Printf(TEXT(
		"%s/Binaries/%s"),
	                       *FUnrealCSharpFunctionLibrary::GetPluginDirectory(),
	                       FPlatformProcess::GetBinariesSubdirectory());
#elif PLATFORM_ANDROID
	return FString::Printf(TEXT(
		"%s/Binaries/Android"),
	                       *FPaths::ProjectDir());
#elif PLATFORM_IOS
	return FString::Printf(TEXT(
		"%s/Binaries/IOS"),
	                       *FPaths::ProjectDir());
#else
	return FPaths::ConvertRelativePathToFull(
		FPaths::GetPath(FPlatformProcess::ExecutablePath()));
#endif
}

FString FLeanCLRFunctionLibrary::GetLibDirectory()
{
	return FString::Printf(TEXT(
		"%s/LeanCLR/%s/net"),
	                       *GetLeanCLRDirectory(),
#if PLATFORM_ANDROID
	                       TEXT("Android")
#elif PLATFORM_IOS
	                       TEXT("IOS")
#else
	                       FPlatformProcess::GetBinariesSubdirectory()
#endif
	);
}
#endif
