#pragma once

#include "UEVersion.h"
#include "FClassReflection.h"

class UNREALCSHARPCORE_API FReflectionRegistry
{
public:
	static FReflectionRegistry& Get();
	
public:
	FReflectionRegistry();
	
public:
	void Initialize();

	void Deinitialize();
	
public:
	FClassReflection* GetClassReflection(const TWeakObjectPtr<UField>& InStruct);
	
	FClassReflection* GetClassReflection(MonoClass* InStruct);
	
	FClassReflection* GetClassReflection(const FString& InNameSpace, const FString& InMonoClassName);
	
	template <class T>
	auto GetClassReflection() -> FClassReflection*;
	
	MonoClass* Get_Byte_Class() const;

	MonoClass* Get_Object_Class() const;

	MonoClass* Get_UInt16_Class() const;

	MonoClass* Get_UInt32_Class() const;

	MonoClass* Get_UInt64_Class() const;

	MonoClass* Get_SByte_Class() const;

	MonoClass* Get_Int16_Class() const;

	MonoClass* Get_Int32_Class() const;

	MonoClass* Get_Int64_Class() const;

	MonoClass* Get_Boolean_Class() const;

	MonoClass* Get_Single_Class() const;

	MonoClass* Get_Enum_Class() const;

	MonoClass* Get_Double_Class() const;
	
	MonoClass* Get_UClass_Class() const;
	
	MonoClass* Get_UObject_Class() const;
	
	MonoClass* Get_TSubclassOf_Class() const;
	
	MonoClass* Get_Name_Class() const;
	
	MonoClass* Get_TScriptInterface_Class();
	
	MonoClass* Get_String_Class() const;
	
#if UE_F_UTF8_STR_PROPERTY
	MonoClass* Get_Utf8String_Class() const;
#endif
	
#if UE_F_ANSI_STR_PROPERTY
	MonoClass* Get_AnsiString_Class() const;
#endif
	
	MonoClass* Get_Text_Class() const;
	
	MonoClass* Get_TWeakObjectPtr_Class() const;
	
	MonoClass* Get_TLazyObjectPtr_Class() const;
	
	MonoClass* Get_TSoftClassPtr_Class() const;
	
	MonoClass* Get_TSoftObjectPtr_Class() const;
	
	MonoClass* Get_TMap_Class() const;
	
	MonoClass* Get_TSet_Class() const;
	
	MonoClass* GetTArray_Class() const;
	
	static FClassReflection* Get_Utils_Class();
	
	void Reset();
	
public:
	MonoClass* Byte_Class;

	MonoClass* Object_Class;

	MonoClass* UInt16_Class;

	MonoClass* UInt32_Class;

	MonoClass* UInt64_Class;

	MonoClass* SByte_Class;

	MonoClass* Int16_Class;

	MonoClass* Int32_Class;

	MonoClass* Int64_Class;

	MonoClass* Boolean_Class;

	MonoClass* Single_Class;

	MonoClass* Enum_Class;

	MonoClass* Double_Class;
	
	MonoClass* UClass_Class;
	
	MonoClass* TSubclassOf_Class;
	
	MonoClass* UObject_Class;
	
	MonoClass* Name_Class;
	
	MonoClass* TScriptInterface_Class;
	
	MonoClass* String_Class;
	
#if UE_F_UTF8_STR_PROPERTY
	MonoClass* Utf8String_Class;
#endif
	
#if UE_F_ANSI_STR_PROPERTY
	MonoClass* AnsiString_Class;
#endif
	
	MonoClass* Text_Class;
	
	MonoClass* TWeakObjectPtr_Class;
	
	MonoClass* TLazyObjectPtr_Class;
	
	MonoClass* TSoftClassPtr_Class;
	
	MonoClass* TSoftObjectPtr_Class;
	
	MonoClass* TMap_Class;
	
	MonoClass* TSet_Class;
	
	MonoClass* TArray_Class;
	
	static inline FClassReflection* Utils_Class{};
	
public:
	TMap<TWeakObjectPtr<UField>, FClassReflection*> ClassReflection;
	
	TMap<MonoClass*, FClassReflection*> ClassReflection1;
	
	TMap<TPair<FString, FString>, FClassReflection*> ClassReflection2;
};

#include "FReflectionRegistry.inl"
