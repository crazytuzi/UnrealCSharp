#pragma once

#define COMBINE_NAMESPACE(A, B) A.Append(".").Append(B)

#define NAMESPACE_ROOT FString(TEXT("Script"))

#define NAMESPACE_COMMON FString(TEXT("Common"))

#define NAMESPACE_LOG FString(TEXT("Log"))

#define NAMESPACE_PROPERTY FString(TEXT("Reflection.Property"))

#define NAMESPACE_FUNCTION FString(TEXT("Reflection.Function"))

#define NAMESPACE_STRUCT FString(TEXT("Reflection.Struct"))

#define NAMESPACE_CONTAINER FString(TEXT("Reflection.Container"))

#define NAMESPACE_DELEGATE FString(TEXT("Reflection.Delegate"))

#define NAMESPACE_BINDING FString(TEXT("Binding"))
