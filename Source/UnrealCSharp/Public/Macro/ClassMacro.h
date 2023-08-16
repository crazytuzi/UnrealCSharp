#pragma once

#define COMBINE_CLASS(A, B) FString::Printf(TEXT("%s.%s"), *A, *B)

#define CLASS_MULTICAST_DELEGATE_UTILS FString(TEXT("MulticastDelegateUtils"))
