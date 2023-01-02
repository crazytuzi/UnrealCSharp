#pragma once

#define COMBINE_CLASS(A, B) A.Append(".").Append(B)

#define CLASS_LOG FString(TEXT("Log"))

#define CLASS_PROPERTY_IMPLEMENTATION FString(TEXT("PropertyImplementation"))

#define CLASS_FUNCTION_IMPLEMENTATION FString(TEXT("FunctionImplementation"))

#define CLASS_STRUCT_IMPLEMENTATION FString(TEXT("StructImplementation"))

#define CLASS_ARRAY_IMPLEMENTATION FString(TEXT("ArrayImplementation"))

#define CLASS_MAP_IMPLEMENTATION FString(TEXT("MapImplementation"))

#define CLASS_SET_IMPLEMENTATION FString(TEXT("SetImplementation"))

#define CLASS_DELEGATE_IMPLEMENTATION FString(TEXT("DelegateImplementation"))

#define CLASS_MULTICAST_DELEGATE_IMPLEMENTATION FString(TEXT("MulticastDelegateImplementation"))

#define CLASS_INT_PTR FString(TEXT("IntPtr"))

#define CLASS_OBJECT_LIST FString(TEXT("ObjectList"))

#define CLASS_U_OBJECT FString(TEXT("UObject"))

#define CLASS_U_STRUCT FString(TEXT("UStruct"))

#define CLASS_F_STRING FString(TEXT("FString"))

#define CLASS_F_NAME FString(TEXT("FName"))

#define CLASS_F_TEXT FString(TEXT("FText"))

#define CLASS_UTILS FString(TEXT("Utils"))

#define CLASS_MULTICAST_DELEGATE_UTILS FString(TEXT("MulticastDelegateUtils"))

#define CLASS_T_ARRAY FString(TEXT("TArray`1"))

#define CLASS_T_MAP FString(TEXT("TMap`2"))

#define CLASS_T_SET FString(TEXT("TSet`1"))

#define CLASS_T_SUB_CLASS_OF FString(TEXT("TSubclassOf`1"))

#define CLASS_T_SCRIPT_INTERFACE FString(TEXT("TScriptInterface`1"))
