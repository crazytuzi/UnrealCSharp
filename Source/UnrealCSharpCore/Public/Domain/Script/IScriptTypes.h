#pragma once

#include "Domain/Script/IManagedHandle.h"

typedef IManagedHandle (*assembly_loader_Load_from_stream_fn)(const uint8*, int32, const char16_t*);

typedef void (*assembly_loader_unload_fn)();

typedef void (*handle_data_free_fn)(PTRINT);

typedef void (*log_bridge_set_log_fn)(PTRINT);

typedef void (*log_bridge_initialize_fn)();

typedef IManagedHandle (*type_bridge_get_class_fn)(const uint8*);

typedef IManagedHandle (*type_bridge_get_type_fn)(IManagedHandle);

typedef IManagedHandle (*type_bridge_get_method_fn)(IManagedHandle, const uint8*, int32);

typedef PTRINT (*type_bridge_get_function_pointer_fn)(const char16_t*, const char16_t*, const char16_t*);

typedef int32 (*type_bridge_get_namespace_fn)(IManagedHandle, uint8*, int32);

typedef int32 (*type_bridge_get_name_fn)(IManagedHandle, uint8*, int32);

typedef int32 (*type_bridge_get_full_name_fn)(IManagedHandle, uint8*, int32);

typedef IManagedHandle (*type_bridge_make_generic_type_fn)(IManagedHandle, IManagedHandle);

typedef IManagedHandle (*type_bridge_make_generic_type2_fn)(IManagedHandle, IManagedHandle, IManagedHandle);

typedef IManagedHandle (*type_bridge_box_bool_fn)(int32*);

typedef IManagedHandle (*type_bridge_box_sbyte_fn)(int8*);

typedef IManagedHandle (*type_bridge_box_int16_fn)(int16*);

typedef IManagedHandle (*type_bridge_box_int32_fn)(int32*);

typedef IManagedHandle (*type_bridge_box_int64_fn)(int64*);

typedef IManagedHandle (*type_bridge_box_byte_fn)(uint8*);

typedef IManagedHandle (*type_bridge_box_uint16_fn)(uint16*);

typedef IManagedHandle (*type_bridge_box_uint32_fn)(uint32*);

typedef IManagedHandle (*type_bridge_box_uint64_fn)(uint64*);

typedef IManagedHandle (*type_bridge_box_float_fn)(float*);

typedef IManagedHandle (*type_bridge_box_double_fn)(double*);

typedef int32 (*type_bridge_unbox_bool_fn)(IManagedHandle, int32*);

typedef int32 (*type_bridge_unbox_sbyte_fn)(IManagedHandle, int8*);

typedef int32 (*type_bridge_unbox_int16_fn)(IManagedHandle, int16*);

typedef int32 (*type_bridge_unbox_int32_fn)(IManagedHandle, int32*);

typedef int32 (*type_bridge_unbox_int64_fn)(IManagedHandle, int64*);

typedef int32 (*type_bridge_unbox_byte_fn)(IManagedHandle, uint8*);

typedef int32 (*type_bridge_unbox_uint16_fn)(IManagedHandle, uint16*);

typedef int32 (*type_bridge_unbox_uint32_fn)(IManagedHandle, uint32*);

typedef int32 (*type_bridge_unbox_uint64_fn)(IManagedHandle, uint64*);

typedef int32 (*type_bridge_unbox_float_fn)(IManagedHandle, float*);

typedef int32 (*type_bridge_unbox_double_fn)(IManagedHandle, double*);

typedef IManagedHandle (*object_bridge_new_object_fn)(IManagedHandle);

typedef void (*field_bridge_set_static_value_fn)(IManagedHandle, const uint8*, IManagedHandle);

typedef IManagedHandle (*field_bridge_get_static_value_fn)(IManagedHandle, const uint8*);

typedef void (*method_bridge_register_binding_fn)(const uint8* const*, const PTRINT*, int32);

typedef IManagedHandle (*method_bridge_invoke_fn)(IManagedHandle, IManagedHandle, int32, IManagedHandle*);

typedef IManagedHandle (*string_bridge_new_string_fn)(const uint8*);

typedef int32 (*string_bridge_get_string_fn)(IManagedHandle, char16_t*, int32);

typedef IManagedHandle (*array_bridge_new_array_fn)(const uint8*, int32);

typedef IManagedHandle (*array_bridge_array_get_fn)(IManagedHandle, int32);

typedef void (*utils_get_class_reflection_fn)(IManagedHandle, PTRINT*);

typedef void (*synchronization_context_tick_fn)(float);

#define SCRIPT_TYPES \
	assembly_loader_Load_from_stream_fn AssemblyLoaderLoadFromStreamFn{}; \
	assembly_loader_unload_fn AssemblyLoaderUnloadFn{}; \
	\
	handle_data_free_fn HandleDataFreeFn{}; \
	\
	log_bridge_set_log_fn LogBridgeSetLogFn{}; \
	log_bridge_initialize_fn LogBridgeInitializeFn{}; \
	\
	type_bridge_get_class_fn TypeBridgeGetClassFn{}; \
	type_bridge_get_type_fn TypeBridgeGetTypeFn{}; \
	type_bridge_get_method_fn TypeBridgeGetMethodFn{}; \
	type_bridge_get_function_pointer_fn TypeBridgeGetFunctionPointerFn{}; \
	type_bridge_get_namespace_fn TypeBridgeGetNamespaceFn{}; \
	type_bridge_get_name_fn TypeBridgeGetNameFn{}; \
	type_bridge_get_full_name_fn TypeBridgeGetFullNameFn{}; \
	type_bridge_make_generic_type_fn TypeBridgeMakeGenericTypeFn{}; \
	type_bridge_make_generic_type2_fn TypeBridgeMakeGenericType2Fn{}; \
	\
	type_bridge_box_bool_fn TypeBridgeBoxBoolFn{}; \
	type_bridge_box_sbyte_fn TypeBridgeBoxSByteFn{}; \
	type_bridge_box_int16_fn TypeBridgeBoxInt16Fn{}; \
	type_bridge_box_int32_fn TypeBridgeBoxInt32Fn{}; \
	type_bridge_box_int64_fn TypeBridgeBoxInt64Fn{}; \
	type_bridge_box_byte_fn TypeBridgeBoxByteFn{}; \
	type_bridge_box_uint16_fn TypeBridgeBoxUInt16Fn{}; \
	type_bridge_box_uint32_fn TypeBridgeBoxUInt32Fn{}; \
	type_bridge_box_uint64_fn TypeBridgeBoxUInt64Fn{}; \
	type_bridge_box_float_fn TypeBridgeBoxFloatFn{}; \
	type_bridge_box_double_fn TypeBridgeBoxDoubleFn{}; \
	\
	type_bridge_unbox_bool_fn TypeBridgeUnboxBoolFn{}; \
	type_bridge_unbox_sbyte_fn TypeBridgeUnboxSByteFn{}; \
	type_bridge_unbox_int16_fn TypeBridgeUnboxInt16Fn{}; \
	type_bridge_unbox_int32_fn TypeBridgeUnboxInt32Fn{}; \
	type_bridge_unbox_int64_fn TypeBridgeUnboxInt64Fn{}; \
	type_bridge_unbox_byte_fn TypeBridgeUnboxByteFn{}; \
	type_bridge_unbox_uint16_fn TypeBridgeUnboxUInt16Fn{}; \
	type_bridge_unbox_uint32_fn TypeBridgeUnboxUInt32Fn{}; \
	type_bridge_unbox_uint64_fn TypeBridgeUnboxUInt64Fn{}; \
	type_bridge_unbox_float_fn TypeBridgeUnboxFloatFn{}; \
	type_bridge_unbox_double_fn TypeBridgeUnboxDoubleFn{}; \
	\
	object_bridge_new_object_fn ObjectBridgeNewObjectFn{}; \
	\
	field_bridge_set_static_value_fn FieldBridgeSetStaticValueFn{}; \
	field_bridge_get_static_value_fn FieldBridgeGetStaticValueFn{}; \
	\
	method_bridge_register_binding_fn MethodBridgeRegisterBindingFn{}; \
	method_bridge_invoke_fn MethodBridgeInvokeFn{}; \
	\
	string_bridge_new_string_fn StringBridgeNewStringFn{}; \
	string_bridge_get_string_fn StringBridgeGetStringFn{}; \
	\
	array_bridge_new_array_fn ArrayBridgeNewArrayFn{}; \
	array_bridge_array_get_fn ArrayBridgeArrayGetFn{}; \
	\
	utils_get_class_reflection_fn UtilsGetClassReflectionFn{}; \
	\
	synchronization_context_tick_fn SynchronizationContextTickFn{};
