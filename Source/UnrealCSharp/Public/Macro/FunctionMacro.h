#pragma once

#define COMBINE_FUNCTION(Function) FString(TEXT("::")).Append(Function)

#define FUNCTION_LOG_IMPLEMENTATION FString(TEXT("LogImplementation"))

#define FUNCTION_SET_OUT FString(TEXT("SetOut"))

#define FUNCTION_CALL_REFLECTION_MEMBER_FUNCTION_IMPLEMENTATION FString(TEXT("CallReflectionMemberFunctionImplementation"))

#define FUNCTION_CALL_REFLECTION_STATIC_FUNCTION_IMPLEMENTATION FString(TEXT("CallReflectionStaticFunctionImplementation"))

#define FUNCTION_REGISTER_STRUCT_IMPLEMENTATION FString(TEXT("RegisterStructImplementation"))

#define FUNCTION_UNREGISTER_STRUCT_IMPLEMENTATION FString(TEXT("UnRegisterStructImplementation"))

#define FUNCTION_REGISTER_ARRAY_IMPLEMENTATION FString(TEXT("RegisterArrayImplementation"))

#define FUNCTION_UNREGISTER_ARRAY_IMPLEMENTATION FString(TEXT("UnRegisterArrayImplementation"))

#define FUNCTION_ARRAY_GET_TYPE_SIZE_IMPLEMENTATION FString(TEXT("Array_GetTypeSizeImplementation"))

#define FUNCTION_ARRAY_GET_SLACK_IMPLEMENTATION FString(TEXT("Array_GetSlackImplementation"))

#define FUNCTION_ARRAY_IS_VALID_INDEX_IMPLEMENTATION FString(TEXT("ARRAY_ISVALIDINDEXIMPLEMENTATION"))

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

#define FUNCTION_ADD FString(TEXT("Add"))

#define FUNCTION_CTOR FString(".ctor")

#define FUNCTION_GET_PATH_NAME FString(TEXT("GetPathName"))
