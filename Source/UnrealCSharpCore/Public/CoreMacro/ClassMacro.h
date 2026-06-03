#pragma once

#include "UEVersion.h"

#define COMBINE_FULL_NAME(A, B) FString::Printf(TEXT("%s.%s"), *A, *B)

#define COMBINE_GENERIC(Type, Arguments) FString::Printf(TEXT("%s`%s"), *Type, *Arguments)

#define CLASS_UTILS FString(TEXT("Utils"))

#define CLASS_SYNCHRONIZATION_CONTEXT FString(TEXT("SynchronizationContext"))

#if WITH_CORECLR
#define CLASS_OBJECT FString(TEXT("Object"))

#define CLASS_BOOLEAN FString(TEXT("Boolean"))

#define CLASS_SBYTE FString(TEXT("SByte"))

#define CLASS_INT16 FString(TEXT("Int16"))

#define CLASS_INT32 FString(TEXT("Int32"))

#define CLASS_INT64 FString(TEXT("Int64"))

#define CLASS_BYTE FString(TEXT("Byte"))

#define CLASS_UINT16 FString(TEXT("UInt16"))

#define CLASS_UINT32 FString(TEXT("UInt32"))

#define CLASS_UINT64 FString(TEXT("UInt64"))

#define CLASS_SINGLE FString(TEXT("Single"))

#define CLASS_DOUBLE FString(TEXT("Double"))

#define CLASS_ENUM FString(TEXT("Enum"))

#define CLASS_ASSEMBLY_LOADER FString(TEXT("AssemblyLoader"))

#define CLASS_HANDLE_DATA FString(TEXT("HandleData"))

#define CLASS_LOG_BRIDGE FString(TEXT("LogBridge"))

#define CLASS_TYPE_BRIDGE FString(TEXT("TypeBridge"))

#define CLASS_OBJECT_BRIDGE FString(TEXT("ObjectBridge"))

#define CLASS_FIELD_BRIDGE FString(TEXT("FieldBridge"))

#define CLASS_METHOD_BRIDGE FString(TEXT("MethodBridge"))

#define CLASS_STRING_BRIDGE FString(TEXT("StringBridge"))

#define CLASS_ARRAY_BRIDGE FString(TEXT("ArrayBridge"))
#endif

#define CLASS_F_STRING FString(TEXT("FString"))

#if UE_F_UTF8_STR_PROPERTY
#define CLASS_F_UTF8_STRING FString(TEXT("FUtf8String"))
#endif

#if UE_F_ANSI_STR_PROPERTY
#define CLASS_F_ANSI_STRING FString(TEXT("FAnsiString"))
#endif

#define CLASS_F_NAME FString(TEXT("FName"))

#define CLASS_F_TEXT FString(TEXT("FText"))

#define TEMPLATE_T_ARRAY FString(TEXT("TArray"))

#define GENERIC_T_ARRAY COMBINE_GENERIC(TEMPLATE_T_ARRAY, FString(TEXT("1")))

#define TEMPLATE_T_MAP FString(TEXT("TMap"))

#define GENERIC_T_MAP COMBINE_GENERIC(TEMPLATE_T_MAP, FString(TEXT("2")))

#define TEMPLATE_T_SET FString(TEXT("TSet"))

#define GENERIC_T_SET COMBINE_GENERIC(TEMPLATE_T_SET, FString(TEXT("1")))

#define TEMPLATE_T_SUB_CLASS_OF FString(TEXT("TSubclassOf"))

#define GENERIC_T_SUB_CLASS_OF COMBINE_GENERIC(TEMPLATE_T_SUB_CLASS_OF, FString(TEXT("1")))

#define TEMPLATE_T_SCRIPT_INTERFACE FString(TEXT("TScriptInterface"))

#define GENERIC_T_SCRIPT_INTERFACE COMBINE_GENERIC(TEMPLATE_T_SCRIPT_INTERFACE, FString(TEXT("1")))

#define TEMPLATE_T_WEAK_OBJECT_PTR FString(TEXT("TWeakObjectPtr"))

#define GENERIC_T_WEAK_OBJECT_PTR COMBINE_GENERIC(TEMPLATE_T_WEAK_OBJECT_PTR, FString(TEXT("1")))

#define TEMPLATE_T_LAZY_OBJECT_PTR FString(TEXT("TLazyObjectPtr"))

#define GENERIC_T_LAZY_OBJECT_PTR COMBINE_GENERIC(TEMPLATE_T_LAZY_OBJECT_PTR, FString(TEXT("1")))

#define TEMPLATE_T_SOFT_OBJECT_PTR FString(TEXT("TSoftObjectPtr"))

#define GENERIC_T_SOFT_OBJECT_PTR COMBINE_GENERIC(TEMPLATE_T_SOFT_OBJECT_PTR, FString(TEXT("1")))

#define TEMPLATE_T_SOFT_CLASS_PTR FString(TEXT("TSoftClassPtr"))

#define GENERIC_T_SOFT_CLASS_PTR COMBINE_GENERIC(TEMPLATE_T_SOFT_CLASS_PTR, FString(TEXT("1")))

#if UE_F_OPTIONAL_PROPERTY
#define TEMPLATE_T_OPTIONAL FString(TEXT("TOptional"))

#define GENERIC_T_OPTIONAL COMBINE_GENERIC(TEMPLATE_T_OPTIONAL, FString(TEXT("1")))
#endif
