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
#include "CoreMacro/PropertyMacro.h"
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

FCoreCLRDomain::~FCoreCLRDomain()
{
	if (HostFxrHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(HostFxrHandle);

		HostFxrHandle = nullptr;
	}
}

void FCoreCLRDomain::Initialize()
{
	if (bIsInitialized)
	{
		return;
	}

	if (LoadAssemblyAndGetFunctionPointerFn == nullptr)
	{
		HostFxrHandle = FPlatformProcess::GetDllHandle(*FCoreCLRFunctionLibrary::GetHostFxrPath());

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
			HostFxrHandle, FUNCTION_HOSTFXR_INITIALIZE_FOR_RUNTIME_CONFIG);

		const auto HostFxrGetRuntimeDelegateFn = GetExport<hostfxr_get_runtime_delegate_fn>(
			HostFxrHandle, FUNCTION_HOSTFXR_GET_RUNTIME_DELEGATE);

		const auto HostFxrCloseFn = GetExport<hostfxr_close_fn>(HostFxrHandle, FUNCTION_HOSTFXR_CLOSE);

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

		hostfxr_handle HostContextHandle{};

		const auto HostFxrInitializeForRuntimeConfigErrorCode = HostFxrInitializeForRuntimeConfigFn(
			reinterpret_cast<const char_t*>(FStringToString<>(FCoreCLRFunctionLibrary::GetRuntimeConfigPath()).Get()),
			&HostFxrInitializeParameters,
			&HostContextHandle);

		if (constexpr auto HostAlreadyInitializedErrorCode = 0x00000008;
			HostFxrInitializeForRuntimeConfigErrorCode != 0 &&
			HostFxrInitializeForRuntimeConfigErrorCode != HostAlreadyInitializedErrorCode)
		{
			return;
		}

		void* OutLoadAssemblyAndGetFunctionPointerFn{};

		if (const auto HostFxrGetRuntimeDelegateErrorCode = HostFxrGetRuntimeDelegateFn(
				HostContextHandle, hdt_load_assembly_and_get_function_pointer, &OutLoadAssemblyAndGetFunctionPointerFn);
			HostFxrGetRuntimeDelegateErrorCode != 0 || OutLoadAssemblyAndGetFunctionPointerFn == nullptr)
		{
			HostFxrCloseFn(HostContextHandle);

			HostContextHandle = nullptr;

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

	if (TypeBridgeGetFunctionPointerFn == nullptr)
	{
		RegisterInterop(InteropAssembly);

		RegisterLog();
	}

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
}

#define SCRIPT_DOMAIN_TYPE FCoreCLRDomain
#include "Domain/Script/FScriptDomainImpl.inl"
#undef SCRIPT_DOMAIN_TYPE

void FCoreCLRDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
	LoadAssembly(InAssemblies);

	if (TypeBridgeGetFunctionPointerFn != nullptr)
	{
		UtilsGetClassReflectionFn = reinterpret_cast<utils_get_class_reflection_fn>(
			TypeBridgeGetFunctionPointerFn(
				reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*FUnrealCSharpFunctionLibrary::GetUEName()).
					Get()),
				reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(
					*COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS)).Get()),
				reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*FUNCTION_UTILS_GET_CLASS_REFLECTION).Get())));

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

	UtilsGetClassReflectionFn = nullptr;

	Assemblies.Empty();
}

void FCoreCLRDomain::RegisterErrorWriter() const
{
	if (const auto HostFxrSetErrorWriterFn = GetExport<hostfxr_set_error_writer_fn>(
		HostFxrHandle, FUNCTION_HOSTFXR_SET_ERROR_WRITER))
	{
		HostFxrSetErrorWriterFn(&FCoreCLRLog::ErrorWriter);
	}
}

void FCoreCLRDomain::RegisterInterop(const FString& InAssembly)
{
	const auto AssemblyLoader = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_ASSEMBLY_LOADER, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, AssemblyLoader, FUNCTION_ASSEMBLY_LOADER_LOAD_FROM_STREAM,
	                                       AssemblyLoaderLoadFromStreamFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, AssemblyLoader, FUNCTION_ASSEMBLY_LOADER_UNLOAD,
	                                       AssemblyLoaderUnloadFn)

	const auto HandleData = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_HANDLE_DATA, INTEROP_NAME);


	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, HandleData, FUNCTION_HANDLE_DATA_FREE,
	                                       HandleDataFreeFn)

	const auto LogBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_LOG_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, LogBridge, FUNCTION_LOG_BRIDGE_SET_LOG,
	                                       LogBridgeSetLogFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, LogBridge, FUNCTION_LOG_BRIDGE_INITIALIZE,
	                                       LogBridgeInitializeFn)

	const auto TypeBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_TYPE_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_CLASS,
	                                       TypeBridgeGetClassFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_TYPE,
	                                       TypeBridgeGetTypeFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_METHOD,
	                                       TypeBridgeGetMethodFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_FUNCTION_POINTER,
	                                       TypeBridgeGetFunctionPointerFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_NAMESPACE,
	                                       TypeBridgeGetNamespaceFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_NAME,
	                                       TypeBridgeGetNameFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_FULL_NAME,
	                                       TypeBridgeGetFullNameFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE,
	                                       TypeBridgeMakeGenericTypeFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE2,
	                                       TypeBridgeMakeGenericType2Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_BOOL,
	                                       TypeBridgeBoxBoolFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_SBYTE,
	                                       TypeBridgeBoxSByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT16,
	                                       TypeBridgeBoxInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT32,
	                                       TypeBridgeBoxInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT64,
	                                       TypeBridgeBoxInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_BYTE,
	                                       TypeBridgeBoxByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT16,
	                                       TypeBridgeBoxUInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT32,
	                                       TypeBridgeBoxUInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT64,
	                                       TypeBridgeBoxUInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_FLOAT,
	                                       TypeBridgeBoxFloatFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_DOUBLE,
	                                       TypeBridgeBoxDoubleFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_BOOL,
	                                       TypeBridgeUnboxBoolFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_SBYTE,
	                                       TypeBridgeUnboxSByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT16,
	                                       TypeBridgeUnboxInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT32,
	                                       TypeBridgeUnboxInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT64,
	                                       TypeBridgeUnboxInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_BYTE,
	                                       TypeBridgeUnboxByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT16,
	                                       TypeBridgeUnboxUInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT32,
	                                       TypeBridgeUnboxUInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT64,
	                                       TypeBridgeUnboxUInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_FLOAT,
	                                       TypeBridgeUnboxFloatFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_DOUBLE,
	                                       TypeBridgeUnboxDoubleFn)

	const auto ObjectBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_OBJECT_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ObjectBridge, FUNCTION_OBJECT_BRIDGE_NEW_OBJECT,
	                                       ObjectBridgeNewObjectFn)

	const auto FieldBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_FIELD_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, FieldBridge, FUNCTION_FIELD_BRIDGE_SET_STATIC_VALUE,
	                                       FieldBridgeSetStaticValueFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, FieldBridge, FUNCTION_FIELD_BRIDGE_GET_STATIC_VALUE,
	                                       FieldBridgeGetStaticValueFn)

	const auto MethodBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_METHOD_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, MethodBridge, FUNCTION_METHOD_BRIDGE_REGISTER_BINDING,
	                                       MethodBridgeRegisterBindingFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, MethodBridge, FUNCTION_METHOD_BRIDGE_INVOKE,
	                                       MethodBridgeInvokeFn)

	const auto StringBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_STRING_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, StringBridge, FUNCTION_STRING_BRIDGE_NEW_STRING,
	                                       StringBridgeNewStringFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, StringBridge, FUNCTION_STRING_BRIDGE_GET_STRING,
	                                       StringBridgeGetStringFn)

	const auto ArrayBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_ARRAY_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_NEW,
	                                       ArrayBridgeNewArrayFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_GET,
	                                       ArrayBridgeArrayGetFn)
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
