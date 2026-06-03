#if WITH_CORECLR
#include "Domain/CoreCLR/FCoreCLRFunctionLibrary.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

FString FCoreCLRFunctionLibrary::GetCoreCLRDirectory()
{
#if WITH_EDITOR
	return FString::Printf(TEXT(
		"%s/Binaries/%s"),
	                       *FUnrealCSharpFunctionLibrary::GetPluginDirectory(),
	                       FPlatformProcess::GetBinariesSubdirectory()
	);
#else
	return FPaths::ConvertRelativePathToFull(FPaths::GetPath(FPlatformProcess::ExecutablePath()));
#endif
}

FString FCoreCLRFunctionLibrary::GetHostFxrPath()
{
	return FString::Printf(TEXT(
		"%s/%s"),
	                       *GetCoreCLRDirectory(),
	                       *LIB_HOSTFXR
	);
}

FString FCoreCLRFunctionLibrary::GetRuntimeConfigPath()
{
	return FString::Printf(TEXT(
		"%s/%s"),
	                       *GetCoreCLRDirectory(),
	                       *CORECLR_RUNTIME_CONFIG
	);
}

FString FCoreCLRFunctionLibrary::GetHostPath()
{
	return FPlatformProcess::ExecutablePath();
}
#endif
