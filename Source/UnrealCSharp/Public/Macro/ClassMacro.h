#pragma once

#define COMBINE_CLASS(A, B) FString::Printf(TEXT("%s.%s"), *A, *B)

#define CLASS_INT_PTR FString(TEXT("IntPtr"))

#define CLASS_OBJECT_LIST FString(TEXT("ObjectList"))

#define CLASS_F_STRING FString(TEXT("FString"))

#define CLASS_F_NAME FString(TEXT("FName"))

#define CLASS_F_TEXT FString(TEXT("FText"))

#define CLASS_UTILS FString(TEXT("Utils"))

#define CLASS_ASSEMBLY_UTIL FString(TEXT("AssemblyUtil"))


#define CLASS_SYNC_CONTEXT FString(TEXT("UnrealCSharpSyncContext"))


#define CLASS_MULTICAST_DELEGATE_UTILS FString(TEXT("MulticastDelegateUtils"))

#define CLASS_T_ARRAY FString(TEXT("TArray`1"))

#define CLASS_T_MAP FString(TEXT("TMap`2"))

#define CLASS_T_SET FString(TEXT("TSet`1"))

#define CLASS_T_SUB_CLASS_OF FString(TEXT("TSubclassOf`1"))

#define CLASS_T_SCRIPT_INTERFACE FString(TEXT("TScriptInterface`1"))

#define CLASS_T_WEAK_OBJECT_PTR FString(TEXT("TWeakObjectPtr`1"))

#define CLASS_T_LAZY_OBJECT_PTR FString(TEXT("TLazyObjectPtr`1"))

#define CLASS_T_SOFT_OBJECT_PTR FString(TEXT("TSoftObjectPtr`1"))

#define CLASS_T_SOFT_CLASS_PTR FString(TEXT("TSoftClassPtr`1"))

#define CLASS_SCRIPT_STRUCT(T) TScriptStruct<T>::Get()

#define CLASS_SCRIPT_STRUCT_NAME(T) FString::Printf(TEXT("F%s"), *CLASS_SCRIPT_STRUCT(T)->GetName())
