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
	
#if UE_F_OPTIONAL_PROPERTY
	MonoClass* GetTOptional_Class() const;
#endif
	
	MonoClass* GetUClassAttribute_Class() const;
	
	MonoClass* GetUStructAttribute_Class() const;
	
	MonoClass* GetUEnumAttribute_Class() const;
	
	MonoClass* GetUInterfaceAttribute_Class() const;
	
	MonoClass* GetUPropertyAttribute_Class() const;
	
	MonoClass* GetUFunctionAttribute_Class() const;
	
	
	
	MonoClass* GetVisibleInstanceOnlyAttribute_Class() const;
	
	MonoClass* GetBlueprintCallableAttribute_Class() const;
	
	MonoClass* GetBlueprintAuthorityOnlyAttribute_Class() const;
	
	MonoClass* GetBlueprintGetterAttribute_Class() const;
	
	MonoClass* GetBlueprintSetterAttribute_Class() const;
	
	MonoClass* GetFieldNotifyAttribute_Class() const;
	
	MonoClass* GetTransientAttribute_Class() const;
	
	MonoClass* GetConfigAttribute_Class() const;
	
	MonoClass* GetBlueprintTypeAttribute_Class() const;
	
	MonoClass* GetNotBlueprintTypeAttribute_Class() const;
	
	MonoClass* GetBlueprintableAttribute_Class() const;
	
	MonoClass* GetNotBlueprintableAttribute_Class() const;
	
	MonoClass* GetNoExportAttribute_Class() const;
	
	MonoClass* GetAbstractAttribute_Class() const;
	
	MonoClass* GetExperimentalAttribute_Class() const;
	
	MonoClass* GetEditorConfigAttribute_Class() const;
	
	MonoClass* GetCategoryAttribute_Class() const;
	
	MonoClass* GetBlueprintInternalUseOnlyAttribute_Class() const;
	
	
	
	MonoClass* GetClassGroupAttribute_Class() const;
	
	MonoClass* GetWithinAttribute_Class() const;
	
	MonoClass* GetMinimalAPIAttribute_Class() const;
	
	MonoClass* GetCustomConstructorAttribute_Class() const;
	
	MonoClass* GetIntrinsicAttribute_Class() const;
	
	MonoClass* GetNotPlaceableAttribute_Class() const;
	
	MonoClass* GetDefaultToInstancedAttribute_Class() const;
	
	MonoClass* GetConstAttribute_Class() const;
	
	MonoClass* GetDeprecatedAttribute_Class() const;
	
	MonoClass* GetPerObjectConfigAttribute_Class() const;
	
	MonoClass* GetConfigDoNotCheckDefaultsAttribute_Class() const;
	
	MonoClass* GetDefaultConfigAttribute_Class() const;
	
	MonoClass* GetEditInlineNewAttribute_Class() const;
	
	MonoClass* GetNotEditInlineNewAttribute_Class() const;
	
	MonoClass* GetHideDropdownAttribute_Class() const;
	
	MonoClass* GetShowCategoriesAttribute_Class() const;
	
	MonoClass* GetHideCategoriesAttribute_Class() const;
	
	MonoClass* GetComponentWrapperClassAttribute_Class() const;
	
	MonoClass* GetHideFunctionsAttribute_Class() const;
	
	MonoClass* GetAutoExpandCategoriesAttribute_Class() const;
	
	MonoClass* GetAutoCollapseCategoriesAttribute_Class() const;
	
	MonoClass* GetCollapseCategoriesAttribute_Class() const;
	
	MonoClass* GetDontCollapseCategoriesAttribute_Class() const;
	
	MonoClass* GetPrioritizeCategoriesAttribute_Class() const;
	
	MonoClass* GetAdvancedClassDisplayAttribute_Class() const;
	
	MonoClass* GetConversionRootAttribute_Class() const;
	
	MonoClass* GetEarlyAccessPreviewAttribute_Class() const;
	
	MonoClass* GetSparseClassDataTypeAttribute_Class() const;
	
	MonoClass* GetCannotImplementInterfaceInBlueprintAttribute_Class() const;
	
	
	MonoClass* GetGlobalConfigAttribute_Class() const;
	
	MonoClass* GetLocalizedAttribute_Class() const;
	
	MonoClass* GetDuplicateTransientAttribute_Class() const;
	
	MonoClass* GetNonPIETransientAttribute_Class() const;
	
	MonoClass* GetNonPIEDuplicateTransientAttribute_Class() const;
	
	MonoClass* GetExportAttribute_Class() const;
	
	MonoClass* GetNoClearAttribute_Class() const;
	
	MonoClass* GetEditFixedSizeAttribute_Class() const;
	
	MonoClass* GetReplicatedAttribute_Class() const;
	
	MonoClass* GetReplicatedUsingAttribute_Class() const;
	
	MonoClass* GetNotReplicatedAttribute_Class() const;
	
	MonoClass* GetInterpAttribute_Class() const;
	
	MonoClass* GetNonTransactionalAttribute_Class() const;
	
	MonoClass* GetInstancedAttribute_Class() const;
	
	MonoClass* GetBlueprintAssignableAttribute_Class() const;
	
	MonoClass* GetSimpleDisplayAttribute_Class() const;
	
	MonoClass* GetAdvancedDisplayAttribute_Class() const;
	
	MonoClass* GetEditAnywhereAttribute_Class() const;
	
	MonoClass* GetEditInstanceOnlyAttribute_Class() const;
	
	MonoClass* GetEditDefaultsOnlyAttribute_Class() const;
	
	MonoClass* GetVisibleAnywhereAttribute_Class() const;
	
	MonoClass* GetVisibleDefaultsOnlyAttribute_Class() const;
	
	MonoClass* GetBlueprintReadOnlyAttribute_Class() const;
	
	MonoClass* GetBlueprintReadWriteAttribute_Class() const;
	
	MonoClass* GetAssetRegistrySearchableAttribute_Class() const;
	
	MonoClass* GetSaveGameAttribute_Class() const;
	
	MonoClass* GetTextExportTransientAttribute_Class() const;
	
	MonoClass* GetSkipSerializationAttribute_Class() const;
	
	MonoClass* GetDefaultSubObjectAttribute_Class() const;
	
	MonoClass* GetRootComponentAttribute_Class() const;
	
	MonoClass* GetAttachmentParentAttribute_Class() const;
	
	MonoClass* GetAttachmentSocketNameAttribute_Class() const;
	
	MonoClass* GetDefaultValueAttribute_Class() const;
	
	
	
	
	FClassReflection* Get_Utils_Class() const;
	
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
	
#if UE_F_OPTIONAL_PROPERTY
	MonoClass* TOptional_Class;
#endif
	
	MonoClass* UClassAttribute_Class;
	
	MonoClass* UStructAttribute_Class;
	
	MonoClass* UEnumAttribute_Class;
	
	MonoClass* UInterfaceAttribute_Class;
	
	MonoClass* UPropertyAttribute_Class;
	
	MonoClass* UFunctionAttribute_Class;
	
	
	
	MonoClass* VisibleInstanceOnlyAttribute_Class;
	
	MonoClass* BlueprintCallableAttribute_Class;
	
	MonoClass* BlueprintAuthorityOnlyAttribute_Class;
	
	MonoClass* BlueprintGetterAttribute_Class;
	
	MonoClass* BlueprintSetterAttribute_Class;
	
	MonoClass* FieldNotifyAttribute_Class;
	
	MonoClass* TransientAttribute_Class;
	
	MonoClass* ConfigAttribute_Class;
	
	MonoClass* BlueprintTypeAttribute_Class;
	
	MonoClass* NotBlueprintTypeAttribute_Class;
	
	MonoClass* BlueprintableAttribute_Class;
	
	MonoClass* NotBlueprintableAttribute_Class;
	
	MonoClass* NoExportAttribute_Class;
	
	MonoClass* AbstractAttribute_Class;
	
	MonoClass* ExperimentalAttribute_Class;
	
	MonoClass* EditorConfigAttribute_Class;
	
	MonoClass* CategoryAttribute_Class;
	
	MonoClass* BlueprintInternalUseOnlyAttribute_Class;
	
	
	
	
	MonoClass* ClassGroupAttribute_Class;
	
	MonoClass* WithinAttribute_Class;
	
	MonoClass* MinimalAPIAttribute_Class;
	
	MonoClass* CustomConstructorAttribute_Class;
	
	MonoClass* IntrinsicAttribute_Class;
	
	MonoClass* NotPlaceableAttribute_Class;
	
	MonoClass* DefaultToInstancedAttribute_Class;
	
	MonoClass* ConstAttribute_Class;
	
	MonoClass* DeprecatedAttribute_Class;
	
	MonoClass* PerObjectConfigAttribute_Class;
	
	MonoClass* ConfigDoNotCheckDefaultsAttribute_Class;
	
	MonoClass* DefaultConfigAttribute_Class;
	
	MonoClass* EditInlineNewAttribute_Class;
	
	MonoClass* NotEditInlineNewAttribute_Class;
	
	MonoClass* HideDropdownAttribute_Class;
	
	MonoClass* ShowCategoriesAttribute_Class;
	
	MonoClass* HideCategoriesAttribute_Class;
	
	MonoClass* ComponentWrapperClassAttribute_Class;
	
	MonoClass* HideFunctionsAttribute_Class;
	
	MonoClass* AutoExpandCategoriesAttribute_Class;
	
	MonoClass* AutoCollapseCategoriesAttribute_Class;
	
	MonoClass* CollapseCategoriesAttribute_Class;
	
	MonoClass* DontCollapseCategoriesAttribute_Class;
	
	MonoClass* PrioritizeCategoriesAttribute_Class;
	
	MonoClass* AdvancedClassDisplayAttribute_Class;
	
	MonoClass* ConversionRootAttribute_Class;
	
	MonoClass* EarlyAccessPreviewAttribute_Class;
	
	MonoClass* SparseClassDataTypeAttribute_Class;
	
	MonoClass* CannotImplementInterfaceInBlueprintAttribute_Class;
	
	
	
	MonoClass* GlobalConfigAttribute_Class;
	
	MonoClass* LocalizedAttribute_Class;
	
	MonoClass* DuplicateTransientAttribute_Class;
	
	MonoClass* NonPIETransientAttribute_Class;
	
	MonoClass* NonPIEDuplicateTransientAttribute_Class;
	
	MonoClass* ExportAttribute_Class;
	
	MonoClass* NoClearAttribute_Class;
	
	MonoClass* EditFixedSizeAttribute_Class;
	
	MonoClass* ReplicatedAttribute_Class;
	
	MonoClass* ReplicatedUsingAttribute_Class;
	
	MonoClass* NotReplicatedAttribute_Class;
	
	MonoClass* InterpAttribute_Class;
	
	MonoClass* NonTransactionalAttribute_Class;
	
	MonoClass* InstancedAttribute_Class;
	
	MonoClass* BlueprintAssignableAttribute_Class;
	
	MonoClass* SimpleDisplayAttribute_Class;
	
	MonoClass* AdvancedDisplayAttribute_Class;
	
	MonoClass* EditAnywhereAttribute_Class;
	
	MonoClass* EditInstanceOnlyAttribute_Class;
	
	MonoClass* EditDefaultsOnlyAttribute_Class;
	
	MonoClass* VisibleAnywhereAttribute_Class;
	
	MonoClass* VisibleDefaultsOnlyAttribute_Class;
	
	MonoClass* BlueprintReadOnlyAttribute_Class;
	
	MonoClass* BlueprintReadWriteAttribute_Class;
	
	MonoClass* AssetRegistrySearchableAttribute_Class;
	
	MonoClass* SaveGameAttribute_Class;
	
	MonoClass* TextExportTransientAttribute_Class;
	
	MonoClass* SkipSerializationAttribute_Class;
	
	MonoClass* DefaultSubObjectAttribute_Class;
	
	MonoClass* RootComponentAttribute_Class;
	
	MonoClass* AttachmentParentAttribute_Class;
	
	MonoClass* AttachmentSocketNameAttribute_Class;
	
	MonoClass* DefaultValueAttribute_Class;
	
	
	
	FClassReflection* Utils_Class{};
	
public:
	TMap<TWeakObjectPtr<UField>, FClassReflection*> ClassReflection;
	
	TMap<MonoClass*, FClassReflection*> ClassReflection1;
	
	TMap<TPair<FString, FString>, FClassReflection*> ClassReflection2;
};

#include "FReflectionRegistry.inl"
