#pragma once

#define COMBINE_CLASS(A, B) FString::Printf(TEXT("%s.%s"), *A, *B)

#define CLASS_INT_PTR FString(TEXT("IntPtr"))

#define CLASS_OBJECT_LIST FString(TEXT("ObjectList"))

#define CLASS_MULTICAST_DELEGATE_UTILS FString(TEXT("MulticastDelegateUtils"))

#define CLASS_SCRIPT_STRUCT(T) TScriptStruct<T>::Get()

#define CLASS_SCRIPT_STRUCT_NAME(T) FString::Printf(TEXT("F%s"), *CLASS_SCRIPT_STRUCT(T)->GetName())
