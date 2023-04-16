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


MonoDomain* FMonoDomain::RootDomain = nullptr;
MonoAssembly* FMonoDomain::UtilAssembly = nullptr;
MonoImage* FMonoDomain::UtilImage = nullptr;

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

	if (RootDomain == nullptr)
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

		RootDomain = mono_jit_init("UnrealCSharp");
		mono_domain_set(RootDomain, false);
	}
	if (UtilAssembly == nullptr)
	{
		UtilAssembly = mono_domain_assembly_open(RootDomain, TCHAR_TO_ANSI(*Params.UtilPath));
		check(UtilAssembly);
	}
	if (UtilImage == nullptr)
	{
		UtilImage = mono_assembly_get_image(UtilAssembly);
		check(UtilImage);
	}
	InitAssemblayLoadContext();
	
	for (const auto& AssemblyPath : Params.Assemblies)
	{
		auto gchandle = LoadLibrary(TCHAR_TO_ANSI(*AssemblyPath));
		AssemblieHandles.Add(gchandle);
		auto ReflectionAssembly = (MonoReflectionAssembly*)mono_gchandle_get_target_v2(gchandle);
		auto Assembly = mono_reflection_assembly_get_assembly(ReflectionAssembly);
		Assemblies.Add(Assembly);
		Images.Add(mono_assembly_get_image(Assembly));
	}

	RegisterLog();

	RegisterBinding();
}

void FMonoDomain::Deinitialize()
{
	Images.Reset();

	for(auto image : Images)
	{
		mono_image_close(image);
	}
	for (auto handle : AssemblieHandles)
	{
		UnloadLibrary(handle);
	}
	Assemblies.Reset();
	AssemblieHandles.Reset();
	Images.Reset();
	UninitAssemblayLoadContext();

}



MonoGCHandle FMonoDomain::LoadLibrary(FString Path)
{
	static MonoMethod* LoadLibraryMethod = nullptr;
	if (UtilImage == nullptr)
		return nullptr;
	if (LoadLibraryMethod == nullptr)
	{
		auto* Class = mono_class_from_name(UtilImage, "Util", "AssemblyUtil");
		if (Class == nullptr)
			return nullptr;
		LoadLibraryMethod = mono_class_get_method_from_name(Class, "LoadLibrary", 1);
		
	};
	if (LoadLibraryMethod == nullptr)
		return nullptr;
	void* args[1];
	args[0] = (void*)mono_string_new(RootDomain, TCHAR_TO_ANSI(*Path));
	MonoObject* Result = mono_runtime_invoke(LoadLibraryMethod, nullptr, args, nullptr);
	if (Result == nullptr)
		return nullptr;
	MonoGCHandle Handle = mono_gchandle_new_v2(Result, true);
	return Handle;
}

void FMonoDomain::UnloadLibrary(MonoGCHandle GCHandle)
{
	mono_gchandle_free_v2(GCHandle);
}

void FMonoDomain::InitAssemblayLoadContext()
{
	static MonoMethod* InitAlcMethod = nullptr;
	if (InitAlcMethod == nullptr)
	{
		auto* Class = mono_class_from_name(UtilImage, "Util", "AssemblyUtil");
		if (Class == nullptr)
			return;
		InitAlcMethod = mono_class_get_method_from_name(Class, "InitAssemblyLoadContext", 0);
	}
	if (InitAlcMethod == nullptr)
		return;
	mono_runtime_invoke(InitAlcMethod, nullptr, nullptr, nullptr);
}
void FMonoDomain::UninitAssemblayLoadContext()
{
	
	static MonoMethod* UninitAlcMethod = nullptr;
	if (UninitAlcMethod == nullptr)
	{
		auto* Class = mono_class_from_name(UtilImage, "Util", "AssemblyUtil");
		if (Class == nullptr)
			return;
		UninitAlcMethod = mono_class_get_method_from_name(Class, "UninitAssemblyLoadContext", 0);
	}
	if (UninitAlcMethod == nullptr)
		return;
	mono_runtime_invoke(UninitAlcMethod, nullptr, nullptr, nullptr);
}

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass) const
{
	if (RootDomain != nullptr && InMonoClass != nullptr)
	{
		if (const auto NewMonoObject = mono_object_new(RootDomain, InMonoClass))
		{
			Runtime_Object_Init(NewMonoObject);

			return NewMonoObject;
		}
	}

	return nullptr;
}

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass, const int32 InParamCount, void** InParams) const
{
	if (RootDomain != nullptr && InMonoClass != nullptr)
	{
		if (const auto NewMonoObject = mono_object_new(RootDomain, InMonoClass))
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
	return RootDomain != nullptr && InMonoType != nullptr ? mono_type_get_object(RootDomain, InMonoType) : nullptr;
}

MonoType* FMonoDomain::Type_Get_Underlying_Type(MonoType* InMonoType) const
{
	return mono_type_get_underlying_type(InMonoType);
}

MonoReflectionMethod* FMonoDomain::Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass)
{
	return RootDomain != nullptr && InMethod != nullptr && InMonoClass != nullptr
		       ? mono_method_get_object(RootDomain, InMethod, InMonoClass)
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
	return RootDomain != nullptr && InMonoClass != nullptr ? mono_value_box(RootDomain, InMonoClass, InValue) : nullptr;
}

void* FMonoDomain::Object_Unbox(MonoObject* InMonoObject) const
{
	return InMonoObject != nullptr ? mono_object_unbox(InMonoObject) : nullptr;
}

MonoString* FMonoDomain::String_New(const char* InText) const
{
	return RootDomain != nullptr && InText != nullptr ? mono_string_new(RootDomain, InText) : nullptr;
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
	return mono_array_new(RootDomain, InMonoClass, InNum);
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

void FMonoDomain::RegisterMonoTrace()
{
	mono_trace_set_log_handler(FMonoLog::MonoLog, nullptr);

	mono_trace_set_print_handler(FMonoLog::MonoPrintf);

	mono_trace_set_printerr_handler(FMonoLog::MonoPrintfError);
}

void FMonoDomain::RegisterLog()
{
	if (RootDomain != nullptr)
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
