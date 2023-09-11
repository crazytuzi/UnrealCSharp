#include "Domain/FMonoDomain.h"
#include "Log/FMonoLog.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/Macro.h"
#include "Template/TGetArrayLength.inl"
#include "mono/metadata/object.h"
#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/utils/mono-logger.h"
#include "mono/metadata/mono-debug.h"
#include "mono/metadata/class.h"
#include "mono/metadata/reflection.h"
#include "Misc/FileHelper.h"
#include "Binding/FBinding.h"

MonoDomain* FMonoDomain::Domain = nullptr;

MonoAssembly* FMonoDomain::AssemblyUtilAssembly = nullptr;

MonoImage* FMonoDomain::AssemblyUtilImage = nullptr;

TArray<MonoGCHandle> FMonoDomain::AssemblyGCHandles;

TArray<MonoAssembly*> FMonoDomain::Assemblies;

TArray<MonoImage*> FMonoDomain::Images;

bool FMonoDomain::bLoadSucceed;

void FMonoDomain::Initialize(const FMonoDomainInitializeParams& InParams)
{
	RegisterMonoTrace();

	RegisterAssemblyPreloadHook();

#if WITH_EDITOR
	if (!FPaths::FileExists(InParams.AssemblyUtil))
	{
		return;
	}
#endif

	if (Domain == nullptr)
	{
		mono_debug_init(MONO_DEBUG_FORMAT_MONO);

		Domain = mono_jit_init("UnrealCSharp");

		mono_domain_set(Domain, false);
	}

#if WITH_EDITOR
	LoadAssembly(TCHAR_TO_ANSI(*FPaths::GetBaseFilename(InParams.AssemblyUtil)), InParams.AssemblyUtil,
	             &AssemblyUtilImage, &AssemblyUtilAssembly);
#endif

	InitializeAssembly(InParams.Assemblies);

	RegisterLog();

	RegisterBinding();
}

void FMonoDomain::Deinitialize()
{
	UnloadAssembly();

	DeinitializeAssembly();
}

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass)
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

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass, const int32 InParamCount, void** InParams)
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

void FMonoDomain::Runtime_Object_Init(MonoObject* InMonoObject)
{
	if (InMonoObject != nullptr)
	{
		mono_runtime_object_init(InMonoObject);
	}
}

MonoClass* FMonoDomain::Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName)
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
                                                    const int32 InParamCount)
{
	if (InMonoClass == nullptr)
	{
		return nullptr;
	}

	return mono_class_get_method_from_name(InMonoClass, TCHAR_TO_ANSI(*InFunctionName), InParamCount);
}

mono_bool FMonoDomain::Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
                                            const mono_bool bCheckInterfaces)
{
	return InMonoClass != nullptr && InSuperMonoClass != nullptr
		       ? mono_class_is_subclass_of(InMonoClass, InSuperMonoClass, bCheckInterfaces)
		       : false;
}

const char* FMonoDomain::Class_Get_Name(MonoClass* InMonoClass)
{
	return InMonoClass != nullptr ? mono_class_get_name(InMonoClass) : nullptr;
}

MonoClass* FMonoDomain::Class_Get_Parent(MonoClass* InMonoClass)
{
	return InMonoClass != nullptr ? mono_class_get_parent(InMonoClass) : nullptr;
}

MonoType* FMonoDomain::Class_Get_Type(MonoClass* InMonoClass)
{
	return InMonoClass != nullptr ? mono_class_get_type(InMonoClass) : nullptr;
}

MonoClassField* FMonoDomain::Class_Get_Fields(MonoClass* InMonoClass, void** InIterator)
{
	return InMonoClass != nullptr ? mono_class_get_fields(InMonoClass, InIterator) : nullptr;
}

MonoProperty* FMonoDomain::Class_Get_Properties(MonoClass* InMonoClass, void** InIterator)
{
	return InMonoClass != nullptr ? mono_class_get_properties(InMonoClass, InIterator) : nullptr;
}

MonoMethod* FMonoDomain::Class_Get_Methods(MonoClass* InMonoClass, void** InIterator)
{
	return InMonoClass != nullptr ? mono_class_get_methods(InMonoClass, InIterator) : nullptr;
}

MonoCustomAttrInfo* FMonoDomain::Custom_Attrs_From_Class(MonoClass* InMonoClass)
{
	return InMonoClass != nullptr ? mono_custom_attrs_from_class(InMonoClass) : nullptr;
}

MonoCustomAttrInfo* FMonoDomain::Custom_Attrs_From_Field(MonoClass* InMonoClass, MonoClassField* InMonoClassField)
{
	return InMonoClass != nullptr && InMonoClassField != nullptr
		       ? mono_custom_attrs_from_field(InMonoClass, InMonoClassField)
		       : nullptr;
}

MonoCustomAttrInfo* FMonoDomain::Custom_Attrs_From_Property(MonoClass* InMonoClass, MonoProperty* InMonoProperty)
{
	return InMonoClass != nullptr && InMonoProperty != nullptr
		       ? mono_custom_attrs_from_property(InMonoClass, InMonoProperty)
		       : nullptr;
}

MonoCustomAttrInfo* FMonoDomain::Custom_Attrs_From_Method(MonoMethod* InMonoMethod)
{
	return InMonoMethod != nullptr ? mono_custom_attrs_from_method(InMonoMethod) : nullptr;
}

mono_bool FMonoDomain::Custom_Attrs_Has_Attr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass)
{
	return InMonoCustomAttrInfo != nullptr && InMonoClass != nullptr
		       ? mono_custom_attrs_has_attr(InMonoCustomAttrInfo, InMonoClass)
		       : false;
}

const char* FMonoDomain::Field_Get_Name(MonoClassField* InMonoClassField)
{
	return InMonoClassField != nullptr ? mono_field_get_name(InMonoClassField) : nullptr;
}

MonoType* FMonoDomain::Field_Get_Type(MonoClassField* InMonoClassField)
{
	return InMonoClassField != nullptr ? mono_field_get_type(InMonoClassField) : nullptr;
}

MonoObject* FMonoDomain::Field_Get_Value_Object(MonoDomain* InMonoDomain, MonoClassField* InMonoClassField,
                                                MonoObject* InMonoObject)
{
	return InMonoDomain != nullptr && InMonoClassField != nullptr && InMonoObject != nullptr
		       ? mono_field_get_value_object(InMonoDomain, InMonoClassField, InMonoObject)
		       : nullptr;
}

const char* FMonoDomain::Property_Get_Name(MonoProperty* InMonoProperty)
{
	return InMonoProperty != nullptr ? mono_property_get_name(InMonoProperty) : nullptr;
}

MonoMethod* FMonoDomain::Property_Get_Get_Method(MonoProperty* InMonoProperty)
{
	return InMonoProperty != nullptr ? mono_property_get_get_method(InMonoProperty) : nullptr;
}

const char* FMonoDomain::Method_Get_Name(MonoMethod* InMonoMethod)
{
	return InMonoMethod != nullptr ? mono_method_get_name(InMonoMethod) : nullptr;
}

void FMonoDomain::Method_Get_Param_Names(MonoMethod* InMonoMethod, const char** InNames)
{
	if (InMonoMethod != nullptr)
	{
		mono_method_get_param_names(InMonoMethod, InNames);
	}
}

MonoMethodSignature* FMonoDomain::Method_Signature(MonoMethod* InMonoMethod)
{
	return InMonoMethod != nullptr ? mono_method_signature(InMonoMethod) : nullptr;
}

uint32_t FMonoDomain::Signature_Get_Param_Count(MonoMethodSignature* InMonoMethodSignature)
{
	return InMonoMethodSignature != nullptr ? mono_signature_get_param_count(InMonoMethodSignature) : 0u;
}

MonoType* FMonoDomain::Signature_Get_Params(MonoMethodSignature* InMonoMethodSignature, void** InIterator)
{
	return InMonoMethodSignature != nullptr ? mono_signature_get_params(InMonoMethodSignature, InIterator) : nullptr;
}

MonoType* FMonoDomain::Signature_Get_Return_Type(MonoMethodSignature* InMonoMethodSignature)
{
	return InMonoMethodSignature != nullptr ? mono_signature_get_return_type(InMonoMethodSignature) : nullptr;
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

MonoType* FMonoDomain::Type_Get_Underlying_Type(MonoType* InMonoType)
{
	return mono_type_get_underlying_type(InMonoType);
}

mono_bool FMonoDomain::Type_Is_ByRef(MonoType* InMonoType)
{
	return mono_type_is_byref(InMonoType);
}

MonoReflectionMethod* FMonoDomain::Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass)
{
	return Domain != nullptr && InMethod != nullptr && InMonoClass != nullptr
		       ? mono_method_get_object(Domain, InMethod, InMonoClass)
		       : nullptr;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams)
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
                                        MonoObject** InExc)
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

void FMonoDomain::Unhandled_Exception(MonoObject* InException)
{
	mono_unhandled_exception(InException);
}

MonoClass* FMonoDomain::Object_Get_Class(MonoObject* InMonoObject)
{
	return InMonoObject != nullptr ? mono_object_get_class(InMonoObject) : nullptr;
}

MonoObject* FMonoDomain::Value_Box(MonoClass* InMonoClass, void* InValue)
{
	return Domain != nullptr && InMonoClass != nullptr ? mono_value_box(Domain, InMonoClass, InValue) : nullptr;
}

void* FMonoDomain::Object_Unbox(MonoObject* InMonoObject)
{
	return InMonoObject != nullptr ? mono_object_unbox(InMonoObject) : nullptr;
}

MonoString* FMonoDomain::String_New(const char* InText)
{
	return Domain != nullptr && InText != nullptr ? mono_string_new(Domain, InText) : nullptr;
}

MonoString* FMonoDomain::Object_To_String(MonoObject* InMonoObject, MonoObject** InExc)
{
	return InMonoObject != nullptr ? mono_object_to_string(InMonoObject, InExc) : nullptr;
}

char* FMonoDomain::String_To_UTF8(MonoString* InMonoString)
{
	return InMonoString != nullptr ? mono_string_to_utf8(InMonoString) : nullptr;
}

MonoArray* FMonoDomain::Array_New(MonoClass* InMonoClass, const uint32 InNum)
{
	return mono_array_new(Domain, InMonoClass, InNum);
}

uint64 FMonoDomain::Array_Length(MonoArray* InMonoArray)
{
	return InMonoArray != nullptr ? mono_array_length(InMonoArray) : 0u;
}

MonoClass* FMonoDomain::Get_Byte_Class()
{
	return mono_get_byte_class();
}

MonoClass* FMonoDomain::Get_Object_Class()
{
	return mono_get_object_class();
}

MonoClass* FMonoDomain::Get_UInt16_Class()
{
	return mono_get_uint16_class();
}

MonoClass* FMonoDomain::Get_UInt32_Class()
{
	return mono_get_uint32_class();
}

MonoClass* FMonoDomain::Get_UInt64_Class()
{
	return mono_get_uint64_class();
}

MonoClass* FMonoDomain::Get_SByte_Class()
{
	return mono_get_sbyte_class();
}

MonoClass* FMonoDomain::Get_Int16_Class()
{
	return mono_get_int16_class();
}

MonoClass* FMonoDomain::Get_Int32_Class()
{
	return mono_get_int32_class();
}

MonoClass* FMonoDomain::Get_Int64_Class()
{
	return mono_get_int64_class();
}

MonoClass* FMonoDomain::Get_Boolean_Class()
{
	return mono_get_boolean_class();
}

MonoClass* FMonoDomain::Get_Single_Class()
{
	return mono_get_single_class();
}

MonoClass* FMonoDomain::Get_Enum_Class()
{
	return mono_get_enum_class();
}

MonoClass* FMonoDomain::Get_Double_Class()
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

MonoGCHandle FMonoDomain::GCHandle_New_V2(MonoObject* InMonoObject, const mono_bool bPinned)
{
	return mono_gchandle_new_v2(InMonoObject, bPinned);
}

MonoGCHandle FMonoDomain::GCHandle_New_WeakRef_V2(MonoObject* InMonoObject, const mono_bool bTrackResurrection)
{
	return mono_gchandle_new_weakref_v2(InMonoObject, bTrackResurrection);
}

MonoObject* FMonoDomain::GCHandle_Get_Target_V2(const MonoGCHandle InGCHandle)
{
	return mono_gchandle_get_target_v2(InGCHandle);
}

void FMonoDomain::GCHandle_Free_V2(const MonoGCHandle InGCHandle)
{
	return mono_gchandle_free_v2(InGCHandle);
}

MonoMethod* FMonoDomain::Parent_Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                           const int32 InParamCount)
{
	while (InMonoClass != nullptr)
	{
		if (const auto FoundMethod = Class_Get_Method_From_Name(InMonoClass, InFunctionName, InParamCount))
		{
			return FoundMethod;
		}

		InMonoClass = Class_Get_Parent(InMonoClass);
	}

	return nullptr;
}

MonoType* FMonoDomain::Property_Get_Type(MonoProperty* InMonoProperty)
{
	if (const auto Method = Property_Get_Get_Method(InMonoProperty))
	{
		if (const auto Signature = Method_Signature(Method))
		{
			return Signature_Get_Return_Type(Signature);
		}
	}

	return nullptr;
}

MonoAssembly* FMonoDomain::AssemblyPreloadHook(MonoAssemblyName* InAssemblyName, char** InAssemblyPath,
                                               void* InUserData)
{
	const auto AssemblyName = mono_assembly_name_get_name(InAssemblyName);

	TArray<uint8> Data;

#if WITH_EDITOR
	auto Path = FString::Printf(TEXT(
		"%s/%s/Source/ThirdParty/Mono/lib/%s/net7.0"),
	                            *FPaths::ProjectPluginsDir(),
	                            *PLUGIN_NAME,
#if PLATFORM_WINDOWS
	                            TEXT("Win64")
#endif
	);
#else
	auto Path = FString::Printf(TEXT(
		"%s/Binaries/%s/Mono/lib/%s/net7.0"),
	                            *FPaths::ProjectDir(),
#if PLATFORM_WINDOWS
								TEXT("Win64"),
								TEXT("Win64"));
#elif PLATFORM_ANDROID
	                            TEXT("Android"),
	                            TEXT("Android"));
#elif PLATFORM_LINUX
	                            TEXT("Linux"),
	                            TEXT("Linux"));
#endif
#endif

	const auto File = FPaths::Combine(Path, AssemblyName) + DLL_SUFFIX;

	MonoAssembly* Assembly;

	LoadAssembly(AssemblyName, File, nullptr, &Assembly);

	return Assembly;
}

void FMonoDomain::LoadAssembly(const char* InAssemblyName, const FString& InFile,
                               MonoImage** OutImage, MonoAssembly** OutAssembly)
{
	TArray<uint8> Data;

	FFileHelper::LoadFileToArray(Data, *InFile);

	auto ImageOpenStatus = MonoImageOpenStatus::MONO_IMAGE_OK;

	const auto Image = mono_image_open_from_data_with_name((char*)Data.GetData(), Data.Num(),
	                                                       true, &ImageOpenStatus,
	                                                       false, InAssemblyName);

	if (ImageOpenStatus != MonoImageOpenStatus::MONO_IMAGE_OK)
	{
		// @TODO
		return;
	}

	const auto Assembly = mono_assembly_load_from_full(Image, InAssemblyName, &ImageOpenStatus, false);

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

void FMonoDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
#if WITH_EDITOR
	InitializeAssemblyLoadContext();
#endif

	LoadAssembly(InAssemblies);
}

void FMonoDomain::DeinitializeAssembly()
{
	UnloadAssembly();

#if WITH_EDITOR
	DeinitializeAssemblyLoadContext();
#endif
}

void FMonoDomain::InitializeAssemblyLoadContext()
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

void FMonoDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
#if WITH_EDITOR
	if (const auto AssemblyUtilMonoClass = mono_class_from_name(AssemblyUtilImage, TCHAR_TO_ANSI(*NAMESPACE_ROOT),
	                                                            TCHAR_TO_ANSI(*CLASS_ASSEMBLY_UTIL)))
	{
		void* Params[1];

		if (const auto LoadMonoMethod = Class_Get_Method_From_Name(AssemblyUtilMonoClass, FUNCTION_ASSEMBLY_UTIL_LOAD,
		                                                           TGetArrayLength(Params)))
		{
			for (const auto& AssemblyPath : InAssemblies)
			{
				if (!FPaths::FileExists(AssemblyPath))
				{
					continue;;
				}

				Params[0] = String_New(TCHAR_TO_ANSI(*AssemblyPath));

				if (const auto Result = Runtime_Invoke(LoadMonoMethod, nullptr, Params, nullptr))
				{
					auto GCHandle = GCHandle_New_V2(Result, true);

					AssemblyGCHandles.Add(GCHandle);

					const auto ReflectionAssembly = (MonoReflectionAssembly*)GCHandle_Get_Target_V2(GCHandle);

					auto Assembly = mono_reflection_assembly_get_assembly(ReflectionAssembly);

					Assemblies.Add(Assembly);

					Images.Add(mono_assembly_get_image(Assembly));
				}
			}
		}
	}
#else
	for (const auto& AssemblyPath : InAssemblies)
	{
		if (!FPaths::FileExists(AssemblyPath))
		{
			continue;;
		}

		MonoImage* Image = nullptr;

		MonoAssembly* Assembly = nullptr;

		LoadAssembly(TCHAR_TO_UTF8(*FPaths::GetBaseFilename(AssemblyPath)), AssemblyPath, &Image, &Assembly);

		if (Image != nullptr)
		{
			Images.Add(Image);
		}

		if (Assembly != nullptr)
		{
			Assemblies.Add(Assembly);

			const auto ReflectionAssembly = mono_assembly_get_object(Domain, Assembly);

			auto GCHandle = GCHandle_New_V2((MonoObject*)ReflectionAssembly, true);

			AssemblyGCHandles.Add(GCHandle);
		}
	}
#endif

	bLoadSucceed = Assemblies.Num() == InAssemblies.Num();
}

void FMonoDomain::UnloadAssembly()
{
	for (const auto GCHandle : AssemblyGCHandles)
	{
		GCHandle_Free_V2(GCHandle);
	}

	AssemblyGCHandles.Reset();

	for (const auto& Image : Images)
	{
		mono_image_close(Image);
	}

	Images.Reset();

	Assemblies.Reset();
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

void FMonoDomain::RegisterLog()
{
	if (Domain != nullptr)
	{
		if (const auto FoundMonoClass = Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(FoundMonoClass, FUNCTION_UTILS_SET_OUT, 0))
			{
				Runtime_Invoke(FoundMethod, nullptr, nullptr, nullptr);
			}
		}
	}
}

void FMonoDomain::RegisterBinding()
{
	for (const auto& Binding : FBinding::Get().GetBinding())
	{
		mono_add_internal_call(TCHAR_TO_ANSI(*Binding.Key), Binding.Value);
	}
}
