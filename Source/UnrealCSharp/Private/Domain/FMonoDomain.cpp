#include "Domain/FMonoDomain.h"
#include "Binding/FBinding.h"
#include "Domain/InternalCall/FMonoInternalCall.h"
#include "Log/FMonoLog.h"
#include "Macro/NamespaceMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/utils/mono-logger.h"
#include "mono/metadata/mono-gc.h"
#include "mono/metadata/mono-debug.h"
#include "mono/metadata/class.h"
#include "mono/metadata/reflection.h"
#include "Template/TGetArrayLength.h"

MonoDomain* FMonoDomain::Domain = nullptr;

MonoAssembly* FMonoDomain::AssemblyUtilAssembly = nullptr;

MonoImage* FMonoDomain::AssemblyUtilImage = nullptr;

FMonoDomain::FMonoDomain(const FMonoDomainInitializeParams& Params)
{
	Initialize(Params);
}

FMonoDomain::~FMonoDomain()
{
	Deinitialize();
}

void FMonoDomain::Initialize(const FMonoDomainInitializeParams& Params)
{
	RegisterMonoTrace();

	if (Domain == nullptr)
	{
#if WITH_EDITOR
		auto MonoDir = FString::Printf(TEXT(
			"%s/Binaries/%s"),
		                               *FPaths::ProjectDir(),
#if PLATFORM_WINDOWS
		                               TEXT("Win64")
#endif
		);

		mono_set_dirs(TCHAR_TO_ANSI(*FPaths::Combine(MonoDir, TEXT("Mono\\lib\\net7.0"))),
		              TCHAR_TO_ANSI(*FPaths::Combine(MonoDir, TEXT(""))));
#else
		mono_set_dirs("Mono\\lib\\net7.0", "");
#endif

		mono_debug_init(MONO_DEBUG_FORMAT_MONO);

		Domain = mono_jit_init("UnrealCSharp");

		mono_domain_set(Domain, false);
	}

	if (AssemblyUtilAssembly == nullptr)
	{
		AssemblyUtilAssembly = mono_domain_assembly_open(Domain, TCHAR_TO_ANSI(*Params.AssemblyUtil));
	}

	if (AssemblyUtilImage == nullptr)
	{
		AssemblyUtilImage = mono_assembly_get_image(AssemblyUtilAssembly);
	}

	InitializeAssembly(Params.Assemblies);

	RegisterLog();

	RegisterBinding();

	RegisterSyncContext();
}

void FMonoDomain::Deinitialize()
{
	UnregisterSyncContext();

	UnloadAssembly();

	DeinitializeAssembly();

}

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass) const
{
	if (Domain != nullptr && InMonoClass != nullptr)
	{
		if (const auto NewMonoObject = mono_object_new(Domain, InMonoClass))
		{
			Runtime_Object_Init(NewMonoObject);

			return NewMonoObject;
		}
	}

	return nullptr;
}

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass, const int32 InParamCount, void** InParams) const
{
	if (Domain != nullptr && InMonoClass != nullptr)
	{
		if (const auto NewMonoObject = mono_object_new(Domain, InMonoClass))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(InMonoClass, FUNCTION_OBJECT_CONSTRUCTOR,
			                                                        InParamCount))
			{
				Runtime_Invoke(FoundMethod, NewMonoObject, InParams);

				return NewMonoObject;
			}

			// @TODO
		}
	}

	return nullptr;
}

void FMonoDomain::Runtime_Object_Init(MonoObject* InMonoObject) const
{
	if (InMonoObject != nullptr)
	{
		mono_runtime_object_init(InMonoObject);
	}
}

MonoClass* FMonoDomain::Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const
{
	for (const auto& Image : Images)
	{
		if (const auto& Class = mono_class_from_name(Image, TCHAR_TO_ANSI(*InNameSpace),
		                                             TCHAR_TO_ANSI(*InMonoClassName)))
		{
			return Class;
		}
	}

	return nullptr;
}

MonoMethod* FMonoDomain::Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                    const int32 InParamCount) const
{
	if (InMonoClass == nullptr)
	{
		return nullptr;
	}

	return mono_class_get_method_from_name(InMonoClass, TCHAR_TO_ANSI(*InFunctionName), InParamCount);
}

mono_bool FMonoDomain::Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
                                            mono_bool bCheckInterfaces)
{
	return InMonoClass != nullptr && InSuperMonoClass != nullptr
		       ? mono_class_is_subclass_of(InMonoClass, InSuperMonoClass, bCheckInterfaces)
		       : false;
}

MonoType* FMonoDomain::Class_Get_Type(MonoClass* InMonoClass) const
{
	return InMonoClass != nullptr ? mono_class_get_type(InMonoClass) : nullptr;
}

MonoType* FMonoDomain::Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType)
{
	return InMonoReflectionType != nullptr ? mono_reflection_type_get_type(InMonoReflectionType) : nullptr;
}

MonoClass* FMonoDomain::Type_Get_Class(MonoType* InMonoType)
{
	return InMonoType != nullptr ? mono_type_get_class(InMonoType) : nullptr;
}

MonoReflectionType* FMonoDomain::Type_Get_Object(MonoType* InMonoType)
{
	return Domain != nullptr && InMonoType != nullptr ? mono_type_get_object(Domain, InMonoType) : nullptr;
}

MonoType* FMonoDomain::Type_Get_Underlying_Type(MonoType* InMonoType) const
{
	return mono_type_get_underlying_type(InMonoType);
}

MonoReflectionMethod* FMonoDomain::Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass)
{
	return Domain != nullptr && InMethod != nullptr && InMonoClass != nullptr
		       ? mono_method_get_object(Domain, InMethod, InMonoClass)
		       : nullptr;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams) const
{
	MonoObject* Exception = nullptr;

	const auto ReturnValue = Runtime_Invoke(InFunction, InMonoObject, InParams, &Exception);

	if (Exception != nullptr)
	{
		Unhandled_Exception(Exception);

		return nullptr;
	}

	return ReturnValue;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams,
                                        MonoObject** InExc) const
{
	return InFunction != nullptr ? mono_runtime_invoke(InFunction, InMonoObject, InParams, InExc) : nullptr;
}

MonoObject* FMonoDomain::Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams)
{
	MonoObject* Exception = nullptr;

	const auto ReturnValue = Runtime_Delegate_Invoke(InDelegate, InParams, &Exception);

	if (Exception != nullptr)
	{
		Unhandled_Exception(Exception);

		return nullptr;
	}

	return ReturnValue;
}

MonoObject* FMonoDomain::Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc)
{
	return InDelegate != nullptr ? mono_runtime_delegate_invoke(InDelegate, InParams, InExc) : nullptr;
}

void FMonoDomain::Unhandled_Exception(MonoObject* InException) const
{
	mono_unhandled_exception(InException);
}

MonoClass* FMonoDomain::Object_Get_Class(MonoObject* InMonoObject)
{
	return InMonoObject != nullptr ? mono_object_get_class(InMonoObject) : nullptr;
}

MonoObject* FMonoDomain::Value_Box(MonoClass* InMonoClass, void* InValue) const
{
	return Domain != nullptr && InMonoClass != nullptr ? mono_value_box(Domain, InMonoClass, InValue) : nullptr;
}

void* FMonoDomain::Object_Unbox(MonoObject* InMonoObject) const
{
	return InMonoObject != nullptr ? mono_object_unbox(InMonoObject) : nullptr;
}

MonoString* FMonoDomain::String_New(const char* InText) const
{
	return Domain != nullptr && InText != nullptr ? mono_string_new(Domain, InText) : nullptr;
}

MonoString* FMonoDomain::Object_To_String(MonoObject* InMonoObject, MonoObject** InExc) const
{
	return InMonoObject != nullptr ? mono_object_to_string(InMonoObject, InExc) : nullptr;
}

char* FMonoDomain::String_To_UTF8(MonoString* InMonoString) const
{
	return InMonoString != nullptr ? mono_string_to_utf8(InMonoString) : nullptr;
}

MonoArray* FMonoDomain::Array_New(MonoClass* InMonoClass, const uint32 InNum)
{
	return mono_array_new(Domain, InMonoClass, InNum);
}

MonoClass* FMonoDomain::Get_Byte_Class() const
{
	return mono_get_byte_class();
}

MonoClass* FMonoDomain::Get_Object_Class() const
{
	return mono_get_object_class();
}

MonoClass* FMonoDomain::Get_UInt16_Class() const
{
	return mono_get_uint16_class();
}

MonoClass* FMonoDomain::Get_UInt32_Class() const
{
	return mono_get_uint32_class();
}

MonoClass* FMonoDomain::Get_UInt64_Class() const
{
	return mono_get_uint64_class();
}

MonoClass* FMonoDomain::Get_Int16_Class() const
{
	return mono_get_int16_class();
}

MonoClass* FMonoDomain::Get_Int32_Class() const
{
	return mono_get_int32_class();
}

MonoClass* FMonoDomain::Get_Int64_Class() const
{
	return mono_get_int64_class();
}

MonoClass* FMonoDomain::Get_Boolean_Class() const
{
	return mono_get_boolean_class();
}

MonoClass* FMonoDomain::Get_Single_Class() const
{
	return mono_get_single_class();
}

MonoClass* FMonoDomain::Get_Enum_Class() const
{
	return mono_get_enum_class();
}

MonoClass* FMonoDomain::Get_Double_Class() const
{
	return mono_get_double_class();
}

uint32 FMonoDomain::GCHandle_New(MonoObject* InMonoObject, const mono_bool bPinned)
{
	return mono_gchandle_new(InMonoObject, bPinned);
}

uint32 FMonoDomain::GCHandle_New_WeakRef(MonoObject* InMonoObject, const mono_bool bTrackResurrection)
{
	return mono_gchandle_new_weakref(InMonoObject, bTrackResurrection);
}

MonoObject* FMonoDomain::GCHandle_Get_Target(const uint32 InGCHandle)
{
	return mono_gchandle_get_target(InGCHandle);
}

void FMonoDomain::GCHandle_Free(const uint32 InGCHandle)
{
	mono_gchandle_free(InGCHandle);
}

MonoMethod* FMonoDomain::Parent_Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                           const int32 InParamCount) const
{
	while (InMonoClass != nullptr)
	{
		if (const auto FoundMethod = Class_Get_Method_From_Name(InMonoClass, InFunctionName, InParamCount))
		{
			return FoundMethod;
		}

		InMonoClass = mono_class_get_parent(InMonoClass);
	}

	return nullptr;
}

MonoString* FMonoDomain::GetTraceback() const
{
	if (Domain != nullptr)
	{
		if (const auto FoundMonoClass = Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(FoundMonoClass, FUNCTION_UTILS_GET_TRACEBACK, 0))
			{
				return reinterpret_cast<MonoString*>(Runtime_Invoke(FoundMethod, nullptr, nullptr));
			}
		}
	}

	return nullptr;
}

void FMonoDomain::RegisterMonoTrace()
{
	mono_trace_set_log_handler(FMonoLog::MonoLog, nullptr);

	mono_trace_set_print_handler(FMonoLog::MonoPrintf);

	mono_trace_set_printerr_handler(FMonoLog::MonoPrintfError);
}

void FMonoDomain::RegisterLog()
{
	if (Domain != nullptr)
	{
		if (const auto FoundMonoClass = Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(FoundMonoClass, FUNCTION_UTILS_SET_OUT, 0))
			{
				Runtime_Invoke(FoundMethod, nullptr, nullptr);
			}
		}
	}
}

void FMonoDomain::RegisterBinding()
{
	for (const auto Binding : FBinding::Get().GetBinding())
	{
		FMonoInternalCall::RegisterInternalCall(TCHAR_TO_ANSI(*Binding.Key), Binding.Value);
	}
}


void FMonoDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
	InitializeAssemblyLoadContext();

	LoadAssembly(InAssemblies);
}

void FMonoDomain::DeinitializeAssembly()
{
	UnloadAssembly();

	DeinitializeAssemblyLoadContext();
}

void FMonoDomain::InitializeAssemblyLoadContext() const
{
	if (const auto AssemblyUtilMonoClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT),
	                                                            TCHAR_TO_ANSI(*CLASS_ASSEMBLY_UTIL)))
	{
		if (const auto InitializeMonoMethod = Class_Get_Method_From_Name(
			AssemblyUtilMonoClass, FUNCTION_ASSEMBLY_UTIL_INITIALIZE, 0))
		{
			Runtime_Invoke(InitializeMonoMethod, nullptr, nullptr, nullptr);
		}
	}
}

void FMonoDomain::DeinitializeAssemblyLoadContext()
{
	if (const auto AssemblyUtilMonoClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT),
	                                                            TCHAR_TO_ANSI(*CLASS_ASSEMBLY_UTIL)))
	{
		if (const auto DeinitializeMonoMethod = Class_Get_Method_From_Name(
			AssemblyUtilMonoClass, FUNCTION_ASSEMBLY_UTIL_DEINITIALIZE, 0))
		{
			Runtime_Invoke(DeinitializeMonoMethod, nullptr, nullptr, nullptr);
		}
	}
}

void FMonoDomain::RegisterSyncContext()
{
	const auto SyncContextClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT),TCHAR_TO_ANSI(*CLASS_SYNC_CONTEXT));
	if (SyncContextClass == nullptr)
		return;
	const auto InitSyncContextMethod = Class_Get_Method_From_Name(SyncContextClass, FUNCTION_UTILS_INIT_SYNC_CONTEXT, 0);
	if (InitSyncContextMethod == nullptr)
		return;
	Runtime_Invoke(InitSyncContextMethod, nullptr, nullptr, nullptr);

	
	TickHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda( [=](float deltaTime) -> bool
	{
		const auto SyncContextClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT), TCHAR_TO_ANSI(*CLASS_SYNC_CONTEXT));
		if (SyncContextClass == nullptr)
			return true;
		const auto TickMethod = Class_Get_Method_From_Name(SyncContextClass, FUNCTION_UTILS_FINI_GLOBAL_TICK, 0);
		if (TickMethod == nullptr)
			return true;
		Runtime_Invoke(TickMethod, nullptr, nullptr, nullptr);
		return true;
	}));
}


void FMonoDomain::UnregisterSyncContext() const
{
	FTicker::GetCoreTicker().RemoveTicker(TickHandle);
	const auto SyncContextClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT),TCHAR_TO_ANSI(*CLASS_SYNC_CONTEXT));
	if (SyncContextClass == nullptr)
	{
		return;
	}
	const auto FiniSyncContextMethod = Class_Get_Method_From_Name(SyncContextClass, FUNCTION_UTILS_FINI_SYNC_CONTEXT, 0);
	if (FiniSyncContextMethod == nullptr)
		return;
	Runtime_Invoke(FiniSyncContextMethod, nullptr, nullptr, nullptr);
}

void FMonoDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
	if (const auto AssemblyUtilMonoClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT),
	                                                            TCHAR_TO_ANSI(*CLASS_ASSEMBLY_UTIL)))
	{
		void* Params[1];

		if (const auto LoadMonoMethod = Class_Get_Method_From_Name(AssemblyUtilMonoClass, FUNCTION_ASSEMBLY_UTIL_LOAD,
		                                                           TGetArrayLength(Params)))
		{
			for (const auto& AssemblyPath : InAssemblies)
			{
				Params[0] = String_New(TCHAR_TO_ANSI(*AssemblyPath));

				if (auto Result = Runtime_Invoke(LoadMonoMethod, nullptr, Params, nullptr))
				{
					// @TODO
					auto GCHandle = mono_gchandle_new_v2(Result, true);

					AssemblyGCHandles.Add(GCHandle);

					// @TODO
					const auto ReflectionAssembly = (MonoReflectionAssembly*)mono_gchandle_get_target_v2(GCHandle);

					auto Assembly = mono_reflection_assembly_get_assembly(ReflectionAssembly);

					Assemblies.Add(Assembly);

					Images.Add(mono_assembly_get_image(Assembly));
				}
			}
		}
	}
}

void FMonoDomain::UnloadAssembly()
{
	for (const auto GCHandle : AssemblyGCHandles)
	{
		mono_gchandle_free_v2(GCHandle);
	}

	AssemblyGCHandles.Reset();

	for (const auto& Image : Images)
	{
		mono_image_close(Image);
	}

	Images.Reset();

	Assemblies.Reset();
}
