#pragma once

#define COMBINE_NAMESPACE(A, B) FString::Printf(TEXT("%s.%s"), *A, *B)

#define NAMESPACE_ROOT FString(TEXT("Script"))

#define NAMESPACE_COMMON FString(TEXT("Common"))

#define NAMESPACE_DYNAMIC FString(TEXT("Dynamic"))
