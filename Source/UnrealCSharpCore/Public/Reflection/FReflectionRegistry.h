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
	MonoClass* GetHideCategoriesAttribute_Class() const;
	
	MonoClass* GetConversionRootAttribute_Class() const;
	
	MonoClass* GetCannotImplementInterfaceInBlueprintAttribute_Class() const;
	
	MonoClass* GetToolTipAttribute_Class() const;
	
	MonoClass* GetShortTooltipAttribute_Class() const;
	
	MonoClass* GetDocumentationPolicyAttribute_Class() const;
	
	MonoClass* GetBlueprintSpawnableComponentAttribute_Class() const;
	
	MonoClass* GetChildCanTickAttribute_Class() const;
	
	MonoClass* GetChildCannotTickAttribute_Class() const;
	
	MonoClass* GetDebugTreeLeafAttribute_Class() const;
	
	MonoClass* GetIgnoreCategoryKeywordsInSubclassesAttribute_Class() const;
	
	MonoClass* GetDeprecatedNodeAttribute_Class() const;
	
	MonoClass* GetDeprecationMessageAttribute_Class() const;
	
	MonoClass* GetDisplayNameAttribute_Class() const;
	
	MonoClass* GetScriptNameAttribute_Class() const;
	
	MonoClass* GetIsBlueprintBaseAttribute_Class() const;
	
	MonoClass* GetKismetHideOverridesAttribute_Class() const;
	
	MonoClass* GetLoadBehaviorAttribute_Class() const;
	
	MonoClass* GetProhibitedInterfacesAttribute_Class() const;
	
	MonoClass* GetRestrictedToClassesAttribute_Class() const;
	
	MonoClass* GetShowWorldContextPinAttribute_Class() const;
	
	MonoClass* GetDontUseGenericSpawnObjectAttribute_Class() const;
	
	MonoClass* GetExposedAsyncProxyAttribute_Class() const;
	
	MonoClass* GetBlueprintThreadSafeAttribute_Class() const;
	
	MonoClass* GetUsesHierarchyAttribute_Class() const;
	
	MonoClass* GetHasNativeBreakAttribute_Class() const;
	
	MonoClass* GetHasNativeMakeAttribute_Class() const;
	
	MonoClass* GetHiddenByDefaultAttribute_Class() const;
	
	MonoClass* GetDisableSplitPinAttribute_Class() const;
	
	MonoClass* GetAllowAbstractAttribute_Class() const;
	
	MonoClass* GetAllowAnyActorAttribute_Class() const;
	
	MonoClass* GetAllowedClassesAttribute_Class() const;
	
	MonoClass* GetAllowPreserveRatioAttribute_Class() const;
	
	MonoClass* GetAllowPrivateAccessAttribute_Class() const;
	
	MonoClass* GetArrayClampAttribute_Class() const;
	
	MonoClass* GetAssetBundlesAttribute_Class() const;
	
	MonoClass* GetBlueprintBaseOnlyAttribute_Class() const;
	
	MonoClass* GetBlueprintCompilerGeneratedDefaultsAttribute_Class() const;
	
	MonoClass* GetClampMinAttribute_Class() const;
	
	MonoClass* GetClampMaxAttribute_Class() const;
	
	MonoClass* GetConfigHierarchyEditableAttribute_Class() const;
	
	MonoClass* GetContentDirAttribute_Class() const;
	
	MonoClass* GetDeltaAttribute_Class() const;
	
	MonoClass* GetDeprecatedPropertyAttribute_Class() const;
	
	MonoClass* GetDisallowedAssetDataTagsAttribute_Class() const;
	
	MonoClass* GetDisallowedClassesAttribute_Class() const;
	
	MonoClass* GetDisplayAfterAttribute_Class() const;
	
	MonoClass* GetDisplayPriorityAttribute_Class() const;
	
	MonoClass* GetDisplayThumbnailAttribute_Class() const;
	
	MonoClass* GetEditConditionAttribute_Class() const;
	
	MonoClass* GetEditConditionHidesAttribute_Class() const;
	
	MonoClass* GetEditFixedOrderAttribute_Class() const;
	
	MonoClass* GetCategoryAttribute_Class() const;
	
	MonoClass* GetExactClassAttribute_Class() const;
	
	MonoClass* GetExposeFunctionCategoriesAttribute_Class() const;
	
	MonoClass* GetExposeOnSpawnAttribute_Class() const;
	
	MonoClass* GetFilePathFilterAttribute_Class() const;
	
	MonoClass* GetRelativeToGameDirAttribute_Class() const;
	
	MonoClass* GetFixedIncrementAttribute_Class() const;
	
	MonoClass* GetForceShowEngineContentAttribute_Class() const;
	
	MonoClass* GetForceShowPluginContentAttribute_Class() const;
	
	MonoClass* GetHideAlphaChannelAttribute_Class() const;
	
	MonoClass* GetHideInDetailPanelAttribute_Class() const;
	
	MonoClass* GetHideViewOptionsAttribute_Class() const;
	
	MonoClass* GetIgnoreForMemberInitializationTestAttribute_Class() const;
	
	MonoClass* GetInlineEditConditionToggleAttribute_Class() const;
	
	MonoClass* GetLinearDeltaSensitivityAttribute_Class() const;
	
	MonoClass* GetLongPackageNameAttribute_Class() const;
	
	MonoClass* GetMakeEditWidgetAttribute_Class() const;
	
	MonoClass* GetMakeStructureDefaultValueAttribute_Class() const;
	
	MonoClass* GetMetaClassAttribute_Class() const;
	
	MonoClass* GetMustImplementAttribute_Class() const;
	
	MonoClass* GetMultipleAttribute_Class() const;
	
	MonoClass* GetMaxLengthAttribute_Class() const;
	
	MonoClass* GetMultiLineAttribute_Class() const;
	
	MonoClass* GetPasswordFieldAttribute_Class() const;
	
	MonoClass* GetNoElementDuplicateAttribute_Class() const;
	
	MonoClass* GetNoResetToDefaultAttribute_Class() const;
	
	MonoClass* GetEditInlineAttribute_Class() const;
	
	MonoClass* GetNoEditInlineAttribute_Class() const;
	
	MonoClass* GetNoSpinboxAttribute_Class() const;
	
	MonoClass* GetOnlyPlaceableAttribute_Class() const;
	
	MonoClass* GetRelativePathAttribute_Class() const;
	
	MonoClass* GetRelativeToGameContentDirAttribute_Class() const;
	
	MonoClass* GetRequiredAssetDataTagsAttribute_Class() const;
	
	MonoClass* GetScriptNoExportAttribute_Class() const;
	
	MonoClass* GetShowOnlyInnerPropertiesAttribute_Class() const;
	
	MonoClass* GetShowTreeViewAttribute_Class() const;
	
	MonoClass* GetSliderExponentAttribute_Class() const;
	
	MonoClass* GetTitlePropertyAttribute_Class() const;
	
	MonoClass* GetUIMinAttribute_Class() const;
	
	MonoClass* GetUIMaxAttribute_Class() const;
	
	MonoClass* GetUnitsAttribute_Class() const;
	
	MonoClass* GetForceUnitsAttribute_Class() const;
	
	MonoClass* GetUntrackedAttribute_Class() const;
	
	MonoClass* GetDevelopmentOnlyAttribute_Class() const;
	
	MonoClass* GetNeedsLatentFixupAttribute_Class() const;
	
	MonoClass* GetLatentCallbackTargetAttribute_Class() const;
	
	MonoClass* GetGetOptionsAttribute_Class() const;
	
	MonoClass* GetPinHiddenByDefaultAttribute_Class() const;
	
	MonoClass* GetValidEnumValuesAttribute_Class() const;
	
	MonoClass* GetInvalidEnumValuesAttribute_Class() const;
	
	MonoClass* GetOverridingInputPropertyAttribute_Class() const;
	
	MonoClass* GetRequiredInputAttribute_Class() const;
	
	MonoClass* GetNeverAsPinAttribute_Class() const;
	
	MonoClass* GetPinShownByDefaultAttribute_Class() const;
	
	MonoClass* GetAlwaysAsPinAttribute_Class() const;
	
	MonoClass* GetCustomizePropertyAttribute_Class() const;
	
	MonoClass* GetCallInEditorAttribute_Class() const;
	
	MonoClass* GetVariadicAttribute_Class() const;
	
	MonoClass* GetReturnDisplayNameAttribute_Class() const;
	
	MonoClass* GetInternalUseParamAttribute_Class() const;
	
	MonoClass* GetForceAsFunctionAttribute_Class() const;
	
	MonoClass* GetIgnoreTypePromotionAttribute_Class() const;
	
	MonoClass* GetArrayParmAttribute_Class() const;
	
	MonoClass* GetArrayTypeDependentParamsAttribute_Class() const;
	
	MonoClass* GetAutoCreateRefTermAttribute_Class() const;
	
	MonoClass* GetHideAssetPickerAttribute_Class() const;
	
	MonoClass* GetBlueprintInternalUseOnlyAttribute_Class() const;
	
	MonoClass* GetBlueprintProtectedAttribute_Class() const;
	
	MonoClass* GetCallableWithoutWorldContextAttribute_Class() const;
	
	MonoClass* GetCommutativeAssociativeBinaryOperatorAttribute_Class() const;
	
	MonoClass* GetCompactNodeTitleAttribute_Class() const;
	
	MonoClass* GetCustomStructureParamAttribute_Class() const;
	
	MonoClass* GetDefaultToSelfAttribute_Class() const;
	
	MonoClass* GetDeprecatedFunctionAttribute_Class() const;
	
	MonoClass* GetExpandEnumAsExecsAttribute_Class() const;
	
	MonoClass* GetExpandBoolAsExecsAttribute_Class() const;
	
	MonoClass* GetScriptMethodAttribute_Class() const;
	
	MonoClass* GetScriptMethodSelfReturnAttribute_Class() const;
	
	MonoClass* GetScriptOperatorAttribute_Class() const;
	
	MonoClass* GetScriptConstantAttribute_Class() const;
	
	MonoClass* GetScriptConstantHostAttribute_Class() const;
	
	MonoClass* GetHidePinAttribute_Class() const;
	
	MonoClass* GetHideSpawnParmsAttribute_Class() const;
	
	MonoClass* GetKeywordsAttribute_Class() const;
	
	MonoClass* GetLatentAttribute_Class() const;
	
	MonoClass* GetLatentInfoAttribute_Class() const;
	
	MonoClass* GetMaterialParameterCollectionFunctionAttribute_Class() const;
	
	MonoClass* GetNativeBreakFuncAttribute_Class() const;
	
	MonoClass* GetNativeMakeFuncAttribute_Class() const;
	
	MonoClass* GetUnsafeDuringActorConstructionAttribute_Class() const;
	
	MonoClass* GetWorldContextAttribute_Class() const;
	
	MonoClass* GetBlueprintAutoCastAttribute_Class() const;
	
	MonoClass* GetNotBlueprintThreadSafeAttribute_Class() const;
	
	MonoClass* GetDeterminesOutputTypeAttribute_Class() const;
	
	MonoClass* GetDynamicOutputParamAttribute_Class() const;
	
	MonoClass* GetDataTablePinAttribute_Class() const;
	
	MonoClass* GetSetParamAttribute_Class() const;
	
	MonoClass* GetMapParamAttribute_Class() const;
	
	MonoClass* GetMapKeyParamAttribute_Class() const;
	
	MonoClass* GetMapValueParamAttribute_Class() const;
	
	MonoClass* GetBitmaskAttribute_Class() const;
	
	MonoClass* GetBitmaskEnumAttribute_Class() const;
	
	MonoClass* GetBitflagsAttribute_Class() const;
	
	MonoClass* GetUseEnumValuesAsMaskValuesInEditorAttribute_Class() const;
	
	MonoClass* GetArrayParamAttribute_Class() const;
	
	
	
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
	MonoClass* HideCategoriesAttribute_Class;
	
	MonoClass* ConversionRootAttribute_Class;
	
	MonoClass* CannotImplementInterfaceInBlueprintAttribute_Class;
	
	MonoClass* ToolTipAttribute_Class;
	
	MonoClass* ShortTooltipAttribute_Class;
	
	MonoClass* DocumentationPolicyAttribute_Class;
	
	MonoClass* BlueprintSpawnableComponentAttribute_Class;
	
	MonoClass* ChildCanTickAttribute_Class;
	
	MonoClass* ChildCannotTickAttribute_Class;
	
	MonoClass* DebugTreeLeafAttribute_Class;
	
	MonoClass* IgnoreCategoryKeywordsInSubclassesAttribute_Class;
	
	MonoClass* DeprecatedNodeAttribute_Class;
	
	MonoClass* DeprecationMessageAttribute_Class;
	
	MonoClass* DisplayNameAttribute_Class;
	
	MonoClass* ScriptNameAttribute_Class;
	
	MonoClass* IsBlueprintBaseAttribute_Class;
	
	MonoClass* KismetHideOverridesAttribute_Class;
	
	MonoClass* LoadBehaviorAttribute_Class;
	
	MonoClass* ProhibitedInterfacesAttribute_Class;
	
	MonoClass* RestrictedToClassesAttribute_Class;
	
	MonoClass* ShowWorldContextPinAttribute_Class;
	
	MonoClass* DontUseGenericSpawnObjectAttribute_Class;
	
	MonoClass* ExposedAsyncProxyAttribute_Class;
	
	MonoClass* BlueprintThreadSafeAttribute_Class;
	
	MonoClass* UsesHierarchyAttribute_Class;
	
	MonoClass* HasNativeBreakAttribute_Class;
	
	MonoClass* HasNativeMakeAttribute_Class;
	
	MonoClass* HiddenByDefaultAttribute_Class;
	
	MonoClass* DisableSplitPinAttribute_Class;
	
	MonoClass* AllowAbstractAttribute_Class;
	
	MonoClass* AllowAnyActorAttribute_Class;
	
	MonoClass* AllowedClassesAttribute_Class;
	
	MonoClass* AllowPreserveRatioAttribute_Class;
	
	MonoClass* AllowPrivateAccessAttribute_Class;
	
	MonoClass* ArrayClampAttribute_Class;
	
	MonoClass* AssetBundlesAttribute_Class;
	
	MonoClass* BlueprintBaseOnlyAttribute_Class;
	
	MonoClass* BlueprintCompilerGeneratedDefaultsAttribute_Class;
	
	MonoClass* ClampMinAttribute_Class;
	
	MonoClass* ClampMaxAttribute_Class;
	
	MonoClass* ConfigHierarchyEditableAttribute_Class;
	
	MonoClass* ContentDirAttribute_Class;
	
	MonoClass* DeltaAttribute_Class;
	
	MonoClass* DeprecatedPropertyAttribute_Class;
	
	MonoClass* DisallowedAssetDataTagsAttribute_Class;
	
	MonoClass* DisallowedClassesAttribute_Class;
	
	MonoClass* DisplayAfterAttribute_Class;
	
	MonoClass* DisplayPriorityAttribute_Class;
	
	MonoClass* DisplayThumbnailAttribute_Class;
	
	MonoClass* EditConditionAttribute_Class;
	
	MonoClass* EditConditionHidesAttribute_Class;
	
	MonoClass* EditFixedOrderAttribute_Class;
	
	MonoClass* CategoryAttribute_Class;
	
	MonoClass* ExactClassAttribute_Class;
	
	MonoClass* ExposeFunctionCategoriesAttribute_Class;
	
	MonoClass* ExposeOnSpawnAttribute_Class;
	
	MonoClass* FilePathFilterAttribute_Class;
	
	MonoClass* RelativeToGameDirAttribute_Class;
	
	MonoClass* FixedIncrementAttribute_Class;
	
	MonoClass* ForceShowEngineContentAttribute_Class;
	
	MonoClass* ForceShowPluginContentAttribute_Class;
	
	MonoClass* HideAlphaChannelAttribute_Class;
	
	MonoClass* HideInDetailPanelAttribute_Class;
	
	MonoClass* HideViewOptionsAttribute_Class;
	
	MonoClass* IgnoreForMemberInitializationTestAttribute_Class;
	
	MonoClass* InlineEditConditionToggleAttribute_Class;
	
	MonoClass* LinearDeltaSensitivityAttribute_Class;
	
	MonoClass* LongPackageNameAttribute_Class;
	
	MonoClass* MakeEditWidgetAttribute_Class;
	
	MonoClass* MakeStructureDefaultValueAttribute_Class;
	
	MonoClass* MetaClassAttribute_Class;
	
	MonoClass* MustImplementAttribute_Class;
	
	MonoClass* MultipleAttribute_Class;
	
	MonoClass* MaxLengthAttribute_Class;
	
	MonoClass* MultiLineAttribute_Class;
	
	MonoClass* PasswordFieldAttribute_Class;
	
	MonoClass* NoElementDuplicateAttribute_Class;
	
	MonoClass* NoResetToDefaultAttribute_Class;
	
	MonoClass* EditInlineAttribute_Class;
	
	MonoClass* NoEditInlineAttribute_Class;
	
	MonoClass* NoSpinboxAttribute_Class;
	
	MonoClass* OnlyPlaceableAttribute_Class;
	
	MonoClass* RelativePathAttribute_Class;
	
	MonoClass* RelativeToGameContentDirAttribute_Class;
	
	MonoClass* RequiredAssetDataTagsAttribute_Class;
	
	MonoClass* ScriptNoExportAttribute_Class;
	
	MonoClass* ShowOnlyInnerPropertiesAttribute_Class;
	
	MonoClass* ShowTreeViewAttribute_Class;
	
	MonoClass* SliderExponentAttribute_Class;
	
	MonoClass* TitlePropertyAttribute_Class;
	
	MonoClass* UIMinAttribute_Class;
	
	MonoClass* UIMaxAttribute_Class;
	
	MonoClass* UnitsAttribute_Class;
	
	MonoClass* ForceUnitsAttribute_Class;
	
	MonoClass* UntrackedAttribute_Class;
	
	MonoClass* DevelopmentOnlyAttribute_Class;
	
	MonoClass* NeedsLatentFixupAttribute_Class;
	
	MonoClass* LatentCallbackTargetAttribute_Class;
	
	MonoClass* GetOptionsAttribute_Class;
	
	MonoClass* PinHiddenByDefaultAttribute_Class;
	
	MonoClass* ValidEnumValuesAttribute_Class;
	
	MonoClass* InvalidEnumValuesAttribute_Class;
	
	MonoClass* OverridingInputPropertyAttribute_Class;
	
	MonoClass* RequiredInputAttribute_Class;
	
	MonoClass* NeverAsPinAttribute_Class;
	
	MonoClass* PinShownByDefaultAttribute_Class;
	
	MonoClass* AlwaysAsPinAttribute_Class;
	
	MonoClass* CustomizePropertyAttribute_Class;
	
	MonoClass* CallInEditorAttribute_Class;
	
	MonoClass* VariadicAttribute_Class;
	
	MonoClass* ReturnDisplayNameAttribute_Class;
	
	MonoClass* InternalUseParamAttribute_Class;
	
	MonoClass* ForceAsFunctionAttribute_Class;
	
	MonoClass* IgnoreTypePromotionAttribute_Class;
	
	MonoClass* ArrayParmAttribute_Class;
	
	MonoClass* ArrayTypeDependentParamsAttribute_Class;
	
	MonoClass* AutoCreateRefTermAttribute_Class;
	
	MonoClass* HideAssetPickerAttribute_Class;
	
	MonoClass* BlueprintInternalUseOnlyAttribute_Class;
	
	MonoClass* BlueprintProtectedAttribute_Class;
	
	MonoClass* CallableWithoutWorldContextAttribute_Class;
	
	MonoClass* CommutativeAssociativeBinaryOperatorAttribute_Class;
	
	MonoClass* CompactNodeTitleAttribute_Class;
	
	MonoClass* CustomStructureParamAttribute_Class;
	
	MonoClass* DefaultToSelfAttribute_Class;
	
	MonoClass* DeprecatedFunctionAttribute_Class;
	
	MonoClass* ExpandEnumAsExecsAttribute_Class;
	
	MonoClass* ExpandBoolAsExecsAttribute_Class;
	
	MonoClass* ScriptMethodAttribute_Class;
	
	MonoClass* ScriptMethodSelfReturnAttribute_Class;
	
	MonoClass* ScriptOperatorAttribute_Class;
	
	MonoClass* ScriptConstantAttribute_Class;
	
	MonoClass* ScriptConstantHostAttribute_Class;
	
	MonoClass* HidePinAttribute_Class;
	
	MonoClass* HideSpawnParmsAttribute_Class;
	
	MonoClass* KeywordsAttribute_Class;
	
	MonoClass* LatentAttribute_Class;
	
	MonoClass* LatentInfoAttribute_Class;
	
	MonoClass* MaterialParameterCollectionFunctionAttribute_Class;
	
	MonoClass* NativeBreakFuncAttribute_Class;
	
	MonoClass* NativeMakeFuncAttribute_Class;
	
	MonoClass* UnsafeDuringActorConstructionAttribute_Class;
	
	MonoClass* WorldContextAttribute_Class;
	
	MonoClass* BlueprintAutoCastAttribute_Class;
	
	MonoClass* NotBlueprintThreadSafeAttribute_Class;
	
	MonoClass* DeterminesOutputTypeAttribute_Class;
	
	MonoClass* DynamicOutputParamAttribute_Class;
	
	MonoClass* DataTablePinAttribute_Class;
	
	MonoClass* SetParamAttribute_Class;
	
	MonoClass* MapParamAttribute_Class;
	
	MonoClass* MapKeyParamAttribute_Class;
	
	MonoClass* MapValueParamAttribute_Class;
	
	MonoClass* BitmaskAttribute_Class;
	
	MonoClass* BitmaskEnumAttribute_Class;
	
	MonoClass* BitflagsAttribute_Class;
	
	MonoClass* UseEnumValuesAsMaskValuesInEditorAttribute_Class;
	
	MonoClass* ArrayParamAttribute_Class;
	
	
	
	FClassReflection* Utils_Class{};
	
public:
	TMap<TWeakObjectPtr<UField>, FClassReflection*> ClassReflection;
	
	TMap<MonoClass*, FClassReflection*> ClassReflection1;
	
	TMap<TPair<FString, FString>, FClassReflection*> ClassReflection2;
};

#include "FReflectionRegistry.inl"
