#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/GenericAttributeMacro.h"
#include "CoreMacro/ClassAttributeMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "CoreMacro/FunctionAttributeMacro.h"

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
	
	UClassAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_CLASS_ATTRIBUTE)->GetClass();
	
	UStructAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_STRUCT_ATTRIBUTE)->GetClass();
	
	UEnumAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_ENUM_ATTRIBUTE)->GetClass();
	
	UPropertyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_PROPERTY_ATTRIBUTE)->GetClass();

	UFunctionAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_FUNCTION_ATTRIBUTE)->GetClass();
	
	UInterfaceAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_INTERFACE_ATTRIBUTE)->GetClass();
	
	
	
	
	VisibleInstanceOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_VISIBLE_INSTANCE_ONLY_ATTRIBUTE)->GetClass();
	
	BlueprintCallableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_CALLABLE_ATTRIBUTE)->GetClass();

	BlueprintAuthorityOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_AUTHORITY_ONLY_ATTRIBUTE)->GetClass();

	BlueprintGetterAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_GETTER_ATTRIBUTE)->GetClass();

	BlueprintSetterAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_SETTER_ATTRIBUTE)->GetClass();

	FieldNotifyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_FIELD_NOTIFY_ATTRIBUTE)->GetClass();

	TransientAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_TRANSIENT_ATTRIBUTE)->GetClass();

	ConfigAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CONFIG_ATTRIBUTE)->GetClass();

	BlueprintTypeAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_TYPE_ATTRIBUTE)->GetClass();

	NotBlueprintTypeAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NOT_BLUEPRINT_TYPE_ATTRIBUTE)->GetClass();
	
	BlueprintableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINTABLE_ATTRIBUTE)->GetClass();
	
	NotBlueprintableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NOT_BLUEPRINTABLE_ATTRIBUTE)->GetClass();
	
	NoExportAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NO_EXPORT_ATTRIBUTE)->GetClass();
	
	AbstractAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ABSTRACT_ATTRIBUTE)->GetClass();
	
	ExperimentalAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EXPERIMENTAL_ATTRIBUTE)->GetClass();
	
	EditorConfigAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EDITOR_CONFIG_ATTRIBUTE)->GetClass();
	
	CategoryAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CATEGORY_ATTRIBUTE)->GetClass();
	
	BlueprintInternalUseOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_INTERNAL_USE_ONLY_ATTRIBUTE)->GetClass();
	
	
	
	ClassGroupAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CLASS_GROUP_ATTRIBUTE)->GetClass();
	
	WithinAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_WITHIN_ATTRIBUTE)->GetClass();
	
	MinimalAPIAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_MINIMAL_API_ATTRIBUTE)->GetClass();
	
	CustomConstructorAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CUSTOM_CONSTRUCTOR_ATTRIBUTE)->GetClass();
	
	IntrinsicAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_INTRINSIC_ATTRIBUTE)->GetClass();
	
	NotPlaceableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NOT_PLACEABLE_ATTRIBUTE)->GetClass();
	
	DefaultToInstancedAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DEFAULT_TO_INSTANCED_ATTRIBUTE)->GetClass();
	
	ConstAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CONST_ATTRIBUTE)->GetClass();
	
	DeprecatedAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DEPRECATED_ATTRIBUTE)->GetClass();
	
	PerObjectConfigAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_PER_OBJECT_CONFIG_ATTRIBUTE)->GetClass();
	
	ConfigDoNotCheckDefaultsAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CONFIG_DO_NOT_CHECK_DEFAULTS_ATTRIBUTE)->GetClass();
	
	DefaultConfigAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DEFAULT_CONFIG_ATTRIBUTE)->GetClass();
	
	EditInlineNewAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EDIT_INLINE_NEW_ATTRIBUTE)->GetClass();
	
	NotEditInlineNewAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NOT_EDIT_INLINE_NEW_ATTRIBUTE)->GetClass();
	
	HideDropdownAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_HIDE_DROP_DOWN_ATTRIBUTE)->GetClass();
	
	ShowCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SHOW_CATEGORIES_ATTRIBUTE)->GetClass();
	
	HideCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_HIDE_CATEGORIES_ATTRIBUTE)->GetClass();
	
	ComponentWrapperClassAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_COMPONENT_WRAPPER_CLASS_ATTRIBUTE)->GetClass();
	
	HideFunctionsAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_HIDE_FUNCTIONS_ATTRIBUTE)->GetClass();
	
	AutoExpandCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_AUTO_EXPAND_CATEGORIES_ATTRIBUTE)->GetClass();
	
	AutoCollapseCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_AUTO_COLLAPSE_CATEGORIES_ATTRIBUTE)->GetClass();
	
	CollapseCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_COLLAPSE_CATEGORIES_ATTRIBUTE)->GetClass();
	
	DontCollapseCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DONT_COLLAPSE_CATEGORIES_ATTRIBUTE)->GetClass();
	
	PrioritizeCategoriesAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_PRIORITIZE_CATEGORIES_ATTRIBUTE)->GetClass();
	
	AdvancedClassDisplayAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ADVANCED_CLASS_DISPLAY_ATTRIBUTE)->GetClass();
	
	ConversionRootAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CONVERSION_ROOT_ATTRIBUTE)->GetClass();

	EarlyAccessPreviewAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EARLY_ACCESS_PREVIEW_ATTRIBUTE)->GetClass();

	SparseClassDataTypeAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SPARSE_CLASS_DATA_TYPE_ATTRIBUTE)->GetClass();

	CannotImplementInterfaceInBlueprintAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CANNOT_IMPLEMENT_INTERFACE_IN_BLUEPRINT_ATTRIBUTE)->GetClass();

	GlobalConfigAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_GLOBAL_CONFIG_ATTRIBUTE)->GetClass();

	LocalizedAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_LOCALIZED_ATTRIBUTE)->GetClass();

	DuplicateTransientAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DUPLICATE_TRANSIENT_ATTRIBUTE)->GetClass();

	NonPIETransientAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NON_PIE_TRANSIENT_ATTRIBUTE)->GetClass();

	NonPIEDuplicateTransientAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NON_PIE_DUPLICATE_TRANSIENT_ATTRIBUTE)->GetClass();

	ExportAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EXPORT_ATTRIBUTE)->GetClass();

	NoClearAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NO_CLEAR_ATTRIBUTE)->GetClass();

	EditFixedSizeAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EDIT_FIXED_SIZE_ATTRIBUTE)->GetClass();

	ReplicatedAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_REPLICATED_ATTRIBUTE)->GetClass();

	ReplicatedUsingAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_REPLICATED_USING_ATTRIBUTE)->GetClass();

	NotReplicatedAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NOT_REPLICATED_ATTRIBUTE)->GetClass();

	InterpAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_INTERP_ATTRIBUTE)->GetClass();

	NonTransactionalAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NON_TRANSACTIONAL_ATTRIBUTE)->GetClass();

	InstancedAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_INSTANCED_ATTRIBUTE)->GetClass();

	BlueprintAssignableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_ASSIGNABLE_ATTRIBUTE)->GetClass();
	
	SimpleDisplayAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SIMPLE_DISPLAY_ATTRIBUTE)->GetClass();
	
	AdvancedDisplayAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ADVANCED_DISPLAY_ATTRIBUTE)->GetClass();
	
	EditAnywhereAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EDIT_ANYWHERE_ATTRIBUTE)->GetClass();
	
	EditInstanceOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EDIT_INSTANCE_ONLY_ATTRIBUTE)->GetClass();
	
	EditDefaultsOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EDIT_DEFAULTS_ONLY_ATTRIBUTE)->GetClass();
	
	VisibleAnywhereAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_VISIBLE_ANYWHERE_ATTRIBUTE)->GetClass();
	
	VisibleDefaultsOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_VISIBLE_DEFAULTS_ONLY_ATTRIBUTE)->GetClass();
	
	BlueprintReadOnlyAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_READ_ONLY_ATTRIBUTE)->GetClass();
	
	BlueprintReadWriteAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_READ_WRITE_ATTRIBUTE)->GetClass();
	
	AssetRegistrySearchableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ASSET_REGISTRY_SEARCHABLE_ATTRIBUTE)->GetClass();
	
	SaveGameAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SAVE_GAME_ATTRIBUTE)->GetClass();
	
	TextExportTransientAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_TEXT_EXPORT_TRANSIENT_ATTRIBUTE)->GetClass();
	
	SkipSerializationAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SKIP_SERIALIZATION_ATTRIBUTE)->GetClass();
	
	DefaultSubObjectAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DEFAULT_SUB_OBJECT_ATTRIBUTE)->GetClass();
	
	RootComponentAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ROOT_COMPONENT_ATTRIBUTE)->GetClass();
	
	AttachmentParentAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ATTACHMENT_PARENT_ATTRIBUTE)->GetClass();
	
	AttachmentSocketNameAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_ATTACHMENT_SOCKET_NAME_ATTRIBUTE)->GetClass();
	
	DefaultValueAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_DEFAULT_VALUE_ATTRIBUTE)->GetClass();
	
	
	BlueprintImplementableEventAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_IMPLEMENTABLE_EVENT_ATTRIBUTE)->GetClass();

	SealedEventAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SEALED_EVENT_ATTRIBUTE)->GetClass();

	ExecAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_EXEC_ATTRIBUTE)->GetClass();

	ServerAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SERVER_ATTRIBUTE)->GetClass();

	ClientAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CLIENT_ATTRIBUTE)->GetClass();

	NetMulticastAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_NET_MULTICAST_ATTRIBUTE)->GetClass();

	ReliableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_RELIABLE_ATTRIBUTE)->GetClass();

	UnreliableAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_UNRELIABLE_ATTRIBUTE)->GetClass();

	BlueprintPureAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_PURE_ATTRIBUTE)->GetClass();

	BlueprintCosmeticAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_BLUEPRINT_COSMETIC_ATTRIBUTE)->GetClass();

	CallInEditorAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CALL_IN_EDITOR_ATTRIBUTE)->GetClass();

	CustomThunkAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_CUSTOM_THUNK_ATTRIBUTE)->GetClass();

	WithValidationAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_WITH_VALIDATION_ATTRIBUTE)->GetClass();

	ServiceRequestAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SERVICE_REQUEST_ATTRIBUTE)->GetClass();

	ServiceResponseAttribute_Class = GetClassReflection(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_SERVICE_RESPONSE_ATTRIBUTE)->GetClass();
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

MonoClass* FReflectionRegistry::GetUClassAttribute_Class() const
{
	return UClassAttribute_Class;
}

MonoClass* FReflectionRegistry::GetUStructAttribute_Class() const
{
	return UStructAttribute_Class;
}

MonoClass* FReflectionRegistry::GetUEnumAttribute_Class() const
{
	return UEnumAttribute_Class;
}

MonoClass* FReflectionRegistry::GetUInterfaceAttribute_Class() const
{
	return UInterfaceAttribute_Class;
}

MonoClass* FReflectionRegistry::GetUPropertyAttribute_Class() const
{
	return UPropertyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetUFunctionAttribute_Class() const
{
	return UFunctionAttribute_Class;
}

MonoClass* FReflectionRegistry::GetVisibleInstanceOnlyAttribute_Class() const
{
	return VisibleInstanceOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintCallableAttribute_Class() const
{
	return BlueprintCallableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintAuthorityOnlyAttribute_Class() const
{
	return BlueprintAuthorityOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintGetterAttribute_Class() const
{
	return BlueprintGetterAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintSetterAttribute_Class() const
{
	return BlueprintSetterAttribute_Class;
}

MonoClass* FReflectionRegistry::GetFieldNotifyAttribute_Class() const
{
	return FieldNotifyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetTransientAttribute_Class() const
{
	return TransientAttribute_Class;
}

MonoClass* FReflectionRegistry::GetConfigAttribute_Class() const
{
	return ConfigAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintTypeAttribute_Class() const
{
	return BlueprintTypeAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNotBlueprintTypeAttribute_Class() const
{
	return NotBlueprintTypeAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintableAttribute_Class() const
{
	return BlueprintableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNotBlueprintableAttribute_Class() const
{
	return NotBlueprintableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNoExportAttribute_Class() const
{
	return NoExportAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAbstractAttribute_Class() const
{
	return AbstractAttribute_Class;
}

MonoClass* FReflectionRegistry::GetExperimentalAttribute_Class() const
{
	return ExperimentalAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEditorConfigAttribute_Class() const
{
	return EditorConfigAttribute_Class;
}

MonoClass* FReflectionRegistry::GetCategoryAttribute_Class() const
{
	return CategoryAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintInternalUseOnlyAttribute_Class() const
{
	return BlueprintInternalUseOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetClassGroupAttribute_Class() const
{
	return ClassGroupAttribute_Class;
}

MonoClass* FReflectionRegistry::GetWithinAttribute_Class() const
{
	return WithinAttribute_Class;
}

MonoClass* FReflectionRegistry::GetMinimalAPIAttribute_Class() const
{
	return MinimalAPIAttribute_Class;
}

MonoClass* FReflectionRegistry::GetCustomConstructorAttribute_Class() const
{
	return CustomConstructorAttribute_Class;
}

MonoClass* FReflectionRegistry::GetIntrinsicAttribute_Class() const
{
	return IntrinsicAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNotPlaceableAttribute_Class() const
{
	return NotPlaceableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDefaultToInstancedAttribute_Class() const
{
	return DefaultToInstancedAttribute_Class;
}

MonoClass* FReflectionRegistry::GetConstAttribute_Class() const
{
	return ConstAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDeprecatedAttribute_Class() const
{
	return DeprecatedAttribute_Class;
}

MonoClass* FReflectionRegistry::GetPerObjectConfigAttribute_Class() const
{
	return PerObjectConfigAttribute_Class;
}

MonoClass* FReflectionRegistry::GetConfigDoNotCheckDefaultsAttribute_Class() const
{
	return ConfigDoNotCheckDefaultsAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDefaultConfigAttribute_Class() const
{
	return DefaultConfigAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEditInlineNewAttribute_Class() const
{
	return EditInlineNewAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNotEditInlineNewAttribute_Class() const
{
	return NotEditInlineNewAttribute_Class;
}

MonoClass* FReflectionRegistry::GetHideDropdownAttribute_Class() const
{
	return HideDropdownAttribute_Class;
}

MonoClass* FReflectionRegistry::GetShowCategoriesAttribute_Class() const
{
	return ShowCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetHideCategoriesAttribute_Class() const
{
	return HideCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetComponentWrapperClassAttribute_Class() const
{
	return ComponentWrapperClassAttribute_Class;
}

MonoClass* FReflectionRegistry::GetHideFunctionsAttribute_Class() const
{
	return HideFunctionsAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAutoExpandCategoriesAttribute_Class() const
{
	return AutoExpandCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAutoCollapseCategoriesAttribute_Class() const
{
	return AutoCollapseCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetCollapseCategoriesAttribute_Class() const
{
	return CollapseCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDontCollapseCategoriesAttribute_Class() const
{
	return DontCollapseCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetPrioritizeCategoriesAttribute_Class() const
{
	return PrioritizeCategoriesAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAdvancedClassDisplayAttribute_Class() const
{
	return AdvancedClassDisplayAttribute_Class;
}

MonoClass* FReflectionRegistry::GetConversionRootAttribute_Class() const
{
	return ConversionRootAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEarlyAccessPreviewAttribute_Class() const
{
	return EarlyAccessPreviewAttribute_Class;
}

MonoClass* FReflectionRegistry::GetSparseClassDataTypeAttribute_Class() const
{
	return SparseClassDataTypeAttribute_Class;
}

MonoClass* FReflectionRegistry::GetCannotImplementInterfaceInBlueprintAttribute_Class() const
{
	return CannotImplementInterfaceInBlueprintAttribute_Class;
}

MonoClass* FReflectionRegistry::GetGlobalConfigAttribute_Class() const
{
	return GlobalConfigAttribute_Class;
}

MonoClass* FReflectionRegistry::GetLocalizedAttribute_Class() const
{
	return LocalizedAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDuplicateTransientAttribute_Class() const
{
	return DuplicateTransientAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNonPIETransientAttribute_Class() const
{
	return NonPIETransientAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNonPIEDuplicateTransientAttribute_Class() const
{
	return NonPIEDuplicateTransientAttribute_Class;
}

MonoClass* FReflectionRegistry::GetExportAttribute_Class() const
{
	return ExportAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNoClearAttribute_Class() const
{
	return NoClearAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEditFixedSizeAttribute_Class() const
{
	return EditFixedSizeAttribute_Class;
}

MonoClass* FReflectionRegistry::GetReplicatedAttribute_Class() const
{
	return ReplicatedAttribute_Class;
}

MonoClass* FReflectionRegistry::GetReplicatedUsingAttribute_Class() const
{
	return ReplicatedUsingAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNotReplicatedAttribute_Class() const
{
	return NotReplicatedAttribute_Class;
}

MonoClass* FReflectionRegistry::GetInterpAttribute_Class() const
{
	return InterpAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNonTransactionalAttribute_Class() const
{
	return NonTransactionalAttribute_Class;
}

MonoClass* FReflectionRegistry::GetInstancedAttribute_Class() const
{
	return InstancedAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintAssignableAttribute_Class() const
{
	return BlueprintAssignableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetSimpleDisplayAttribute_Class() const
{
	return SimpleDisplayAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAdvancedDisplayAttribute_Class() const
{
	return AdvancedDisplayAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEditAnywhereAttribute_Class() const
{
	return EditAnywhereAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEditInstanceOnlyAttribute_Class() const
{
	return EditInstanceOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetEditDefaultsOnlyAttribute_Class() const
{
	return EditDefaultsOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetVisibleAnywhereAttribute_Class() const
{
	return VisibleAnywhereAttribute_Class;
}

MonoClass* FReflectionRegistry::GetVisibleDefaultsOnlyAttribute_Class() const
{
	return VisibleDefaultsOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintReadOnlyAttribute_Class() const
{
	return BlueprintReadOnlyAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintReadWriteAttribute_Class() const
{
	return BlueprintReadWriteAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAssetRegistrySearchableAttribute_Class() const
{
	return AssetRegistrySearchableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetSaveGameAttribute_Class() const
{
	return SaveGameAttribute_Class;
}

MonoClass* FReflectionRegistry::GetTextExportTransientAttribute_Class() const
{
	return TextExportTransientAttribute_Class;
}

MonoClass* FReflectionRegistry::GetSkipSerializationAttribute_Class() const
{
	return SkipSerializationAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDefaultSubObjectAttribute_Class() const
{
	return DefaultSubObjectAttribute_Class;
}

MonoClass* FReflectionRegistry::GetRootComponentAttribute_Class() const
{
	return RootComponentAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAttachmentParentAttribute_Class() const
{
	return AttachmentParentAttribute_Class;
}

MonoClass* FReflectionRegistry::GetAttachmentSocketNameAttribute_Class() const
{
	return AttachmentSocketNameAttribute_Class;
}

MonoClass* FReflectionRegistry::GetDefaultValueAttribute_Class() const
{
	return DefaultValueAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintImplementableEventAttribute_Class() const
{
	return BlueprintImplementableEventAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintNativeEventAttribute_Class() const
{
	return BlueprintNativeEventAttribute_Class;
}

MonoClass* FReflectionRegistry::GetSealedEventAttribute_Class() const
{
	return SealedEventAttribute_Class;
}

MonoClass* FReflectionRegistry::GetExecAttribute_Class() const
{
	return ExecAttribute_Class;
}

MonoClass* FReflectionRegistry::GetServerAttribute_Class() const
{
	return ServerAttribute_Class;
}

MonoClass* FReflectionRegistry::GetClientAttribute_Class() const
{
	return ClientAttribute_Class;
}

MonoClass* FReflectionRegistry::GetNetMulticastAttribute_Class() const
{
	return NetMulticastAttribute_Class;
}

MonoClass* FReflectionRegistry::GetReliableAttribute_Class() const
{
	return ReliableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetUnreliableAttribute_Class() const
{
	return UnreliableAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintPureAttribute_Class() const
{
	return BlueprintPureAttribute_Class;
}

MonoClass* FReflectionRegistry::GetBlueprintCosmeticAttribute_Class() const
{
	return BlueprintCosmeticAttribute_Class;
}

MonoClass* FReflectionRegistry::GetCallInEditorAttribute_Class() const
{
	return CallInEditorAttribute_Class;
}

MonoClass* FReflectionRegistry::GetCustomThunkAttribute_Class() const
{
	return CustomThunkAttribute_Class;
}

MonoClass* FReflectionRegistry::GetWithValidationAttribute_Class() const
{
	return WithinAttribute_Class;
}

MonoClass* FReflectionRegistry::GetServiceRequestAttribute_Class() const
{
	return ServiceRequestAttribute_Class;
}

MonoClass* FReflectionRegistry::GetServiceResponseAttribute_Class() const
{
	return ServiceResponseAttribute_Class;
}

FClassReflection* FReflectionRegistry::Get_Utils_Class() const
{
	return Utils_Class;
}

void FReflectionRegistry::Reset()
{
	ClassReflection.Empty();
	
	ClassReflection1.Empty();
}
