#pragma once

#define COMBINE_NAMESPACE(A, B) FString::Printf(TEXT("%s.%s"), *A, *B)

#define NAMESPACE_ROOT FString(TEXT("Script"))

#define NAMESPACE_SCRIPT FString(TEXT("Script"))

#define NAMESPACE_SYSTEM FString(TEXT("System"))

#define NAMESPACE_LIBRARY FString(TEXT("Library"))

#define NAMESPACE_CORE_UOBJECT FString(TEXT("CoreUObject"))

#define NAMESPACE_DYNAMIC FString(TEXT("Dynamic"))
