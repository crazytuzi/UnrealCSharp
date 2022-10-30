#pragma once

#define COMBINE_FUNCTION(Function) FString(TEXT("::")).Append(Function)

#define FUNCTION_LOG_IMPLEMENTATION FString(TEXT("LogImplementation"))

#define FUNCTION_SET_OUT FString(TEXT("SetOut"))

#define FUNCTION_CALL_REFLECTION_MEMBER_FUNCTION_IMPLEMENTATION FString(TEXT("CallReflectionMemberFunctionImplementation"))

#define FUNCTION_CALL_REFLECTION_STATIC_FUNCTION_IMPLEMENTATION FString(TEXT("CallReflectionStaticFunctionImplementation"))

#define FUNCTION_ADD FString(TEXT("Add"))

#define FUNCTION_CTOR FString(".ctor")
