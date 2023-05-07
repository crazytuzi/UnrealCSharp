#pragma once

#define COMBINE_FUNCTION(Function) FString::Printf(TEXT("::%s"), *Function)

#define FUNCTION_OBJECT_LIST_ADD FString(TEXT("Add"))

#define FUNCTION_UTILS_IS_OVERRIDE_TYPE FString(TEXT("IsOverrideType"))

#define FUNCTION_UTILS_IS_OVERRIDE_METHOD FString(TEXT("IsOverrideMethod"))

#define FUNCTION_UTILS_MULTICAST_DELEGATE_GET_TARGET FString(TEXT("MulticastDelegate_GetTarget"))

#define FUNCTION_UTILS_MULTICAST_DELEGATE_EQUALS FString(TEXT("MulticastDelegate_Equals"))

#define FUNCTION_UTILS_GET_TRACEBACK FString(TEXT("GetTraceback"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_INITIALIZE FString(TEXT("Initialize"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_DEINITIALIZE FString(TEXT("Deinitialize"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_TICK FString(TEXT("Tick"))
