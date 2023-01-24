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

FMonoDomain::FMonoDomain(const FMonoDomainInitializeParams& Params):
	Domain(nullptr),
	Assembly(nullptr),
	Image(nullptr)
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

#if WITH_EDITOR
	auto MonoDir = FString::Printf(
		TEXT("%s/Binaries/%s"),
		*FPaths::ProjectDir(),
#if PLATFORM_WINDOWS
		TEXT("Win64")
#endif
	);

	mono_set_dirs(TCHAR_TO_ANSI(*FPaths::Combine(MonoDir, TEXT("Mono/lib"))),
	              TCHAR_TO_ANSI(*FPaths::Combine(MonoDir, TEXT("Mono/etc"))));
#else
	mono_set_dirs("Mono/lib", "Mono/etc");
#endif

	Domain = mono_jit_init(TCHAR_TO_ANSI(*Params.Domain));

	Assembly = mono_domain_assembly_open(Domain, TCHAR_TO_ANSI(*Params.Assembly));

	Image = mono_assembly_get_image(Assembly);

	RegisterLog();

	RegisterBinding();
}

void FMonoDomain::Deinitialize()
{
	if (Image != nullptr)
	{
		mono_image_close(Image);

		Image = nullptr;
	}

	if (Assembly != nullptr)
	{
		mono_assembly_name_free(mono_assembly_get_name(Assembly));

		Assembly = nullptr;
	}

	if (Domain != nullptr)
	{
		mono_jit_cleanup(Domain);

		Domain = nullptr;
	}
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
				Runtime_Invoke(FoundMethod, NewMonoObject, InParams, nullptr);

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
	return Image != nullptr
		       ? mono_class_from_name(Image, TCHAR_TO_ANSI(*InNameSpace), TCHAR_TO_ANSI(*InMonoClassName))
		       : nullptr;
}

MonoMethod* FMonoDomain::Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                    const int32 InParamCount) const
{
	return InMonoClass != nullptr
		       ? mono_class_get_method_from_name(InMonoClass, TCHAR_TO_ANSI(*InFunctionName), InParamCount)
		       : nullptr;
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

MonoReflectionMethod* FMonoDomain::Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass)
{
	return Domain != nullptr && InMethod != nullptr && InMonoClass != nullptr
		       ? mono_method_get_object(Domain, InMethod, InMonoClass)
		       : nullptr;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams,
                                        MonoObject** InExc) const
{
	return InFunction != nullptr ? mono_runtime_invoke(InFunction, InMonoObject, InParams, InExc) : nullptr;
}

MonoObject* FMonoDomain::Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc)
{
	return InDelegate != nullptr ? mono_runtime_delegate_invoke(InDelegate, InParams, InExc) : nullptr;
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

void FMonoDomain::RegisterMonoTrace()
{
	mono_trace_set_log_handler(FMonoLog::MonoLog, nullptr);

	mono_trace_set_print_handler(FMonoLog::MonoPrintf);

	mono_trace_set_printerr_handler(FMonoLog::MonoPrintf);
}

void FMonoDomain::RegisterLog()
{
	if (Domain != nullptr)
	{
		if (const auto FoundMonoClass = Class_From_Name(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LOG), CLASS_LOG_IMPLEMENTATION))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(FoundMonoClass, FUNCTION_LOG_SET_OUT, 0))
			{
				Runtime_Invoke(FoundMethod, nullptr, nullptr, nullptr);
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
