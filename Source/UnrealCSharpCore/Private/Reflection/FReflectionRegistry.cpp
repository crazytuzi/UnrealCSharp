#include "Reflection/FReflectionRegistry.h"

FReflectionRegistry& FReflectionRegistry::Get()
{
	static FReflectionRegistry ReflectionRegistry;
	
	return ReflectionRegistry;
}

FReflectionRegistry::FReflectionRegistry()
{
}

void FReflectionRegistry::Initialize()
{
	Byte_Class = FMonoDomain::Get_Byte_Class();
	
	Object_Class = FMonoDomain::Get_Object_Class();
	
	UInt16_Class = FMonoDomain::Get_UInt16_Class();
	
	UInt32_Class = FMonoDomain::Get_UInt32_Class();
	
	UInt64_Class = FMonoDomain::Get_UInt64_Class();
	
	SByte_Class = FMonoDomain::Get_SByte_Class();
	
	Int16_Class = FMonoDomain::Get_Int16_Class();
	
	Int32_Class = FMonoDomain::Get_Int32_Class();
	
	Int64_Class = FMonoDomain::Get_Int64_Class();
	
	Boolean_Class = FMonoDomain::Get_Boolean_Class();
	
	Single_Class = FMonoDomain::Get_Single_Class();
	
	Enum_Class = FMonoDomain::Get_Enum_Class();
	
	Double_Class = FMonoDomain::Get_Double_Class();
	
	Utils_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);
	
	UClass_Class = GetClassReflection(UClass::StaticClass())->GetClass();
	
	TSubclassOf_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SUB_CLASS_OF)->GetClass();
	
	UObject_Class = GetClassReflection(UObject::StaticClass())->GetClass();
	
	Name_Class = GetClassReflection<FName>()->GetClass();
	
	TScriptInterface_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SCRIPT_INTERFACE)->GetClass();
	
	String_Class = GetClassReflection<FString>()->GetClass();
	
#if UE_F_UTF8_STR_PROPERTY
	Utf8String_Class = GetClassReflection<FUtf8String>()->GetClass();
#endif
	
#if UE_F_ANSI_STR_PROPERTY
	AnsiString_Class = GetClassReflection<FAnsiString>()->GetClass();
#endif
	
	Text_Class = GetClassReflection<FText>()->GetClass();
	
	TWeakObjectPtr_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_WEAK_OBJECT_PTR)->GetClass();

	TLazyObjectPtr_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_LAZY_OBJECT_PTR)->GetClass();
	
	TSoftClassPtr_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_CLASS_PTR)->GetClass();

	TSoftObjectPtr_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_OBJECT_PTR)->GetClass();

	TMap_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_MAP)->GetClass();
	
	TSet_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SET)->GetClass();
	
	TArray_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_ARRAY)->GetClass();
	
#if UE_F_OPTIONAL_PROPERTY
	TOptional_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_OPTIONAL)->GetClass();
#endif
}

void FReflectionRegistry::Deinitialize()
{
	ClassReflection.Empty();
	
	ClassReflection1.Empty();
	
	ClassReflection2.Empty();
}

FClassReflection* FReflectionRegistry::GetClassReflection(const TWeakObjectPtr<UField>& InStruct)
{
	if (const auto FoundClassReflection = ClassReflection.Find(InStruct))
	{
		return *FoundClassReflection;
	}
	
	if (const auto FoundMonoClass = FClassReflection::GetMonoClass(InStruct))
	{
		auto Class = new FClassReflection(InStruct, FoundMonoClass);
		
		ClassReflection.Add(InStruct, Class);
		
		ClassReflection1.Add(FoundMonoClass, Class);
		
		return Class;
	}
	
	return nullptr;
}

FClassReflection* FReflectionRegistry::GetClassReflection(MonoClass* InStruct)
{
	if (const auto FoundClassReflection = ClassReflection1.Find(InStruct))
	{
		return *FoundClassReflection;
	}
	
	return ClassReflection1.Add(InStruct, new FClassReflection(InStruct));
}

FClassReflection* FReflectionRegistry::GetClassReflection(const FString& InNameSpace, const FString& InMonoClassName)
{
	auto Pair = TPair<FString, FString>(InNameSpace, InMonoClassName);
	
	if (const auto FoundClassReflection = ClassReflection2.Find(Pair))
	{
		return *FoundClassReflection;
	}
	
	if (auto Class1 = FMonoDomain::Class_From_Name(InNameSpace, InMonoClassName))
	{
		auto Class = new FClassReflection(InMonoClassName, Class1);
		
		ClassReflection1.Add(Class1, Class);
		
		ClassReflection2.Add(Pair, Class);
		
		return Class;
	}
	
	return nullptr;
}

MonoClass* FReflectionRegistry::Get_Byte_Class() const
{
	return Byte_Class;
}

MonoClass* FReflectionRegistry::Get_Object_Class() const
{
	return Object_Class;
}

MonoClass* FReflectionRegistry::Get_UInt16_Class() const
{
	return UInt16_Class;
}

MonoClass* FReflectionRegistry::Get_UInt32_Class() const
{
	return UInt32_Class;
}

MonoClass* FReflectionRegistry::Get_UInt64_Class() const
{
	return UInt64_Class;
}

MonoClass* FReflectionRegistry::Get_SByte_Class() const
{
	return SByte_Class;
}

MonoClass* FReflectionRegistry::Get_Int16_Class() const
{
	return Int16_Class;
}

MonoClass* FReflectionRegistry::Get_Int32_Class() const
{
	return Int32_Class;
}

MonoClass* FReflectionRegistry::Get_Int64_Class() const
{
	return Int64_Class;
}

MonoClass* FReflectionRegistry::Get_Boolean_Class() const
{
	return Boolean_Class;
}

MonoClass* FReflectionRegistry::Get_Single_Class() const
{
	return Single_Class;
}

MonoClass* FReflectionRegistry::Get_Enum_Class() const
{
	return Enum_Class;
}

MonoClass* FReflectionRegistry::Get_Double_Class() const
{
	return Double_Class;
}

MonoClass* FReflectionRegistry::Get_UClass_Class() const
{
	return UClass_Class;
}

MonoClass* FReflectionRegistry::Get_UObject_Class() const
{
	return UObject_Class;
}

MonoClass* FReflectionRegistry::Get_TSubclassOf_Class() const
{
	return TSubclassOf_Class;
}

MonoClass* FReflectionRegistry::Get_Name_Class() const
{
	return Name_Class;
}

MonoClass* FReflectionRegistry::Get_TScriptInterface_Class()
{
	return TScriptInterface_Class;
}

MonoClass* FReflectionRegistry::Get_String_Class() const
{
	return String_Class;
}

#if UE_F_UTF8_STR_PROPERTY
MonoClass* FReflectionRegistry::Get_Utf8String_Class() const
{
	return Utf8String_Class;
}
#endif

#if UE_F_ANSI_STR_PROPERTY
MonoClass* FReflectionRegistry::Get_AnsiString_Class() const
{
	return AnsiString_Class;
}
#endif

MonoClass* FReflectionRegistry::Get_Text_Class() const
{
	return Text_Class;
}

MonoClass* FReflectionRegistry::Get_TWeakObjectPtr_Class() const
{
	return TWeakObjectPtr_Class;
}

MonoClass* FReflectionRegistry::Get_TLazyObjectPtr_Class() const
{
	return TLazyObjectPtr_Class;
}

MonoClass* FReflectionRegistry::Get_TSoftClassPtr_Class() const
{
	return TSoftClassPtr_Class;
}

MonoClass* FReflectionRegistry::Get_TSoftObjectPtr_Class() const
{
	return TSoftObjectPtr_Class;
}

MonoClass* FReflectionRegistry::Get_TMap_Class() const
{
	return TMap_Class;
}

MonoClass* FReflectionRegistry::Get_TSet_Class() const
{
	return TSet_Class;
}

MonoClass* FReflectionRegistry::GetTArray_Class() const
{
	return TArray_Class;
}

#if UE_F_OPTIONAL_PROPERTY
MonoClass* FReflectionRegistry::GetTOptional_Class() const
{
	return TOptional_Class;
}
#endif

FClassReflection* FReflectionRegistry::Get_Utils_Class()
{
	return Utils_Class;
}

void FReflectionRegistry::Reset()
{
	ClassReflection.Empty();
	
	ClassReflection1.Empty();
}
