#include "Domain/Mono/FMonoDomain.h"
#if WITH_MONO
#include "Misc/FileHelper.h"
#include "Domain/Mono/FMonoFunctionLibrary.h"
#include "Domain/Mono/FMonoLog.h"
#include "Domain/Script/FScriptLog.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Template/TGetArrayLength.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Binding/FBinding.h"
#include "Setting/UnrealCSharpSetting.h"
#include "Reflection/FReflectionRegistry.h"
#include "Reflection/FClassReflection.h"
#include "Reflection/FMethodReflection.h"
#include "mono/metadata/object.h"
#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/utils/mono-logger.h"
#include "mono/metadata/mono-debug.h"
#include "mono/metadata/class.h"
#include "mono/metadata/reflection.h"
#include "DotnetVersion.h"
#include "mono/jit/mono-private-unstable.h"
#include "mono/metadata/mono-private-unstable.h"
#include "mono/utils/mono-error.h"
#if UE_TRACE_ENABLED
#include "Domain/Mono/FMonoProfiler.h"
#endif

#define GET_METHOD_AND_GET_FUNCTION_POINTER(InFn, InManagedClass, InName, InParamCount) \
	if (const auto Method = Class_Get_Method_From_Name(InManagedClass, InName, InParamCount); \
		Method != nullptr) \
	{ \
		InFn = reinterpret_cast<decltype(InFn)>(Method_Get_Unmanaged_Callers_Only_Ftnptr(Method)); \
	}

PRAGMA_DISABLE_DANGLING_WARNINGS

MonoDomain* FMonoDomain::Domain{};

#if PLATFORM_IOS
extern void* mono_aot_module_System_Private_CoreLib_info;
#endif

void FMonoDomain::Initialize()
{
	RegisterMonoTrace();

	RegisterAssemblyPreloadHook();

	if (Domain == nullptr)
	{
#if PLATFORM_IOS
		mono_jit_set_aot_mode(MONO_AOT_MODE_INTERP);

		mono_aot_register_module(static_cast<void**>(mono_aot_module_System_Private_CoreLib_info));

#if !DOTNET9
		mono_dllmap_insert(NULL, "System.Native", NULL, "__Internal", NULL);

		mono_dllmap_insert(NULL, "System.Net.Security.Native", NULL, "__Internal", NULL);

		mono_dllmap_insert(NULL, "System.IO.Compression.Native", NULL, "__Internal", NULL);

		mono_dllmap_insert(NULL, "System.Security.Cryptography.Native.Apple", NULL, "__Internal", NULL);

#if DOTNET8
		mono_dllmap_insert(NULL, "System.Globalization.Native", NULL, "__Internal", NULL);
#endif
#endif

		setenv("DOTNET_SYSTEM_GLOBALIZATION_INVARIANT", "1", TRUE);
#else
#if DOTNET9
#if PLATFORM_WINDOWS
		const auto LibDirectory = FMonoFunctionLibrary::GetLibDirectory();

		const char* PropertyKeys[] = {
			"NATIVE_DLL_SEARCH_DIRECTORIES"
		};
		const char* PropertyValues[] = {
			TCHAR_TO_ANSI(*LibDirectory),
		};

		monovm_initialize(std::size(PropertyKeys), PropertyKeys, PropertyValues);
#endif

#if PLATFORM_LINUX
		setenv ("DOTNET_SYSTEM_GLOBALIZATION_INVARIANT", "1", 1);
#endif
#endif

		mono_jit_set_aot_mode(MONO_AOT_MODE_NONE);
#endif

		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
			if (UnrealCSharpSetting->IsEnableDebug())
			{
				const auto Config = FString::Printf(TEXT(
					"--debugger-agent=transport=dt_socket,server=y,suspend=n,address=%s:%d"
				),
				                                    *UnrealCSharpSetting->GetHost(),
				                                    UnrealCSharpSetting->GetPort()
				);

				char* Options[] = {
					TCHAR_TO_ANSI(TEXT("--soft-breakpoints")),
					TCHAR_TO_ANSI(*Config)
				};

				mono_jit_parse_options(sizeof(Options) / sizeof(char*), Options);
			}
		}

		mono_debug_init(MONO_DEBUG_FORMAT_MONO);

		Domain = mono_jit_init("UnrealCSharp");

		mono_domain_set(Domain, false);

		RegisterProfiler();
	}

	RegisterInterop(FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath());

	RegisterLog();

	InitializeAssembly(FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath());
}

void FMonoDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
	LoadAssembly(InAssemblies);

	if (!bIsInitialized)
	{
		return;
	}

	UtilsGetClassReflectionFn = reinterpret_cast<decltype(UtilsGetClassReflectionFn)>(
		TypeBridgeGetFunctionPointerFn(
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*FUnrealCSharpFunctionLibrary::GetUEName()).Get()),
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(
				*COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS)).Get()),
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*FUNCTION_UTILS_GET_CLASS_REFLECTION).Get())));

	RegisterSynchronizationContextTick();

	FReflectionRegistry::Get().Initialize();

	RegisterBinding();
}

void FMonoDomain::Deinitialize()
{
	if (!bIsInitialized)
	{
		return;
	}

	bIsInitialized = false;

	UnloadAssembly();
}

#define SCRIPT_DOMAIN_TYPE FMonoDomain
#include "Domain/Script/FScriptDomainImpl.inl"
#undef SCRIPT_DOMAIN_TYPE

MonoObject* FMonoDomain::Object_New(MonoClass* InManagedClass)
{
	return Domain != nullptr && InManagedClass != nullptr
		       ? mono_object_new(Domain, InManagedClass)
		       : nullptr;
}

MonoObject* FMonoDomain::Value_Box(MonoClass* InManagedClass, void* InValue)
{
	return Domain != nullptr && InManagedClass != nullptr
		       ? mono_value_box(Domain, InManagedClass, InValue)
		       : nullptr;
}

MonoString* FMonoDomain::String_New(const char* InText)
{
	return Domain != nullptr && InText != nullptr ? mono_string_new(Domain, InText) : nullptr;
}

MonoMethod* FMonoDomain::Class_Get_Method_From_Name(MonoClass* InManagedClass, const FString& InName,
                                                    const int32 InParamCount)
{
	return InManagedClass != nullptr
		       ? mono_class_get_method_from_name(InManagedClass, TCHAR_TO_ANSI(*InName), InParamCount)
		       : nullptr;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InManagedMethod, MonoObject* InManagedObject,
                                        void** InParams)
{
	MonoObject* Exception{};

	const auto ReturnValue = Runtime_Invoke(InManagedMethod, InManagedObject, InParams, &Exception);

	if (Exception != nullptr)
	{
		Unhandled_Exception(Exception);

		return nullptr;
	}

	return ReturnValue;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InManagedMethod, MonoObject* InManagedObject,
                                        void** InParams, MonoObject** InExc)
{
	return InManagedMethod != nullptr
		       ? mono_runtime_invoke(InManagedMethod, InManagedObject, InParams, InExc)
		       : nullptr;
}

void FMonoDomain::Unhandled_Exception(MonoObject* InManagedObject)
{
	mono_unhandled_exception(InManagedObject);
}

void FMonoDomain::Free(void* InPointer)
{
	if (InPointer != nullptr)
	{
		mono_free(InPointer);
	}
}

void* FMonoDomain::Method_Get_Unmanaged_Callers_Only_Ftnptr(MonoMethod* InManagedMethod)
{
	MonoError Error;

	Error.init = 0;

	return mono_method_get_unmanaged_callers_only_ftnptr(InManagedMethod, &Error);
}

MonoObject* FMonoDomain::Object_Init(MonoClass* InManagedClass, const int32 InParamCount, void** InParams)
{
	if (const auto Object = Object_New(InManagedClass); Object != nullptr)
	{
		Object_Constructor(Object, InParamCount, InParams);

		return Object;
	}

	return nullptr;
}

void FMonoDomain::Object_Constructor(MonoObject* InManagedObject, const int32 InParamCount, void** InParams)
{
	if (const auto FoundClass = mono_object_get_class(InManagedObject))
	{
		if (const auto FoundMethod = Class_Get_Method_From_Name(FoundClass, FUNCTION_OBJECT_CONSTRUCTOR,
		                                                        InParamCount))
		{
			Runtime_Invoke(FoundMethod, InManagedObject, InParams);
		}
	}
}

MonoMethod* FMonoDomain::Class_Get_Method_From_Params(MonoClass* InManagedClass, const FString& InName,
                                                      const TArray<MonoType*>& InParams)
{
	void* MethodIter{};

	while (const auto Method = mono_class_get_methods(InManagedClass, &MethodIter))
	{
		if (strcmp(mono_method_get_name(Method), TCHAR_TO_ANSI(*InName)))
		{
			continue;
		}

		const auto Signature = mono_method_signature(Method);

		if (mono_signature_get_param_count(Signature) != InParams.Num())
		{
			continue;
		}

		void* ParamIter{};

		auto Index = 0;

		auto bIsSame = true;

		while (const auto ParamType = mono_signature_get_params(Signature, &ParamIter))
		{
			if (strcmp(mono_type_get_name_full(ParamType, MONO_TYPE_NAME_FORMAT_FULL_NAME),
			           mono_type_get_name_full(InParams[Index], MONO_TYPE_NAME_FORMAT_FULL_NAME)))
			{
				bIsSame = false;

				break;
			}

			Index++;
		}

		if (bIsSame == true)
		{
			return Method;
		}
	}

	return nullptr;
}

MonoAssembly* FMonoDomain::AssemblyPreloadHook(MonoAssemblyName* InManagedAssemblyName,
                                               char** OutAssemblyPath, void* InUserData)
{
	auto AssemblyName = FString(mono_assembly_name_get_name(InManagedAssemblyName));

	if (AssemblyName == ASSEMBLY_CORE_LIB_RESOURCE_NAME)
	{
		AssemblyName = ASSEMBLY_CORE_LIB_NAME;
	}

	if (const auto AssemblyLoader = FMonoFunctionLibrary::GetAssemblyLoader())
	{
		if (const auto Data = AssemblyLoader->Load(AssemblyName);
			!Data.IsEmpty())
		{
			MonoAssembly* Assembly{};

			LoadAssembly(AssemblyName, Data, nullptr, &Assembly);

			return Assembly;
		}
	}

	return nullptr;
}

void FMonoDomain::LoadAssembly(const FString& InAssemblyName, const TArray<uint8>& InData, MonoImage** OutImage,
                               MonoAssembly** OutAssembly)
{
	auto ImageOpenStatus = MonoImageOpenStatus::MONO_IMAGE_OK;

	const auto Image = mono_image_open_from_data_with_name((char*)InData.GetData(), InData.Num(),
	                                                       true, &ImageOpenStatus,
	                                                       false, TCHAR_TO_UTF8(*InAssemblyName));

	if (ImageOpenStatus != MonoImageOpenStatus::MONO_IMAGE_OK)
	{
		// @TODO
		return;
	}

	const auto Assembly = mono_assembly_load_from_full(Image, TCHAR_TO_UTF8(*InAssemblyName), &ImageOpenStatus, false);

	if (ImageOpenStatus != MonoImageOpenStatus::MONO_IMAGE_OK)
	{
		// @TODO
		return;
	}

	if (OutImage != nullptr)
	{
		*OutImage = Image;
	}

	if (OutAssembly != nullptr)
	{
		*OutAssembly = Assembly;
	}
}

void FMonoDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
	if (AssemblyLoaderLoadFromStreamFn != nullptr)
	{
		Assemblies.Empty();

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

			TArray<uint8> Data;

			FFileHelper::LoadFileToArray(Data, *AssemblyPath);

			if (const auto Handle = AssemblyLoaderLoadFromStreamFn(Data.GetData(), Data.Num(),
			                                                       reinterpret_cast<const char16_t*>(*FPaths::GetPath(
				                                                       AssemblyPath)));
				IManagedHandleIsValid(Handle))
			{
				Assemblies.Add(Handle);
			}
		}

		bIsInitialized = true;
	}
}

void FMonoDomain::UnloadAssembly()
{
	FReflectionRegistry::Get().Deinitialize();

	if (AssemblyLoaderUnloadFn != nullptr)
	{
		AssemblyLoaderUnloadFn();
	}

	UtilsGetClassReflectionFn = nullptr;

	Assemblies.Empty();
}

void FMonoDomain::RegisterAssemblyPreloadHook()
{
	mono_install_assembly_preload_hook(AssemblyPreloadHook, nullptr);
}

void FMonoDomain::RegisterMonoTrace()
{
	mono_trace_set_log_handler(FMonoLog::Log, nullptr);

	mono_trace_set_print_handler(FMonoLog::Printf);

	mono_trace_set_printerr_handler(FMonoLog::PrintfError);
}

void FMonoDomain::RegisterInterop(const FString& InAssembly)
{
	static MonoImage* Image{};

	if (Image == nullptr)
	{
		if (FPaths::FileExists(InAssembly))
		{
			TArray<uint8> Data;

			FFileHelper::LoadFileToArray(Data, *InAssembly);

			MonoAssembly* Assembly{};

			LoadAssembly(FPaths::GetBaseFilename(InAssembly), Data, &Image, &Assembly);
		}
	}

	const auto GetClass = [](const FString& InNameSpace, const FString& InName) -> MonoClass*
	{
		return Image != nullptr
			       ? mono_class_from_name(Image, TCHAR_TO_ANSI(*InNameSpace), TCHAR_TO_ANSI(*InName))
			       : nullptr;
	};

	const auto AssemblyLoader = GetClass(NAMESPACE_INTEROP, CLASS_ASSEMBLY_LOADER);

	GET_METHOD_AND_GET_FUNCTION_POINTER(AssemblyLoaderLoadFromStreamFn, AssemblyLoader,
	                                    FUNCTION_ASSEMBLY_LOADER_LOAD_FROM_STREAM, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(AssemblyLoaderUnloadFn, AssemblyLoader, FUNCTION_ASSEMBLY_LOADER_UNLOAD, 0)

	const auto HandleData = GetClass(NAMESPACE_INTEROP, CLASS_HANDLE_DATA);

	GET_METHOD_AND_GET_FUNCTION_POINTER(HandleDataFreeFn, HandleData, FUNCTION_HANDLE_DATA_FREE, 1)

	const auto LogBridge = GetClass(NAMESPACE_INTEROP, CLASS_LOG_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(LogBridgeSetLogFn, LogBridge, FUNCTION_LOG_BRIDGE_SET_LOG, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(LogBridgeInitializeFn, LogBridge, FUNCTION_LOG_BRIDGE_INITIALIZE, 0)

	const auto TypeBridge = GetClass(NAMESPACE_INTEROP, CLASS_TYPE_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetClassFn, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_CLASS, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetTypeFn, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_TYPE, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetMethodFn, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_METHOD, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetFunctionPointerFn, TypeBridge,
	                                    FUNCTION_TYPE_BRIDGE_GET_FUNCTION_POINTER, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetNamespaceFn, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_NAMESPACE, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetNameFn, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_NAME, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeGetFullNameFn, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_FULL_NAME, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeMakeGenericTypeFn, TypeBridge, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE,
	                                    2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeMakeGenericType2Fn, TypeBridge,
	                                    FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE2, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxBoolFn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_BOOL, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxSByteFn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_SBYTE, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxInt16Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT16, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxInt32Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT32, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxInt64Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT64, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxByteFn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_BYTE, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxUInt16Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT16, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxUInt32Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT32, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxUInt64Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT64, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxFloatFn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_FLOAT, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeBoxDoubleFn, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_DOUBLE, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxBoolFn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_BOOL, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxSByteFn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_SBYTE, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxInt16Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT16, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxInt32Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT32, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxInt64Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT64, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxByteFn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_BYTE, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxUInt16Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT16, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxUInt32Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT32, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxUInt64Fn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT64, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxFloatFn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_FLOAT, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(TypeBridgeUnboxDoubleFn, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_DOUBLE, 2)

	const auto ObjectBridge = GetClass(NAMESPACE_INTEROP, CLASS_OBJECT_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(ObjectBridgeNewObjectFn, ObjectBridge, FUNCTION_OBJECT_BRIDGE_NEW_OBJECT, 1)

	const auto FieldBridge = GetClass(NAMESPACE_INTEROP, CLASS_FIELD_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(FieldBridgeSetStaticValueFn, FieldBridge,
	                                    FUNCTION_FIELD_BRIDGE_SET_STATIC_VALUE, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(FieldBridgeGetStaticValueFn, FieldBridge,
	                                    FUNCTION_FIELD_BRIDGE_GET_STATIC_VALUE, 2)

	const auto MethodBridge = GetClass(NAMESPACE_INTEROP, CLASS_METHOD_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(MethodBridgeRegisterBindingFn, MethodBridge,
	                                    FUNCTION_METHOD_BRIDGE_REGISTER_BINDING, 3)

	GET_METHOD_AND_GET_FUNCTION_POINTER(MethodBridgeInvokeFn, MethodBridge, FUNCTION_METHOD_BRIDGE_INVOKE, 4)

	const auto StringBridge = GetClass(NAMESPACE_INTEROP, CLASS_STRING_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(StringBridgeNewStringFn, StringBridge, FUNCTION_STRING_BRIDGE_NEW_STRING, 1)

	GET_METHOD_AND_GET_FUNCTION_POINTER(StringBridgeGetStringFn, StringBridge, FUNCTION_STRING_BRIDGE_GET_STRING, 3)

	const auto ArrayBridge = GetClass(NAMESPACE_INTEROP, CLASS_ARRAY_BRIDGE);

	GET_METHOD_AND_GET_FUNCTION_POINTER(ArrayBridgeNewArrayFn, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_NEW, 2)

	GET_METHOD_AND_GET_FUNCTION_POINTER(ArrayBridgeArrayGetFn, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_GET, 2)
}

void FMonoDomain::RegisterProfiler()
{
#if UE_TRACE_ENABLED
	FMonoProfiler::Register();
#endif
}

PRAGMA_ENABLE_DANGLING_WARNINGS
#endif
