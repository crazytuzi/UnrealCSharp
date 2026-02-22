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
	
	MonoClass* GetComponentWrapperClassAttribute_Class() const;
	
	MonoClass* GetHideFunctionsAttribute_Class() const;
	
	MonoClass* GetAutoExpandCategoriesAttribute_Class() const;
	
	MonoClass* GetAutoCollapseCategoriesAttribute_Class() const;
	
	MonoClass* GetCollapseCategoriesAttribute_Class() const;
	
	MonoClass* GetDontCollapseCategoriesAttribute_Class() const;
	
	MonoClass* GetPrioritizeCategoriesAttribute_Class() const;
	
	MonoClass* GetAdvancedClassDisplayAttribute_Class() const;
	
	MonoClass* GetEarlyAccessPreviewAttribute_Class() const;
	
	MonoClass* GetSparseClassDataTypeAttribute_Class() const;
	
	
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
	
	
	MonoClass* GetBlueprintImplementableEventAttribute_Class() const;
	
	MonoClass* GetBlueprintNativeEventAttribute_Class() const;
	
	MonoClass* GetSealedEventAttribute_Class() const;
	
	MonoClass* GetExecAttribute_Class() const;
	
	MonoClass* GetServerAttribute_Class() const;
	
	MonoClass* GetClientAttribute_Class() const;
	
	MonoClass* GetNetMulticastAttribute_Class() const;
	
	MonoClass* GetReliableAttribute_Class() const;
	
	MonoClass* GetUnreliableAttribute_Class() const;
	
	MonoClass* GetBlueprintPureAttribute_Class() const;
	
	MonoClass* GetBlueprintCosmeticAttribute_Class() const;
	
	MonoClass* GetCustomThunkAttribute_Class() const;
	
	MonoClass* GetWithValidationAttribute_Class() const;
	
	MonoClass* GetServiceRequestAttribute_Class() const;
	
	MonoClass* GetServiceResponseAttribute_Class() const;
	
	// MetaDataAttributeMacro.h - 按顺序添加
#if WITH_EDITOR
	FClassReflection* GetHideCategoriesAttribute_Class() const;
	
	FClassReflection* GetConversionRootAttribute_Class() const;
	
	FClassReflection* GetCannotImplementInterfaceInBlueprintAttribute_Class() const;
	
	FClassReflection* GetToolTipAttribute_Class() const;
	
	FClassReflection* GetShortTooltipAttribute_Class() const;
	
	FClassReflection* GetDocumentationPolicyAttribute_Class() const;
	
	FClassReflection* GetBlueprintSpawnableComponentAttribute_Class() const;
	
	FClassReflection* GetChildCanTickAttribute_Class() const;
	
	FClassReflection* GetChildCannotTickAttribute_Class() const;
	
	FClassReflection* GetDebugTreeLeafAttribute_Class() const;
	
	FClassReflection* GetIgnoreCategoryKeywordsInSubclassesAttribute_Class() const;
	
	FClassReflection* GetDeprecatedNodeAttribute_Class() const;
	
	FClassReflection* GetDeprecationMessageAttribute_Class() const;
	
	FClassReflection* GetDisplayNameAttribute_Class() const;
	
	FClassReflection* GetScriptNameAttribute_Class() const;
	
	FClassReflection* GetIsBlueprintBaseAttribute_Class() const;
	
	FClassReflection* GetKismetHideOverridesAttribute_Class() const;
	
	FClassReflection* GetLoadBehaviorAttribute_Class() const;
	
	FClassReflection* GetProhibitedInterfacesAttribute_Class() const;
	
	FClassReflection* GetRestrictedToClassesAttribute_Class() const;
	
	FClassReflection* GetShowWorldContextPinAttribute_Class() const;
	
	FClassReflection* GetDontUseGenericSpawnObjectAttribute_Class() const;
	
	FClassReflection* GetExposedAsyncProxyAttribute_Class() const;
	
	FClassReflection* GetBlueprintThreadSafeAttribute_Class() const;
	
	FClassReflection* GetUsesHierarchyAttribute_Class() const;
	
	FClassReflection* GetHasNativeBreakAttribute_Class() const;
	
	FClassReflection* GetHasNativeMakeAttribute_Class() const;
	
	FClassReflection* GetHiddenByDefaultAttribute_Class() const;
	
	FClassReflection* GetDisableSplitPinAttribute_Class() const;
	
	FClassReflection* GetAllowAbstractAttribute_Class() const;
	
	FClassReflection* GetAllowAnyActorAttribute_Class() const;
	
	FClassReflection* GetAllowedClassesAttribute_Class() const;
	
	FClassReflection* GetAllowPreserveRatioAttribute_Class() const;
	
	FClassReflection* GetAllowPrivateAccessAttribute_Class() const;
	
	FClassReflection* GetArrayClampAttribute_Class() const;
	
	FClassReflection* GetAssetBundlesAttribute_Class() const;
	
	FClassReflection* GetBlueprintBaseOnlyAttribute_Class() const;
	
	FClassReflection* GetBlueprintCompilerGeneratedDefaultsAttribute_Class() const;
	
	FClassReflection* GetClampMinAttribute_Class() const;
	
	FClassReflection* GetClampMaxAttribute_Class() const;
	
	FClassReflection* GetConfigHierarchyEditableAttribute_Class() const;
	
	FClassReflection* GetContentDirAttribute_Class() const;
	
	FClassReflection* GetDeltaAttribute_Class() const;
	
	FClassReflection* GetDeprecatedPropertyAttribute_Class() const;
	
	FClassReflection* GetDisallowedAssetDataTagsAttribute_Class() const;
	
	FClassReflection* GetDisallowedClassesAttribute_Class() const;
	
	FClassReflection* GetDisplayAfterAttribute_Class() const;
	
	FClassReflection* GetDisplayPriorityAttribute_Class() const;
	
	FClassReflection* GetDisplayThumbnailAttribute_Class() const;
	
	FClassReflection* GetEditConditionAttribute_Class() const;
	
	FClassReflection* GetEditConditionHidesAttribute_Class() const;
	
	FClassReflection* GetEditFixedOrderAttribute_Class() const;
	
	FClassReflection* GetCategoryAttribute_Class() const;
	
	FClassReflection* GetExactClassAttribute_Class() const;
	
	FClassReflection* GetExposeFunctionCategoriesAttribute_Class() const;
	
	FClassReflection* GetExposeOnSpawnAttribute_Class() const;
	
	FClassReflection* GetFilePathFilterAttribute_Class() const;
	
	FClassReflection* GetRelativeToGameDirAttribute_Class() const;
	
	FClassReflection* GetFixedIncrementAttribute_Class() const;
	
	FClassReflection* GetForceShowEngineContentAttribute_Class() const;
	
	FClassReflection* GetForceShowPluginContentAttribute_Class() const;
	
	FClassReflection* GetHideAlphaChannelAttribute_Class() const;
	
	FClassReflection* GetHideInDetailPanelAttribute_Class() const;
	
	FClassReflection* GetHideViewOptionsAttribute_Class() const;
	
	FClassReflection* GetIgnoreForMemberInitializationTestAttribute_Class() const;
	
	FClassReflection* GetInlineEditConditionToggleAttribute_Class() const;
	
	FClassReflection* GetLinearDeltaSensitivityAttribute_Class() const;
	
	FClassReflection* GetLongPackageNameAttribute_Class() const;
	
	FClassReflection* GetMakeEditWidgetAttribute_Class() const;
	
	FClassReflection* GetMakeStructureDefaultValueAttribute_Class() const;
	
	FClassReflection* GetMetaClassAttribute_Class() const;
	
	FClassReflection* GetMustImplementAttribute_Class() const;
	
	FClassReflection* GetMultipleAttribute_Class() const;
	
	FClassReflection* GetMaxLengthAttribute_Class() const;
	
	FClassReflection* GetMultiLineAttribute_Class() const;
	
	FClassReflection* GetPasswordFieldAttribute_Class() const;
	
	FClassReflection* GetNoElementDuplicateAttribute_Class() const;
	
	FClassReflection* GetNoResetToDefaultAttribute_Class() const;
	
	FClassReflection* GetEditInlineAttribute_Class() const;
	
	FClassReflection* GetNoEditInlineAttribute_Class() const;
	
	FClassReflection* GetNoSpinboxAttribute_Class() const;
	
	FClassReflection* GetOnlyPlaceableAttribute_Class() const;
	
	FClassReflection* GetRelativePathAttribute_Class() const;
	
	FClassReflection* GetRelativeToGameContentDirAttribute_Class() const;
	
	FClassReflection* GetRequiredAssetDataTagsAttribute_Class() const;
	
	FClassReflection* GetScriptNoExportAttribute_Class() const;
	
	FClassReflection* GetShowOnlyInnerPropertiesAttribute_Class() const;
	
	FClassReflection* GetShowTreeViewAttribute_Class() const;
	
	FClassReflection* GetSliderExponentAttribute_Class() const;
	
	FClassReflection* GetTitlePropertyAttribute_Class() const;
	
	FClassReflection* GetUIMinAttribute_Class() const;
	
	FClassReflection* GetUIMaxAttribute_Class() const;
	
	FClassReflection* GetUnitsAttribute_Class() const;
	
	FClassReflection* GetForceUnitsAttribute_Class() const;
	
	FClassReflection* GetUntrackedAttribute_Class() const;
	
	FClassReflection* GetDevelopmentOnlyAttribute_Class() const;
	
	FClassReflection* GetNeedsLatentFixupAttribute_Class() const;
	
	FClassReflection* GetLatentCallbackTargetAttribute_Class() const;
	
	FClassReflection* GetGetOptionsAttribute_Class() const;
	
	FClassReflection* GetPinHiddenByDefaultAttribute_Class() const;
	
	FClassReflection* GetValidEnumValuesAttribute_Class() const;
	
	FClassReflection* GetInvalidEnumValuesAttribute_Class() const;
	
	FClassReflection* GetOverridingInputPropertyAttribute_Class() const;
	
	FClassReflection* GetRequiredInputAttribute_Class() const;
	
	FClassReflection* GetNeverAsPinAttribute_Class() const;
	
	FClassReflection* GetPinShownByDefaultAttribute_Class() const;
	
	FClassReflection* GetAlwaysAsPinAttribute_Class() const;
	
	FClassReflection* GetCustomizePropertyAttribute_Class() const;
	
	FClassReflection* GetCallInEditorAttribute_Class() const;
	
	FClassReflection* GetVariadicAttribute_Class() const;
	
	FClassReflection* GetReturnDisplayNameAttribute_Class() const;
	
	FClassReflection* GetInternalUseParamAttribute_Class() const;
	
	FClassReflection* GetForceAsFunctionAttribute_Class() const;
	
	FClassReflection* GetIgnoreTypePromotionAttribute_Class() const;
	
	FClassReflection* GetArrayParmAttribute_Class() const;
	
	FClassReflection* GetArrayTypeDependentParamsAttribute_Class() const;
	
	FClassReflection* GetAutoCreateRefTermAttribute_Class() const;
	
	FClassReflection* GetHideAssetPickerAttribute_Class() const;
	
	FClassReflection* GetBlueprintInternalUseOnlyAttribute_Class() const;
	
	FClassReflection* GetBlueprintProtectedAttribute_Class() const;
	
	FClassReflection* GetCallableWithoutWorldContextAttribute_Class() const;
	
	FClassReflection* GetCommutativeAssociativeBinaryOperatorAttribute_Class() const;
	
	FClassReflection* GetCompactNodeTitleAttribute_Class() const;
	
	FClassReflection* GetCustomStructureParamAttribute_Class() const;
	
	FClassReflection* GetDefaultToSelfAttribute_Class() const;
	
	FClassReflection* GetDeprecatedFunctionAttribute_Class() const;
	
	FClassReflection* GetExpandEnumAsExecsAttribute_Class() const;
	
	FClassReflection* GetExpandBoolAsExecsAttribute_Class() const;
	
	FClassReflection* GetScriptMethodAttribute_Class() const;
	
	FClassReflection* GetScriptMethodSelfReturnAttribute_Class() const;
	
	FClassReflection* GetScriptOperatorAttribute_Class() const;
	
	FClassReflection* GetScriptConstantAttribute_Class() const;
	
	FClassReflection* GetScriptConstantHostAttribute_Class() const;
	
	FClassReflection* GetHidePinAttribute_Class() const;
	
	FClassReflection* GetHideSpawnParmsAttribute_Class() const;
	
	FClassReflection* GetKeywordsAttribute_Class() const;
	
	FClassReflection* GetLatentAttribute_Class() const;
	
	FClassReflection* GetLatentInfoAttribute_Class() const;
	
	FClassReflection* GetMaterialParameterCollectionFunctionAttribute_Class() const;
	
	FClassReflection* GetNativeBreakFuncAttribute_Class() const;
	
	FClassReflection* GetNativeMakeFuncAttribute_Class() const;
	
	FClassReflection* GetUnsafeDuringActorConstructionAttribute_Class() const;
	
	FClassReflection* GetWorldContextAttribute_Class() const;
	
	FClassReflection* GetBlueprintAutoCastAttribute_Class() const;
	
	FClassReflection* GetNotBlueprintThreadSafeAttribute_Class() const;
	
	FClassReflection* GetDeterminesOutputTypeAttribute_Class() const;
	
	FClassReflection* GetDynamicOutputParamAttribute_Class() const;
	
	FClassReflection* GetDataTablePinAttribute_Class() const;
	
	FClassReflection* GetSetParamAttribute_Class() const;
	
	FClassReflection* GetMapParamAttribute_Class() const;
	
	FClassReflection* GetMapKeyParamAttribute_Class() const;
	
	FClassReflection* GetMapValueParamAttribute_Class() const;
	
	FClassReflection* GetBitmaskAttribute_Class() const;
	
	FClassReflection* GetBitmaskEnumAttribute_Class() const;
	
	FClassReflection* GetBitflagsAttribute_Class() const;
	
	FClassReflection* GetUseEnumValuesAsMaskValuesInEditorAttribute_Class() const;
	
	FClassReflection* GetArrayParamAttribute_Class() const;
#endif
	
	
	
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
	
	MonoClass* ComponentWrapperClassAttribute_Class;
	
	MonoClass* HideFunctionsAttribute_Class;
	
	MonoClass* AutoExpandCategoriesAttribute_Class;
	
	MonoClass* AutoCollapseCategoriesAttribute_Class;
	
	MonoClass* CollapseCategoriesAttribute_Class;
	
	MonoClass* DontCollapseCategoriesAttribute_Class;
	
	MonoClass* PrioritizeCategoriesAttribute_Class;
	
	MonoClass* AdvancedClassDisplayAttribute_Class;
	
	MonoClass* EarlyAccessPreviewAttribute_Class;
	
	MonoClass* SparseClassDataTypeAttribute_Class;
	
	
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
	
	
	
	MonoClass* BlueprintImplementableEventAttribute_Class;
	
	MonoClass* BlueprintNativeEventAttribute_Class;
	
	MonoClass* SealedEventAttribute_Class;
	
	MonoClass* ExecAttribute_Class;
	
	MonoClass* ServerAttribute_Class;
	
	MonoClass* ClientAttribute_Class;
	
	MonoClass* NetMulticastAttribute_Class;
	
	MonoClass* ReliableAttribute_Class;
	
	MonoClass* UnreliableAttribute_Class;
	
	MonoClass* BlueprintPureAttribute_Class;
	
	MonoClass* BlueprintCosmeticAttribute_Class;
	
	MonoClass* CustomThunkAttribute_Class;
	
	MonoClass* WithValidationAttribute_Class;
	
	MonoClass* ServiceRequestAttribute_Class;
	
	MonoClass* ServiceResponseAttribute_Class;
	
	// MetaDataAttributeMacro.h - 按顺序添加
#if WITH_EDITOR
	FClassReflection* HideCategoriesAttribute_Class;
	
	FClassReflection* ConversionRootAttribute_Class;
	
	FClassReflection* CannotImplementInterfaceInBlueprintAttribute_Class;
	
	FClassReflection* ToolTipAttribute_Class;
	
	FClassReflection* ShortTooltipAttribute_Class;
	
	FClassReflection* DocumentationPolicyAttribute_Class;
	
	FClassReflection* BlueprintSpawnableComponentAttribute_Class;
	
	FClassReflection* ChildCanTickAttribute_Class;
	
	FClassReflection* ChildCannotTickAttribute_Class;
	
	FClassReflection* DebugTreeLeafAttribute_Class;
	
	FClassReflection* IgnoreCategoryKeywordsInSubclassesAttribute_Class;
	
	FClassReflection* DeprecatedNodeAttribute_Class;
	
	FClassReflection* DeprecationMessageAttribute_Class;
	
	FClassReflection* DisplayNameAttribute_Class;
	
	FClassReflection* ScriptNameAttribute_Class;
	
	FClassReflection* IsBlueprintBaseAttribute_Class;
	
	FClassReflection* KismetHideOverridesAttribute_Class;
	
	FClassReflection* LoadBehaviorAttribute_Class;
	
	FClassReflection* ProhibitedInterfacesAttribute_Class;
	
	FClassReflection* RestrictedToClassesAttribute_Class;
	
	FClassReflection* ShowWorldContextPinAttribute_Class;
	
	FClassReflection* DontUseGenericSpawnObjectAttribute_Class;
	
	FClassReflection* ExposedAsyncProxyAttribute_Class;
	
	FClassReflection* BlueprintThreadSafeAttribute_Class;
	
	FClassReflection* UsesHierarchyAttribute_Class;
	
	FClassReflection* HasNativeBreakAttribute_Class;
	
	FClassReflection* HasNativeMakeAttribute_Class;
	
	FClassReflection* HiddenByDefaultAttribute_Class;
	
	FClassReflection* DisableSplitPinAttribute_Class;
	
	FClassReflection* AllowAbstractAttribute_Class;
	
	FClassReflection* AllowAnyActorAttribute_Class;
	
	FClassReflection* AllowedClassesAttribute_Class;
	
	FClassReflection* AllowPreserveRatioAttribute_Class;
	
	FClassReflection* AllowPrivateAccessAttribute_Class;
	
	FClassReflection* ArrayClampAttribute_Class;
	
	FClassReflection* AssetBundlesAttribute_Class;
	
	FClassReflection* BlueprintBaseOnlyAttribute_Class;
	
	FClassReflection* BlueprintCompilerGeneratedDefaultsAttribute_Class;
	
	FClassReflection* ClampMinAttribute_Class;
	
	FClassReflection* ClampMaxAttribute_Class;
	
	FClassReflection* ConfigHierarchyEditableAttribute_Class;
	
	FClassReflection* ContentDirAttribute_Class;
	
	FClassReflection* DeltaAttribute_Class;
	
	FClassReflection* DeprecatedPropertyAttribute_Class;
	
	FClassReflection* DisallowedAssetDataTagsAttribute_Class;
	
	FClassReflection* DisallowedClassesAttribute_Class;
	
	FClassReflection* DisplayAfterAttribute_Class;
	
	FClassReflection* DisplayPriorityAttribute_Class;
	
	FClassReflection* DisplayThumbnailAttribute_Class;
	
	FClassReflection* EditConditionAttribute_Class;
	
	FClassReflection* EditConditionHidesAttribute_Class;
	
	FClassReflection* EditFixedOrderAttribute_Class;
	
	FClassReflection* CategoryAttribute_Class;
	
	FClassReflection* ExactClassAttribute_Class;
	
	FClassReflection* ExposeFunctionCategoriesAttribute_Class;
	
	FClassReflection* ExposeOnSpawnAttribute_Class;
	
	FClassReflection* FilePathFilterAttribute_Class;
	
	FClassReflection* RelativeToGameDirAttribute_Class;
	
	FClassReflection* FixedIncrementAttribute_Class;
	
	FClassReflection* ForceShowEngineContentAttribute_Class;
	
	FClassReflection* ForceShowPluginContentAttribute_Class;
	
	FClassReflection* HideAlphaChannelAttribute_Class;
	
	FClassReflection* HideInDetailPanelAttribute_Class;
	
	FClassReflection* HideViewOptionsAttribute_Class;
	
	FClassReflection* IgnoreForMemberInitializationTestAttribute_Class;
	
	FClassReflection* InlineEditConditionToggleAttribute_Class;
	
	FClassReflection* LinearDeltaSensitivityAttribute_Class;
	
	FClassReflection* LongPackageNameAttribute_Class;
	
	FClassReflection* MakeEditWidgetAttribute_Class;
	
	FClassReflection* MakeStructureDefaultValueAttribute_Class;
	
	FClassReflection* MetaClassAttribute_Class;
	
	FClassReflection* MustImplementAttribute_Class;
	
	FClassReflection* MultipleAttribute_Class;
	
	FClassReflection* MaxLengthAttribute_Class;
	
	FClassReflection* MultiLineAttribute_Class;
	
	FClassReflection* PasswordFieldAttribute_Class;
	
	FClassReflection* NoElementDuplicateAttribute_Class;
	
	FClassReflection* NoResetToDefaultAttribute_Class;
	
	FClassReflection* EditInlineAttribute_Class;
	
	FClassReflection* NoEditInlineAttribute_Class;
	
	FClassReflection* NoSpinboxAttribute_Class;
	
	FClassReflection* OnlyPlaceableAttribute_Class;
	
	FClassReflection* RelativePathAttribute_Class;
	
	FClassReflection* RelativeToGameContentDirAttribute_Class;
	
	FClassReflection* RequiredAssetDataTagsAttribute_Class;
	
	FClassReflection* ScriptNoExportAttribute_Class;
	
	FClassReflection* ShowOnlyInnerPropertiesAttribute_Class;
	
	FClassReflection* ShowTreeViewAttribute_Class;
	
	FClassReflection* SliderExponentAttribute_Class;
	
	FClassReflection* TitlePropertyAttribute_Class;
	
	FClassReflection* UIMinAttribute_Class;
	
	FClassReflection* UIMaxAttribute_Class;
	
	FClassReflection* UnitsAttribute_Class;
	
	FClassReflection* ForceUnitsAttribute_Class;
	
	FClassReflection* UntrackedAttribute_Class;
	
	FClassReflection* DevelopmentOnlyAttribute_Class;
	
	FClassReflection* NeedsLatentFixupAttribute_Class;
	
	FClassReflection* LatentCallbackTargetAttribute_Class;
	
	FClassReflection* GetOptionsAttribute_Class;
	
	FClassReflection* PinHiddenByDefaultAttribute_Class;
	
	FClassReflection* ValidEnumValuesAttribute_Class;
	
	FClassReflection* InvalidEnumValuesAttribute_Class;
	
	FClassReflection* OverridingInputPropertyAttribute_Class;
	
	FClassReflection* RequiredInputAttribute_Class;
	
	FClassReflection* NeverAsPinAttribute_Class;
	
	FClassReflection* PinShownByDefaultAttribute_Class;
	
	FClassReflection* AlwaysAsPinAttribute_Class;
	
	FClassReflection* CustomizePropertyAttribute_Class;
	
	FClassReflection* CallInEditorAttribute_Class;
	
	FClassReflection* VariadicAttribute_Class;
	
	FClassReflection* ReturnDisplayNameAttribute_Class;
	
	FClassReflection* InternalUseParamAttribute_Class;
	
	FClassReflection* ForceAsFunctionAttribute_Class;
	
	FClassReflection* IgnoreTypePromotionAttribute_Class;
	
	FClassReflection* ArrayParmAttribute_Class;
	
	FClassReflection* ArrayTypeDependentParamsAttribute_Class;
	
	FClassReflection* AutoCreateRefTermAttribute_Class;
	
	FClassReflection* HideAssetPickerAttribute_Class;
	
	FClassReflection* BlueprintInternalUseOnlyAttribute_Class;
	
	FClassReflection* BlueprintProtectedAttribute_Class;
	
	FClassReflection* CallableWithoutWorldContextAttribute_Class;
	
	FClassReflection* CommutativeAssociativeBinaryOperatorAttribute_Class;
	
	FClassReflection* CompactNodeTitleAttribute_Class;
	
	FClassReflection* CustomStructureParamAttribute_Class;
	
	FClassReflection* DefaultToSelfAttribute_Class;
	
	FClassReflection* DeprecatedFunctionAttribute_Class;
	
	FClassReflection* ExpandEnumAsExecsAttribute_Class;
	
	FClassReflection* ExpandBoolAsExecsAttribute_Class;
	
	FClassReflection* ScriptMethodAttribute_Class;
	
	FClassReflection* ScriptMethodSelfReturnAttribute_Class;
	
	FClassReflection* ScriptOperatorAttribute_Class;
	
	FClassReflection* ScriptConstantAttribute_Class;
	
	FClassReflection* ScriptConstantHostAttribute_Class;
	
	FClassReflection* HidePinAttribute_Class;
	
	FClassReflection* HideSpawnParmsAttribute_Class;
	
	FClassReflection* KeywordsAttribute_Class;
	
	FClassReflection* LatentAttribute_Class;
	
	FClassReflection* LatentInfoAttribute_Class;
	
	FClassReflection* MaterialParameterCollectionFunctionAttribute_Class;
	
	FClassReflection* NativeBreakFuncAttribute_Class;
	
	FClassReflection* NativeMakeFuncAttribute_Class;
	
	FClassReflection* UnsafeDuringActorConstructionAttribute_Class;
	
	FClassReflection* WorldContextAttribute_Class;
	
	FClassReflection* BlueprintAutoCastAttribute_Class;
	
	FClassReflection* NotBlueprintThreadSafeAttribute_Class;
	
	FClassReflection* DeterminesOutputTypeAttribute_Class;
	
	FClassReflection* DynamicOutputParamAttribute_Class;
	
	FClassReflection* DataTablePinAttribute_Class;
	
	FClassReflection* SetParamAttribute_Class;
	
	FClassReflection* MapParamAttribute_Class;
	
	FClassReflection* MapKeyParamAttribute_Class;
	
	FClassReflection* MapValueParamAttribute_Class;
	
	FClassReflection* BitmaskAttribute_Class;
	
	FClassReflection* BitmaskEnumAttribute_Class;
	
	FClassReflection* BitflagsAttribute_Class;
	
	FClassReflection* UseEnumValuesAsMaskValuesInEditorAttribute_Class;
	
	FClassReflection* ArrayParamAttribute_Class;
#endif
	
	
	
	FClassReflection* Utils_Class{};
	
public:
	TMap<TWeakObjectPtr<UField>, FClassReflection*> ClassReflection;
	
	TMap<MonoClass*, FClassReflection*> ClassReflection1;
	
	TMap<TPair<FString, FString>, FClassReflection*> ClassReflection2;
};

#include "FReflectionRegistry.inl"
