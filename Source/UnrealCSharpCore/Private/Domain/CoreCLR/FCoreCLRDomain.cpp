#include "Domain/CoreCLR/FCoreCLRDomain.h"
#if WITH_CORECLR
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformMisc.h"
#include "Misc/Paths.h"
#include "Misc/App.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Reflection/FReflectionRegistry.h"
#include "Reflection/FClassReflection.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Binding/FBinding.h"
#include "CoreMacro/CoreCLRMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/Macro.h"
#include "Domain/CoreCLR/FCoreCLRFunctionLibrary.h"
#include "Domain/CoreCLR/FCoreCLRLog.h"
#include "Domain/Script/FScriptLog.h"
#include "Setting/UnrealCSharpSetting.h"

#define LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, InType, InMethod, InFn) \
{ \
	void* OutFn{}; \
	if (LoadAssemblyAndGetFunctionPointer(InAssembly, InType, InMethod, &OutFn); OutFn != nullptr) \
	{ \
		InFn = reinterpret_cast<decltype(InFn)>(OutFn); \
	} \
}

void* FCoreCLRDomain::HostFxrDllHandle{};

hostfxr_handle FCoreCLRDomain::HostFxrHandle{};

load_assembly_and_get_function_pointer_fn FCoreCLRDomain::LoadAssemblyAndGetFunctionPointerFn{};

void FCoreCLRDomain::Initialize()
{
	if (bIsInitialized)
	{
		return;
	}

	if (HostFxrDllHandle == nullptr)
	{
		HostFxrDllHandle = FPlatformProcess::GetDllHandle(*FCoreCLRFunctionLibrary::GetHostFxrPath());

		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
			if (UnrealCSharpSetting->IsEnableDebug())
			{
				FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics"), TEXT("1"));

				FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics_Debugger"), TEXT("1"));

				FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_DiagnosticPorts"), TEXT(""));
			}
		}

		RegisterErrorWriter();

		const auto HostFxrInitializeForRuntimeConfigFn = GetExport<hostfxr_initialize_for_runtime_config_fn>(
			HostFxrDllHandle, FUNCTION_HOSTFXR_INITIALIZE_FOR_RUNTIME_CONFIG);

		const auto HostFxrGetRuntimeDelegateFn = GetExport<hostfxr_get_runtime_delegate_fn>(
			HostFxrDllHandle, FUNCTION_HOSTFXR_GET_RUNTIME_DELEGATE);

		const auto HostPath = FCoreCLRFunctionLibrary::GetHostPath();

		auto CoreCLRDirectory = FCoreCLRFunctionLibrary::GetCoreCLRDirectory();

		FPaths::MakePlatformFilename(CoreCLRDirectory);

		const auto HostPathString = FStringToString<>(HostPath);

		const auto CoreCLRDirectoryString = FStringToString<>(CoreCLRDirectory);

		const auto HostFxrInitializeParameters = hostfxr_initialize_parameters
		{
			sizeof(hostfxr_initialize_parameters),
			reinterpret_cast<const char_t*>(HostPathString.Get()),
			reinterpret_cast<const char_t*>(CoreCLRDirectoryString.Get())
		};

		const auto HostFxrInitializeForRuntimeConfigErrorCode = HostFxrInitializeForRuntimeConfigFn(
			reinterpret_cast<const char_t*>(FStringToString<>(FCoreCLRFunctionLibrary::GetRuntimeConfigPath()).Get()),
			&HostFxrInitializeParameters,
			&HostFxrHandle);

		if (constexpr auto HostAlreadyInitializedErrorCode = 0x00000008;
			HostFxrInitializeForRuntimeConfigErrorCode != 0 &&
			HostFxrInitializeForRuntimeConfigErrorCode != HostAlreadyInitializedErrorCode)
		{
			return;
		}

		void* OutLoadAssemblyAndGetFunctionPointerFn{};

		if (const auto HostFxrGetRuntimeDelegateErrorCode = HostFxrGetRuntimeDelegateFn(
				HostFxrHandle, hdt_load_assembly_and_get_function_pointer, &OutLoadAssemblyAndGetFunctionPointerFn);
			HostFxrGetRuntimeDelegateErrorCode != 0 || OutLoadAssemblyAndGetFunctionPointerFn == nullptr)
		{
			return;
		}

		LoadAssemblyAndGetFunctionPointerFn = reinterpret_cast<load_assembly_and_get_function_pointer_fn>(
			OutLoadAssemblyAndGetFunctionPointerFn);
	}

	const auto InteropAssembly = FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath();

	if (!IFileManager::Get().FileExists(*InteropAssembly))
	{
		bIsInitialized = true;

		return;
	}

	RegisterInterop(InteropAssembly);

	RegisterLog();

	bIsInitialized = true;

	InitializeAssembly(FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath());
}

void FCoreCLRDomain::Deinitialize()
{
	if (!bIsInitialized)
	{
		return;
	}

	bIsInitialized = false;

	UnloadAssembly();

	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpSetting>())
	{
		if (UnrealCSharpSetting->IsEnableDebug())
		{
			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics"), TEXT("0"));

			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics_Debugger"), TEXT("0"));

			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_DiagnosticPorts"), TEXT(""));
		}
	}

	if (HostFxrHandle != nullptr)
	{
		if (const auto HostFxrCloseFn = GetExport<hostfxr_close_fn>(
			HostFxrDllHandle, FUNCTION_HOSTFXR_CLOSE))
		{
			HostFxrCloseFn(HostFxrHandle);
		}

		HostFxrHandle = nullptr;
	}
}

#define SCRIPT_DOMAIN_TYPE FCoreCLRDomain
#include "Domain/Script/FScriptDomainImpl.inl"
#undef SCRIPT_DOMAIN_TYPE

void FCoreCLRDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
	LoadAssembly(InAssemblies);

	if (TypeBridgeGetFunctionPointerFn != nullptr)
	{
#define GET_UTILS_FUNCTION_POINTER(InFn, InName) \
	InFn = reinterpret_cast<decltype(InFn)>(TypeBridgeGetFunctionPointerFn( \
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>( \
				*FUnrealCSharpFunctionLibrary::GetUEName()).Get()), \
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>( \
				*COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS)).Get()), \
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*InName).Get())));

		GET_UTILS_FUNCTION_POINTER(UtilsIsOverrideFn, FUNCTION_UTILS_IS_OVERRIDE)

		GET_UTILS_FUNCTION_POINTER(UtilsGetClassDescriptorFn, FUNCTION_UTILS_GET_CLASS_DESCRIPTOR)

		GET_UTILS_FUNCTION_POINTER(UtilsGetClassPropertiesFn, FUNCTION_UTILS_GET_CLASS_PROPERTIES)

		GET_UTILS_FUNCTION_POINTER(UtilsGetClassFieldsFn, FUNCTION_UTILS_GET_CLASS_FIELDS)

		GET_UTILS_FUNCTION_POINTER(UtilsGetClassMethodsFn, FUNCTION_UTILS_GET_CLASS_METHODS)
#undef GET_UTILS_FUNCTION_POINTER

		RegisterSynchronizationContextTick();

		FReflectionRegistry::Get().Initialize();

		RegisterBinding();
	}
}

void FCoreCLRDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
	if (!bIsInitialized)
	{
		return;
	}

	Assemblies.Empty();

	const auto PublishDirectory = StringCast<UTF16CHAR>(*FUnrealCSharpFunctionLibrary::GetFullPublishDirectory());

	for (const auto& AssemblyPath : InAssemblies)
	{
		if (!FPaths::FileExists(AssemblyPath))
		{
			continue;
		}

		if (AssemblyPath == FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath())
		{
			continue;
		}

		if (TArray<uint8> Data; FFileHelper::LoadFileToArray(Data, *AssemblyPath))
		{
			if (AssemblyLoaderLoadFromStreamFn != nullptr)
			{
				if (const auto Handle = AssemblyLoaderLoadFromStreamFn(Data.GetData(), Data.Num(),
				                                                       reinterpret_cast<const char16_t*>(
					                                                       PublishDirectory.Get()));
					IManagedHandleIsValid(Handle))
				{
					Assemblies.Add(Handle);
				}
			}
		}
	}
}

void FCoreCLRDomain::UnloadAssembly()
{
	FReflectionRegistry::Get().Deinitialize();

	if (AssemblyLoaderUnloadFn != nullptr)
	{
		AssemblyLoaderUnloadFn();
	}

#define CORECLR_METHOD_CLEAR(Name, FnType, ClassMacro, FuncMacro, ParamCount) Name##Fn = nullptr;

	COMMON_BRIDGE_METHODS(CORECLR_METHOD_CLEAR)

	NATIVE_BRIDGE_METHODS(CORECLR_METHOD_CLEAR)

#undef CORECLR_METHOD_CLEAR

	UtilsIsOverrideFn = nullptr;

	UtilsGetClassDescriptorFn = nullptr;

	UtilsGetClassPropertiesFn = nullptr;

	UtilsGetClassFieldsFn = nullptr;

	UtilsGetClassMethodsFn = nullptr;

	SynchronizationContextTickFn = nullptr;

	Assemblies.Empty();
}

void FCoreCLRDomain::RegisterErrorWriter() const
{
	if (const auto HostFxrSetErrorWriterFn = GetExport<hostfxr_set_error_writer_fn>(
		HostFxrDllHandle, FUNCTION_HOSTFXR_SET_ERROR_WRITER))
	{
		HostFxrSetErrorWriterFn(&FCoreCLRLog::ErrorWriter);
	}
}

void FCoreCLRDomain::RegisterInterop(const FString& InAssembly)
{
#define RESOLVE_CORECLR_METHOD(Name, FnType, ClassMacro, FuncMacro, ParamCount) \
	{ \
		const auto TypeName = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, ClassMacro, INTEROP_NAME); \
		LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeName, FuncMacro, Name##Fn) \
	}

	COMMON_BRIDGE_METHODS(RESOLVE_CORECLR_METHOD)

	NATIVE_BRIDGE_METHODS(RESOLVE_CORECLR_METHOD)

#undef RESOLVE_CORECLR_METHOD
}


void FCoreCLRDomain::LoadAssemblyAndGetFunctionPointer(const FString& InAssembly, const FString& InType,
                                                       const FString& InMethod,
                                                       void** OutFunctionPointer) const
{
	if (LoadAssemblyAndGetFunctionPointerFn != nullptr)
	{
		LoadAssemblyAndGetFunctionPointerFn(
			StringCast<char_t>(*InAssembly).Get(),
			StringCast<char_t>(*InType).Get(),
			StringCast<char_t>(*InMethod).Get(),
			UNMANAGEDCALLERSONLY_METHOD,
			nullptr,
			OutFunctionPointer);
	}
}
#endif
