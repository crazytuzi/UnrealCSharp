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

typedef int32 (*utils_is_override_fn)(IManagedHandle);

typedef void (*utils_get_class_descriptor_fn)(IManagedHandle, PTRINT*);

typedef void (*utils_get_class_properties_fn)(IManagedHandle, PTRINT*);

typedef void (*utils_get_class_fields_fn)(IManagedHandle, PTRINT*);

typedef void (*utils_get_class_methods_fn)(IManagedHandle, PTRINT*);

typedef void (*synchronization_context_tick_fn)(float);

#define COMMON_BRIDGE_METHODS(Op) \
	Op(AssemblyLoaderUnload, assembly_loader_unload_fn, CLASS_ASSEMBLY_LOADER, FUNCTION_ASSEMBLY_LOADER_UNLOAD, 0) \
	\
	Op(HandleDataFree, handle_data_free_fn, CLASS_HANDLE_DATA, FUNCTION_HANDLE_DATA_FREE, 1) \
	\
	Op(TypeBridgeGetClass, type_bridge_get_class_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_CLASS, 1) \
	Op(TypeBridgeGetType, type_bridge_get_type_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_TYPE, 1) \
	Op(TypeBridgeGetMethod, type_bridge_get_method_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_METHOD, 3) \
	Op(TypeBridgeGetNamespace, type_bridge_get_namespace_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_NAMESPACE, 3) \
	Op(TypeBridgeGetName, type_bridge_get_name_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_NAME, 3) \
	Op(TypeBridgeGetFullName, type_bridge_get_full_name_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_FULL_NAME, 3) \
	Op(TypeBridgeMakeGenericType, type_bridge_make_generic_type_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE, 2) \
	Op(TypeBridgeMakeGenericType2, type_bridge_make_generic_type2_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE2, 3) \
	\
	Op(TypeBridgeBoxBool, type_bridge_box_bool_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_BOOL, 1) \
	Op(TypeBridgeBoxSByte, type_bridge_box_sbyte_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_SBYTE, 1) \
	Op(TypeBridgeBoxInt16, type_bridge_box_int16_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_INT16, 1) \
	Op(TypeBridgeBoxInt32, type_bridge_box_int32_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_INT32, 1) \
	Op(TypeBridgeBoxInt64, type_bridge_box_int64_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_INT64, 1) \
	Op(TypeBridgeBoxByte, type_bridge_box_byte_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_BYTE, 1) \
	Op(TypeBridgeBoxUInt16, type_bridge_box_uint16_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_UINT16, 1) \
	Op(TypeBridgeBoxUInt32, type_bridge_box_uint32_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_UINT32, 1) \
	Op(TypeBridgeBoxUInt64, type_bridge_box_uint64_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_UINT64, 1) \
	Op(TypeBridgeBoxFloat, type_bridge_box_float_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_FLOAT, 1) \
	Op(TypeBridgeBoxDouble, type_bridge_box_double_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_BOX_DOUBLE, 1) \
	\
	Op(TypeBridgeUnboxBool, type_bridge_unbox_bool_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_BOOL, 2) \
	Op(TypeBridgeUnboxSByte, type_bridge_unbox_sbyte_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_SBYTE, 2) \
	Op(TypeBridgeUnboxInt16, type_bridge_unbox_int16_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_INT16, 2) \
	Op(TypeBridgeUnboxInt32, type_bridge_unbox_int32_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_INT32, 2) \
	Op(TypeBridgeUnboxInt64, type_bridge_unbox_int64_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_INT64, 2) \
	Op(TypeBridgeUnboxByte, type_bridge_unbox_byte_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_BYTE, 2) \
	Op(TypeBridgeUnboxUInt16, type_bridge_unbox_uint16_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_UINT16, 2) \
	Op(TypeBridgeUnboxUInt32, type_bridge_unbox_uint32_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_UINT32, 2) \
	Op(TypeBridgeUnboxUInt64, type_bridge_unbox_uint64_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_UINT64, 2) \
	Op(TypeBridgeUnboxFloat, type_bridge_unbox_float_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_FLOAT, 2) \
	Op(TypeBridgeUnboxDouble, type_bridge_unbox_double_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_UNBOX_DOUBLE, 2) \
	\
	Op(ObjectBridgeNewObject, object_bridge_new_object_fn, CLASS_OBJECT_BRIDGE, FUNCTION_OBJECT_BRIDGE_NEW_OBJECT, 1) \
	\
	Op(FieldBridgeSetStaticValue, field_bridge_set_static_value_fn, CLASS_FIELD_BRIDGE, FUNCTION_FIELD_BRIDGE_SET_STATIC_VALUE, 3) \
	Op(FieldBridgeGetStaticValue, field_bridge_get_static_value_fn, CLASS_FIELD_BRIDGE, FUNCTION_FIELD_BRIDGE_GET_STATIC_VALUE, 2) \
	\
	Op(MethodBridgeInvoke, method_bridge_invoke_fn, CLASS_METHOD_BRIDGE, FUNCTION_METHOD_BRIDGE_INVOKE, 4) \
	\
	Op(StringBridgeNewString, string_bridge_new_string_fn, CLASS_STRING_BRIDGE, FUNCTION_STRING_BRIDGE_NEW_STRING, 1) \
	Op(StringBridgeGetString, string_bridge_get_string_fn, CLASS_STRING_BRIDGE, FUNCTION_STRING_BRIDGE_GET_STRING, 3) \
	\
	Op(ArrayBridgeNewArray, array_bridge_new_array_fn, CLASS_ARRAY_BRIDGE, FUNCTION_ARRAY_BRIDGE_ARRAY_NEW, 2) \
	Op(ArrayBridgeArrayGet, array_bridge_array_get_fn, CLASS_ARRAY_BRIDGE, FUNCTION_ARRAY_BRIDGE_ARRAY_GET, 2)

#define NATIVE_BRIDGE_METHODS(Op) \
	Op(AssemblyLoaderLoadFromStream, assembly_loader_Load_from_stream_fn, CLASS_ASSEMBLY_LOADER, FUNCTION_ASSEMBLY_LOADER_LOAD_FROM_STREAM, 3) \
	\
	Op(LogBridgeSetLog, log_bridge_set_log_fn, CLASS_LOG_BRIDGE, FUNCTION_LOG_BRIDGE_SET_LOG, 1) \
	Op(LogBridgeInitialize, log_bridge_initialize_fn, CLASS_LOG_BRIDGE, FUNCTION_LOG_BRIDGE_INITIALIZE, 0) \
	\
	Op(TypeBridgeGetFunctionPointer, type_bridge_get_function_pointer_fn, CLASS_TYPE_BRIDGE, FUNCTION_TYPE_BRIDGE_GET_FUNCTION_POINTER, 3) \
	\
	Op(MethodBridgeRegisterBinding, method_bridge_register_binding_fn, CLASS_METHOD_BRIDGE, FUNCTION_METHOD_BRIDGE_REGISTER_BINDING, 3)

#define UTILS_BRIDGE_METHODS(Op) \
	Op(UtilsIsOverride, utils_is_override_fn, COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS), FUNCTION_UTILS_IS_OVERRIDE, 1) \
	Op(UtilsGetClassDescriptor, utils_get_class_descriptor_fn, COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS), FUNCTION_UTILS_GET_CLASS_DESCRIPTOR, 2) \
	Op(UtilsGetClassProperties, utils_get_class_properties_fn, COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS), FUNCTION_UTILS_GET_CLASS_PROPERTIES, 2) \
	Op(UtilsGetClassFields, utils_get_class_fields_fn, COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS), FUNCTION_UTILS_GET_CLASS_FIELDS, 2) \
	Op(UtilsGetClassMethods, utils_get_class_methods_fn, COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS), FUNCTION_UTILS_GET_CLASS_METHODS, 2) \
	\
	Op(SynchronizationContextTick, synchronization_context_tick_fn, COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_SYNCHRONIZATION_CONTEXT), FUNCTION_SYNCHRONIZATION_CONTEXT_TICK, 1)

#define SCRIPT_TYPE_MEMBER(Name, FnType, ClassMacro, FuncMacro, ParamCount) FnType Name##Fn{};

#define SCRIPT_TYPES \
	COMMON_BRIDGE_METHODS(SCRIPT_TYPE_MEMBER) \
	NATIVE_BRIDGE_METHODS(SCRIPT_TYPE_MEMBER) \
	UTILS_BRIDGE_METHODS(SCRIPT_TYPE_MEMBER)
