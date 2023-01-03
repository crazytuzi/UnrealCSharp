#include "Domain/FMonoDomain.h"
#include "Binding/FBinding.h"
#include "Domain/InternalCall/FArrayImplementation.h"
#include "Domain/InternalCall/FDelegateImplementation.h"
#include "Domain/InternalCall/FMonoInternalCall.h"
#include "Domain/InternalCall/FPropertyImplementation.h"
#include "Domain/InternalCall/FFunctionImplementation.h"
#include "Domain/InternalCall/FMapImplementation.h"
#include "Domain/InternalCall/FMulticastDelegateImplementation.h"
#include "Domain/InternalCall/FSetImplementation.h"
#include "Domain/InternalCall/FStructImplementation.h"
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

#if !WITH_EDITOR
	mono_set_dirs("Mono/lib", "Mono/etc");
#endif

	Domain = mono_jit_init(TCHAR_TO_ANSI(*Params.Domain));

	Assembly = mono_domain_assembly_open(Domain, TCHAR_TO_ANSI(*Params.Assembly));

	Image = mono_assembly_get_image(Assembly);

	RegisterReflectionPropertyImplementation();

	RegisterReflectionFunctionImplementation();

	RegisterReflectionStructImplementation();

	RegisterReflectionContainerImplementation();

	RegisterReflectionDelegateImplementation();

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

void FMonoDomain::RegisterReflectionPropertyImplementation()
{
	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Byte)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(UInt16)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(UInt32)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(UInt64)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int8)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int16)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int64)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Bool)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Float)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Object)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Class)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Interface)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Array)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(WeakObject)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(LazyObject)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(SoftObject)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Double)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Map)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Set)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(FieldPath)
}

void FMonoDomain::RegisterReflectionFunctionImplementation()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_FUNCTION), CLASS_FUNCTION_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_FUNCTION_REFLECTION_IMPLEMENTATION))),
		static_cast<void*>(FFunctionImplementation::Function_ReflectionImplementation));
}

void FMonoDomain::RegisterReflectionStructImplementation()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_STRUCT), CLASS_STRUCT_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_STRUCT_REGISTER_IMPLEMENTATION))),
		static_cast<void*>(FStructImplementation::Struct_RegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_STRUCT), CLASS_STRUCT_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_STRUCT_UNREGISTER_IMPLEMENTATION))),
		static_cast<void*>(FStructImplementation::Struct_UnRegisterImplementation));
}

void FMonoDomain::RegisterReflectionContainerImplementation()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_REGISTER_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_RegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_UNREGISTER_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_UnRegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_GET_TYPE_SIZE_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_GetTypeSizeImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_GET_SLACK_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_GetSlackImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_IS_VALID_INDEX_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_IsValidIndexImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_NUM_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_NumImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_MAX_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_MaxImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_GET_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_GetImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_SET_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_SetImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_FIND_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_FindImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_FIND_LAST_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_FindLastImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_CONTAINS_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_ContainsImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_ADD_UNINITIALIZED_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_AddUninitializedImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_INSERT_ZEROED_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_InsertZeroedImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_INSERT_DEFAULTED_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_InsertDefaultedImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_REMOVE_AT_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_RemoveAtImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_RESET_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_ResetImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_EMPTY_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_EmptyImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_SET_NUM_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_SetNumImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_ADD_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_AddImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_ADD_ZEROED_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_AddZeroedImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_ADD_UNIQUE_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_AddUniqueImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_REMOVE_SINGLE_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_RemoveSingleImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_REMOVE_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_RemoveImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_SWAP_MEMORY_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_SwapMemoryImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_ARRAY_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_ARRAY_SWAP_IMPLEMENTATION))),
		static_cast<void*>(FArrayImplementation::Array_SwapImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_REGISTER_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_RegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_UNREGISTER_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_UnRegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_EMPTY_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_EmptyImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_NUM_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_NumImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_ADD_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_AddImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_REMOVE_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_RemoveImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_FIND_KEY_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_FindKeyImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_FIND_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_FindImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_CONTAINS_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_ContainsImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_GET_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_GetImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_MAP_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_MAP_SET_IMPLEMENTATION))),
		static_cast<void*>(FMapImplementation::Map_SetImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_REGISTER_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_RegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_UNREGISTER_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_UnRegisterImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_EMPTY_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_EmptyImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_NUM_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_NumImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_ADD_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_AddImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_REMOVE_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_RemoveImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_SET_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_SET_CONTAINS_IMPLEMENTATION))),
		static_cast<void*>(FSetImplementation::Set_ContainsImplementation));
}

void FMonoDomain::RegisterReflectionDelegateImplementation()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE), CLASS_DELEGATE_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_DELEGATE_BIND_IMPLEMENTATION))),
		static_cast<void*>(FDelegateImplementation::Delegate_BindImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE), CLASS_DELEGATE_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_DELEGATE_IS_BOUND_IMPLEMENTATION))),
		static_cast<void*>(FDelegateImplementation::Delegate_IsBoundImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE), CLASS_DELEGATE_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_DELEGATE_UNBIND_IMPLEMENTATION))),
		static_cast<void*>(FDelegateImplementation::Delegate_UnBindImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE), CLASS_DELEGATE_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_DELEGATE_CLEAR_IMPLEMENTATION))),
		static_cast<void*>(FDelegateImplementation::Delegate_ClearImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE), CLASS_DELEGATE_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_DELEGATE_EXECUTE_IMPLEMENTATION))),
		static_cast<void*>(FDelegateImplementation::Delegate_ExecuteImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_IS_BOUND_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_IsBoundImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_CONTAINS_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_ADD_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_AddImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_ADD_UNIQUE_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_AddUniqueImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_REMOVE_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_RemoveImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_REMOVE_ALL_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_RemoveAllImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_CLEAR_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_ClearImplementation));

	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),
				CLASS_MULTICAST_DELEGATE_IMPLEMENTATION) + COMBINE_FUNCTION(
				FUNCTION_MULTICAST_DELEGATE_BROADCAST_IMPLEMENTATION))),
		static_cast<void*>(FMulticastDelegateImplementation::MulticastDelegate_BroadcastImplementation));
}

void FMonoDomain::RegisterLog()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LOG), CLASS_LOG) + COMBINE_FUNCTION(
				FUNCTION_LOG_IMPLEMENTATION))),
		static_cast<void*>(FMonoLog::LogImplementation));

	if (Domain != nullptr)
	{
		if (const auto FoundMonoClass = Class_From_Name(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LOG), CLASS_LOG))
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
