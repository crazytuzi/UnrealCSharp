﻿#pragma once

#define COMBINE_FUNCTION(Function) FString::Printf(TEXT("::%s"), *Function)

#define FUNCTION_UTILS_IS_OVERRIDE_TYPE FString(TEXT("IsOverrideType"))

#define FUNCTION_UTILS_IS_OVERRIDE_METHOD FString(TEXT("IsOverrideMethod"))

#define FUNCTION_UTILS_MULTICAST_DELEGATE_GET_TARGET FString(TEXT("MulticastDelegate_GetTarget"))

#define FUNCTION_UTILS_MULTICAST_DELEGATE_EQUALS FString(TEXT("MulticastDelegate_Equals"))

#define FUNCTION_UTILS_GET_TRACEBACK FString(TEXT("GetTraceback"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_INITIALIZE FString(TEXT("Initialize"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_DEINITIALIZE FString(TEXT("Deinitialize"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_TICK FString(TEXT("Tick"))

#define FUNCTION_DESTRUCTOR FString(TEXT("Destructor"))

#define FUNCTION_GET_SUBSCRIPT FString(TEXT("GetSubscript"))

#define FUNCTION_SET_SUBSCRIPT FString(TEXT("SetSubscript"))

#define FUNCTION_LOGICAL_NOT FString(TEXT("LogicalNot"))

#define FUNCTION_UNARY_PLUS FString(TEXT("UnaryPlus"))

#define FUNCTION_UNARY_MINUS FString(TEXT("UnaryMinus"))

#define FUNCTION_COMPLEMENT FString(TEXT("Complement"))

#define FUNCTION_PRE_INCREMENT FString(TEXT("PreIncrement"))

#define FUNCTION_PRE_DECREMENT FString(TEXT("PreDecrement"))

#define FUNCTION_PLUS FString(TEXT("Plus"))

#define FUNCTION_MINUS FString(TEXT("Minus"))

#define FUNCTION_MULTIPLIES FString(TEXT("Multiplies"))

#define FUNCTION_DIVIDES FString(TEXT("Divides"))

#define FUNCTION_MODULUS FString(TEXT("Modulus"))

#define FUNCTION_BIT_AND FString(TEXT("BitAnd"))

#define FUNCTION_BIT_OR FString(TEXT("BitOr"))

#define FUNCTION_BIT_XOR FString(TEXT("BitXor"))

#define FUNCTION_LEFT_SHIFT FString(TEXT("LeftShift"))

#define FUNCTION_RIGHT_SHIFT FString(TEXT("RightShift"))

#define FUNCTION_EQUAL_TO FString(TEXT("EqualTo"))

#define FUNCTION_NOT_EQUAL_TO FString(TEXT("NotEqualTo"))

#define FUNCTION_LESS FString(TEXT("Less"))

#define FUNCTION_LESS_EQUAL FString(TEXT("LessEqual"))

#define FUNCTION_GREATER FString(TEXT("Greater"))

#define FUNCTION_GREATER_EQUAL FString(TEXT("GreaterEqual"))

#define FUNCTION_SET_HANDLE FString(TEXT("SetHandle"))
