#pragma once

#define COMBINE_FUNCTION(Function) FString(TEXT("::")).Append(Function)

#define FUNCTION_LOG_IMPLEMENTATION FString(TEXT("LogImplementation"))

#define FUNCTION_LOG_SET_OUT FString(TEXT("SetOut"))

#define FUNCTION_FUNCTION_REFLECTION_IMPLEMENTATION FString(TEXT("Function_ReflectionImplementation"))

#define FUNCTION_STRUCT_REGISTER_IMPLEMENTATION FString(TEXT("Struct_RegisterImplementation"))

#define FUNCTION_STRUCT_UNREGISTER_IMPLEMENTATION FString(TEXT("Struct_UnRegisterImplementation"))

#define FUNCTION_ARRAY_REGISTER_IMPLEMENTATION FString(TEXT("Array_RegisterImplementation"))

#define FUNCTION_ARRAY_UNREGISTER_IMPLEMENTATION FString(TEXT("Array_UnRegisterImplementation"))

#define FUNCTION_ARRAY_GET_TYPE_SIZE_IMPLEMENTATION FString(TEXT("Array_GetTypeSizeImplementation"))

#define FUNCTION_ARRAY_GET_SLACK_IMPLEMENTATION FString(TEXT("Array_GetSlackImplementation"))

#define FUNCTION_ARRAY_IS_VALID_INDEX_IMPLEMENTATION FString(TEXT("Array_IsValidIndexImplementation"))

#define FUNCTION_ARRAY_NUM_IMPLEMENTATION FString(TEXT("Array_NumImplementation"))

#define FUNCTION_ARRAY_MAX_IMPLEMENTATION FString(TEXT("Array_MaxImplementation"))

#define FUNCTION_ARRAY_GET_IMPLEMENTATION FString(TEXT("Array_GetImplementation"))

#define FUNCTION_ARRAY_SET_IMPLEMENTATION FString(TEXT("Array_SetImplementation"))

#define FUNCTION_ARRAY_FIND_IMPLEMENTATION FString(TEXT("Array_FindImplementation"))

#define FUNCTION_ARRAY_FIND_LAST_IMPLEMENTATION FString(TEXT("Array_FindLastImplementation"))

#define FUNCTION_ARRAY_CONTAINS_IMPLEMENTATION FString(TEXT("Array_ContainsImplementation"))

#define FUNCTION_ARRAY_ADD_UNINITIALIZED_IMPLEMENTATION FString(TEXT("Array_AddUninitializedImplementation"))

#define FUNCTION_ARRAY_INSERT_ZEROED_IMPLEMENTATION FString(TEXT("Array_InsertZeroedImplementation"))

#define FUNCTION_ARRAY_INSERT_DEFAULTED_IMPLEMENTATION FString(TEXT("Array_InsertDefaultedImplementation"))

#define FUNCTION_ARRAY_REMOVE_AT_IMPLEMENTATION FString(TEXT("Array_RemoveAtImplementation"))

#define FUNCTION_ARRAY_RESET_IMPLEMENTATION FString(TEXT("Array_ResetImplementation"))

#define FUNCTION_ARRAY_EMPTY_IMPLEMENTATION FString(TEXT("Array_EmptyImplementation"))

#define FUNCTION_ARRAY_SET_NUM_IMPLEMENTATION FString(TEXT("Array_SetNumImplementation"))

#define FUNCTION_ARRAY_ADD_IMPLEMENTATION FString(TEXT("Array_AddImplementation"))

#define FUNCTION_ARRAY_ADD_ZEROED_IMPLEMENTATION FString(TEXT("Array_AddZeroedImplementation"))

#define FUNCTION_ARRAY_ADD_UNIQUE_IMPLEMENTATION FString(TEXT("Array_AddUniqueImplementation"))

#define FUNCTION_ARRAY_REMOVE_SINGLE_IMPLEMENTATION FString(TEXT("Array_RemoveSingleImplementation"))

#define FUNCTION_ARRAY_REMOVE_IMPLEMENTATION FString(TEXT("Array_RemoveImplementation"))

#define FUNCTION_ARRAY_SWAP_MEMORY_IMPLEMENTATION FString(TEXT("Array_SwapMemoryImplementation"))

#define FUNCTION_ARRAY_SWAP_IMPLEMENTATION FString(TEXT("Array_SwapImplementation"))

#define FUNCTION_MAP_REGISTER_IMPLEMENTATION FString(TEXT("Map_RegisterImplementation"))

#define FUNCTION_MAP_UNREGISTER_IMPLEMENTATION FString(TEXT("Map_UnRegisterImplementation"))

#define FUNCTION_MAP_EMPTY_IMPLEMENTATION FString(TEXT("Map_EmptyImplementation"))

#define FUNCTION_MAP_NUM_IMPLEMENTATION FString(TEXT("Map_NumImplementation"))

#define FUNCTION_MAP_ADD_IMPLEMENTATION FString(TEXT("Map_AddImplementation"))

#define FUNCTION_MAP_REMOVE_IMPLEMENTATION FString(TEXT("Map_RemoveImplementation"))

#define FUNCTION_MAP_FIND_KEY_IMPLEMENTATION FString(TEXT("Map_FindKeyImplementation"))

#define FUNCTION_MAP_FIND_IMPLEMENTATION FString(TEXT("Map_FindImplementation"))

#define FUNCTION_MAP_CONTAINS_IMPLEMENTATION FString(TEXT("Map_ContainsImplementation"))

#define FUNCTION_MAP_GET_IMPLEMENTATION FString(TEXT("Map_GetImplementation"))

#define FUNCTION_MAP_SET_IMPLEMENTATION FString(TEXT("Map_SetImplementation"))

#define FUNCTION_SET_REGISTER_IMPLEMENTATION FString(TEXT("Set_RegisterImplementation"))

#define FUNCTION_SET_UNREGISTER_IMPLEMENTATION FString(TEXT("Set_UnRegisterImplementation"))

#define FUNCTION_SET_EMPTY_IMPLEMENTATION FString(TEXT("Set_EmptyImplementation"))

#define FUNCTION_SET_NUM_IMPLEMENTATION FString(TEXT("Set_NumImplementation"))

#define FUNCTION_SET_ADD_IMPLEMENTATION FString(TEXT("Set_AddImplementation"))

#define FUNCTION_SET_REMOVE_IMPLEMENTATION FString(TEXT("Set_RemoveImplementation"))

#define FUNCTION_SET_CONTAINS_IMPLEMENTATION FString(TEXT("Set_ContainsImplementation"))

#define FUNCTION_DELEGATE_BIND_IMPLEMENTATION FString(TEXT("Delegate_BindImplementation"))

#define FUNCTION_DELEGATE_IS_BOUND_IMPLEMENTATION FString(TEXT("Delegate_IsBoundImplementation"))

#define FUNCTION_DELEGATE_UNBIND_IMPLEMENTATION FString(TEXT("Delegate_UnBindImplementation"))

#define FUNCTION_DELEGATE_CLEAR_IMPLEMENTATION FString(TEXT("Delegate_ClearImplementation"))

#define FUNCTION_DELEGATE_EXECUTE_IMPLEMENTATION FString(TEXT("Delegate_ExecuteImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_IS_BOUND_IMPLEMENTATION FString(TEXT("MulticastDelegate_IsBoundImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_CONTAINS_IMPLEMENTATION FString(TEXT("MulticastDelegate_ContainsImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_ADD_IMPLEMENTATION FString(TEXT("MulticastDelegate_AddImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_ADD_UNIQUE_IMPLEMENTATION FString(TEXT("MulticastDelegate_AddUniqueImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_REMOVE_IMPLEMENTATION FString(TEXT("MulticastDelegate_RemoveImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_REMOVE_ALL_IMPLEMENTATION FString(TEXT("MulticastDelegate_RemoveAllImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_CLEAR_IMPLEMENTATION FString(TEXT("MulticastDelegate_ClearImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_BROADCAST_IMPLEMENTATION FString(TEXT("MulticastDelegate_BroadcastImplementation"))

#define FUNCTION_MULTICAST_DELEGATE_GET_TARGET FString(TEXT("MulticastDelegate_GetTarget"))

#define FUNCTION_MULTICAST_DELEGATE_EQUALS FString(TEXT("MulticastDelegate_Equals"))

#define FUNCTION_OBJECT_LIST_ADD FString(TEXT("Add"))

#define FUNCTION_OBJECT_CONSTRUCTOR FString(".ctor")

#define FUNCTION_UTILS_GET_PATH_NAME FString(TEXT("GetPathName"))

#define FUNCTION_UTILS_IS_OVERRIDE_TYPE FString(TEXT("IsOverrideType"))

#define FUNCTION_UTILS_IS_OVERRIDE_METHOD FString(TEXT("IsOverrideMethod"))

#define FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE FString(TEXT("MakeGenericTypeInstance"))

#define FUNCTION_STATIC_CLASS FString(TEXT("StaticClass"))

#define FUNCTION_SUB_CLASS_OF_GET FString(TEXT("Get"))
