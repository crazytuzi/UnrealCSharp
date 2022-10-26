#pragma once

#define COMBINE_NAMESPACE(A, B) A.Append(".").Append(B)

#define NAMESPACE_ROOT FString(TEXT("Script"))

#define NAMESPACE_ENGINE FString(TEXT("Engine"))

#define NAMESPACE_GAME FString(TEXT("Game"))

#define NAMESPACE_LOG FString(TEXT("Log"))

#define NAMESPACE_PROPERTY FString(TEXT("Reflection.Property"))

#define NAMESPACE_FUNCTION FString(TEXT("Reflection.Function"))
