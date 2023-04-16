#pragma once

#define COMBINE_FUNCTION(Function) FString::Printf(TEXT("::%s"), *Function)

#define FUNCTION_OBJECT_LIST_ADD FString(TEXT("Add"))

#define FUNCTION_OBJECT_CONSTRUCTOR FString(".ctor")

#define FUNCTION_UTILS_SET_OUT FString(TEXT("SetOut"))

#define FUNCTION_UTILS_GET_PATH_NAME FString(TEXT("GetPathName"))

#define FUNCTION_UTILS_IS_OVERRIDE_TYPE FString(TEXT("IsOverrideType"))

#define FUNCTION_UTILS_IS_OVERRIDE_METHOD FString(TEXT("IsOverrideMethod"))

#define FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE FString(TEXT("MakeGenericTypeInstance"))

#define FUNCTION_UTILS_GET_GENERIC_ARGUMENTS FString(TEXT("GetGenericArguments"))

#define FUNCTION_UTILS_GET_TYPE FString(TEXT("GetType"))

#define FUNCTION_UTILS_MULTICAST_DELEGATE_GET_TARGET FString(TEXT("MulticastDelegate_GetTarget"))

#define FUNCTION_UTILS_MULTICAST_DELEGATE_EQUALS FString(TEXT("MulticastDelegate_Equals"))

#define FUNCTION_UTILS_GET_TRACEBACK FString(TEXT("GetTraceback"))

#define FUNCTION_STATIC_STRUCT FString(TEXT("StaticStruct"))
