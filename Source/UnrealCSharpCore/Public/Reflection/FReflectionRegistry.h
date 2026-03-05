#pragma once

#include "UEVersion.h"
#include "FClassReflection.h"
#include "Domain/FMonoDomain.h"

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
	FClassReflection* GetClass(const TWeakObjectPtr<UField>& InField);

	FClassReflection* GetClass(MonoReflectionType* InReflectionType);

	FClassReflection* GetClass(MonoClass* InClass);

	FClassReflection* GetClass(const FString& InNameSpace, const FString& InName);

	template <class T>
	auto GetClass() -> FClassReflection*;

public:
	FClassReflection* GetUtilsClass() const;

	FClassReflection* GetByteClass() const;

	FClassReflection* GetObjectClass() const;

	FClassReflection* GetUInt16Class() const;

	FClassReflection* GetUInt32Class() const;

	FClassReflection* GetUInt64Class() const;

	FClassReflection* GetSByteClass() const;

	FClassReflection* GetInt16Class() const;

	FClassReflection* GetInt32Class() const;

	FClassReflection* GetInt64Class() const;

	FClassReflection* GetBooleanClass() const;

	FClassReflection* GetSingleClass() const;

	FClassReflection* GetEnumClass() const;

	FClassReflection* GetDoubleClass() const;

	FClassReflection* GetUClassClass() const;

	FClassReflection* GetUObjectClass() const;

	FClassReflection* GetTSubclassOfClass() const;

	FClassReflection* GetNameClass() const;

	FClassReflection* GetTScriptInterfaceClass();

	FClassReflection* GetStringClass() const;

#if UE_F_UTF8_STR_PROPERTY
	FClassReflection* GetUtf8StringClass() const;
#endif

#if UE_F_ANSI_STR_PROPERTY
	FClassReflection* GetAnsiStringClass() const;
#endif

	FClassReflection* GetTextClass() const;

	FClassReflection* GetTWeakObjectPtrClass() const;

	FClassReflection* GetTLazyObjectPtrClass() const;

	FClassReflection* GetTSoftClassPtrClass() const;

	FClassReflection* GetTSoftObjectPtrClass() const;

	FClassReflection* GetTMapClass() const;

	FClassReflection* GetTSetClass() const;

	FClassReflection* GetTArrayClass() const;

#if UE_F_OPTIONAL_PROPERTY
	FClassReflection* GetTOptionalClass() const;
#endif

	FClassReflection* GetOverrideAttributeClass() const;

	FClassReflection* GetUClassAttributeClass() const;

	FClassReflection* GetUStructAttributeClass() const;

	FClassReflection* GetUEnumAttributeClass() const;

	FClassReflection* GetUInterfaceAttributeClass() const;

	FClassReflection* GetUPropertyAttributeClass() const;

	FClassReflection* GetUFunctionAttributeClass() const;

	FClassReflection* GetVisibleInstanceOnlyAttributeClass() const;

	FClassReflection* GetBlueprintCallableAttributeClass() const;

	FClassReflection* GetBlueprintAuthorityOnlyAttributeClass() const;

	FClassReflection* GetBlueprintGetterAttributeClass() const;

	FClassReflection* GetBlueprintSetterAttributeClass() const;

	FClassReflection* GetFieldNotifyAttributeClass() const;

	FClassReflection* GetTransientAttributeClass() const;

	FClassReflection* GetConfigAttributeClass() const;

	FClassReflection* GetBlueprintTypeAttributeClass() const;

	FClassReflection* GetNotBlueprintTypeAttributeClass() const;

	FClassReflection* GetBlueprintableAttributeClass() const;

	FClassReflection* GetNotBlueprintableAttributeClass() const;

	FClassReflection* GetNoExportAttributeClass() const;

	FClassReflection* GetAbstractAttributeClass() const;

	FClassReflection* GetExperimentalAttributeClass() const;

	FClassReflection* GetEditorConfigAttributeClass() const;

	FClassReflection* GetClassGroupAttributeClass() const;

	FClassReflection* GetWithinAttributeClass() const;

	FClassReflection* GetMinimalAPIAttributeClass() const;

	FClassReflection* GetCustomConstructorAttributeClass() const;

	FClassReflection* GetIntrinsicAttributeClass() const;

	FClassReflection* GetNotPlaceableAttributeClass() const;

	FClassReflection* GetDefaultToInstancedAttributeClass() const;

	FClassReflection* GetConstAttributeClass() const;

	FClassReflection* GetDeprecatedAttributeClass() const;

	FClassReflection* GetPerObjectConfigAttributeClass() const;

	FClassReflection* GetConfigDoNotCheckDefaultsAttributeClass() const;

	FClassReflection* GetDefaultConfigAttributeClass() const;

	FClassReflection* GetEditInlineNewAttributeClass() const;

	FClassReflection* GetNotEditInlineNewAttributeClass() const;

	FClassReflection* GetHideDropdownAttributeClass() const;

	FClassReflection* GetShowCategoriesAttributeClass() const;

	FClassReflection* GetComponentWrapperClassAttributeClass() const;

	FClassReflection* GetHideFunctionsAttributeClass() const;

	FClassReflection* GetAutoExpandCategoriesAttributeClass() const;

	FClassReflection* GetAutoCollapseCategoriesAttributeClass() const;

	FClassReflection* GetCollapseCategoriesAttributeClass() const;

	FClassReflection* GetDontCollapseCategoriesAttributeClass() const;

	FClassReflection* GetPrioritizeCategoriesAttributeClass() const;

	FClassReflection* GetAdvancedClassDisplayAttributeClass() const;

	FClassReflection* GetEarlyAccessPreviewAttributeClass() const;

	FClassReflection* GetSparseClassDataTypeAttributeClass() const;

	FClassReflection* GetGlobalConfigAttributeClass() const;

	FClassReflection* GetLocalizedAttributeClass() const;

	FClassReflection* GetDuplicateTransientAttributeClass() const;

	FClassReflection* GetNonPIETransientAttributeClass() const;

	FClassReflection* GetNonPIEDuplicateTransientAttributeClass() const;

	FClassReflection* GetExportAttributeClass() const;

	FClassReflection* GetNoClearAttributeClass() const;

	FClassReflection* GetEditFixedSizeAttributeClass() const;

	FClassReflection* GetReplicatedAttributeClass() const;

	FClassReflection* GetReplicatedUsingAttributeClass() const;

	FClassReflection* GetNotReplicatedAttributeClass() const;

	FClassReflection* GetInterpAttributeClass() const;

	FClassReflection* GetNonTransactionalAttributeClass() const;

	FClassReflection* GetInstancedAttributeClass() const;

	FClassReflection* GetBlueprintAssignableAttributeClass() const;

	FClassReflection* GetSimpleDisplayAttributeClass() const;

	FClassReflection* GetAdvancedDisplayAttributeClass() const;

	FClassReflection* GetEditAnywhereAttributeClass() const;

	FClassReflection* GetEditInstanceOnlyAttributeClass() const;

	FClassReflection* GetEditDefaultsOnlyAttributeClass() const;

	FClassReflection* GetVisibleAnywhereAttributeClass() const;

	FClassReflection* GetVisibleDefaultsOnlyAttributeClass() const;

	FClassReflection* GetBlueprintReadOnlyAttributeClass() const;

	FClassReflection* GetBlueprintReadWriteAttributeClass() const;

	FClassReflection* GetAssetRegistrySearchableAttributeClass() const;

	FClassReflection* GetSaveGameAttributeClass() const;

	FClassReflection* GetTextExportTransientAttributeClass() const;

	FClassReflection* GetSkipSerializationAttributeClass() const;

	FClassReflection* GetDefaultSubObjectAttributeClass() const;

	FClassReflection* GetRootComponentAttributeClass() const;

	FClassReflection* GetAttachmentParentAttributeClass() const;

	FClassReflection* GetAttachmentSocketNameAttributeClass() const;

	FClassReflection* GetDefaultValueAttributeClass() const;

	FClassReflection* GetBlueprintImplementableEventAttributeClass() const;

	FClassReflection* GetBlueprintNativeEventAttributeClass() const;

	FClassReflection* GetSealedEventAttributeClass() const;

	FClassReflection* GetExecAttributeClass() const;

	FClassReflection* GetServerAttributeClass() const;

	FClassReflection* GetClientAttributeClass() const;

	FClassReflection* GetNetMulticastAttributeClass() const;

	FClassReflection* GetReliableAttributeClass() const;

	FClassReflection* GetUnreliableAttributeClass() const;

	FClassReflection* GetBlueprintPureAttributeClass() const;

	FClassReflection* GetBlueprintCosmeticAttributeClass() const;

	FClassReflection* GetCustomThunkAttributeClass() const;

	FClassReflection* GetWithValidationAttributeClass() const;

	FClassReflection* GetServiceRequestAttributeClass() const;

	FClassReflection* GetServiceResponseAttributeClass() const;

#if WITH_EDITOR
	FClassReflection* GetHideCategoriesAttributeClass() const;

	FClassReflection* GetConversionRootAttributeClass() const;

	FClassReflection* GetCannotImplementInterfaceInBlueprintAttributeClass() const;

	FClassReflection* GetToolTipAttributeClass() const;

	FClassReflection* GetShortTooltipAttributeClass() const;

	FClassReflection* GetDocumentationPolicyAttributeClass() const;

	FClassReflection* GetBlueprintSpawnableComponentAttributeClass() const;

	FClassReflection* GetChildCanTickAttributeClass() const;

	FClassReflection* GetChildCannotTickAttributeClass() const;

	FClassReflection* GetDebugTreeLeafAttributeClass() const;

	FClassReflection* GetIgnoreCategoryKeywordsInSubclassesAttributeClass() const;

	FClassReflection* GetDeprecatedNodeAttributeClass() const;

	FClassReflection* GetDeprecationMessageAttributeClass() const;

	FClassReflection* GetDisplayNameAttributeClass() const;

	FClassReflection* GetScriptNameAttributeClass() const;

	FClassReflection* GetIsBlueprintBaseAttributeClass() const;

	FClassReflection* GetKismetHideOverridesAttributeClass() const;

	FClassReflection* GetLoadBehaviorAttributeClass() const;

	FClassReflection* GetProhibitedInterfacesAttributeClass() const;

	FClassReflection* GetRestrictedToClassesAttributeClass() const;

	FClassReflection* GetShowWorldContextPinAttributeClass() const;

	FClassReflection* GetDontUseGenericSpawnObjectAttributeClass() const;

	FClassReflection* GetExposedAsyncProxyAttributeClass() const;

	FClassReflection* GetBlueprintThreadSafeAttributeClass() const;

	FClassReflection* GetUsesHierarchyAttributeClass() const;

	FClassReflection* GetHasNativeBreakAttributeClass() const;

	FClassReflection* GetHasNativeMakeAttributeClass() const;

	FClassReflection* GetHiddenByDefaultAttributeClass() const;

	FClassReflection* GetDisableSplitPinAttributeClass() const;

	FClassReflection* GetAllowAbstractAttributeClass() const;

	FClassReflection* GetAllowAnyActorAttributeClass() const;

	FClassReflection* GetAllowedClassesAttributeClass() const;

	FClassReflection* GetAllowPreserveRatioAttributeClass() const;

	FClassReflection* GetAllowPrivateAccessAttributeClass() const;

	FClassReflection* GetArrayClampAttributeClass() const;

	FClassReflection* GetAssetBundlesAttributeClass() const;

	FClassReflection* GetBlueprintBaseOnlyAttributeClass() const;

	FClassReflection* GetBlueprintCompilerGeneratedDefaultsAttributeClass() const;

	FClassReflection* GetClampMinAttributeClass() const;

	FClassReflection* GetClampMaxAttributeClass() const;

	FClassReflection* GetConfigHierarchyEditableAttributeClass() const;

	FClassReflection* GetContentDirAttributeClass() const;

	FClassReflection* GetDeltaAttributeClass() const;

	FClassReflection* GetDeprecatedPropertyAttributeClass() const;

	FClassReflection* GetDisallowedAssetDataTagsAttributeClass() const;

	FClassReflection* GetDisallowedClassesAttributeClass() const;

	FClassReflection* GetDisplayAfterAttributeClass() const;

	FClassReflection* GetDisplayPriorityAttributeClass() const;

	FClassReflection* GetDisplayThumbnailAttributeClass() const;

	FClassReflection* GetEditConditionAttributeClass() const;

	FClassReflection* GetEditConditionHidesAttributeClass() const;

	FClassReflection* GetEditFixedOrderAttributeClass() const;

	FClassReflection* GetCategoryAttributeClass() const;

	FClassReflection* GetExactClassAttributeClass() const;

	FClassReflection* GetExposeFunctionCategoriesAttributeClass() const;

	FClassReflection* GetExposeOnSpawnAttributeClass() const;

	FClassReflection* GetFilePathFilterAttributeClass() const;

	FClassReflection* GetRelativeToGameDirAttributeClass() const;

	FClassReflection* GetFixedIncrementAttributeClass() const;

	FClassReflection* GetForceShowEngineContentAttributeClass() const;

	FClassReflection* GetForceShowPluginContentAttributeClass() const;

	FClassReflection* GetHideAlphaChannelAttributeClass() const;

	FClassReflection* GetHideInDetailPanelAttributeClass() const;

	FClassReflection* GetHideViewOptionsAttributeClass() const;

	FClassReflection* GetIgnoreForMemberInitializationTestAttributeClass() const;

	FClassReflection* GetInlineEditConditionToggleAttributeClass() const;

	FClassReflection* GetLinearDeltaSensitivityAttributeClass() const;

	FClassReflection* GetLongPackageNameAttributeClass() const;

	FClassReflection* GetMakeEditWidgetAttributeClass() const;

	FClassReflection* GetMakeStructureDefaultValueAttributeClass() const;

	FClassReflection* GetMetaClassAttributeClass() const;

	FClassReflection* GetMustImplementAttributeClass() const;

	FClassReflection* GetMultipleAttributeClass() const;

	FClassReflection* GetMaxLengthAttributeClass() const;

	FClassReflection* GetMultiLineAttributeClass() const;

	FClassReflection* GetPasswordFieldAttributeClass() const;

	FClassReflection* GetNoElementDuplicateAttributeClass() const;

	FClassReflection* GetNoResetToDefaultAttributeClass() const;

	FClassReflection* GetEditInlineAttributeClass() const;

	FClassReflection* GetNoEditInlineAttributeClass() const;

	FClassReflection* GetNoSpinboxAttributeClass() const;

	FClassReflection* GetOnlyPlaceableAttributeClass() const;

	FClassReflection* GetRelativePathAttributeClass() const;

	FClassReflection* GetRelativeToGameContentDirAttributeClass() const;

	FClassReflection* GetRequiredAssetDataTagsAttributeClass() const;

	FClassReflection* GetScriptNoExportAttributeClass() const;

	FClassReflection* GetShowOnlyInnerPropertiesAttributeClass() const;

	FClassReflection* GetShowTreeViewAttributeClass() const;

	FClassReflection* GetSliderExponentAttributeClass() const;

	FClassReflection* GetTitlePropertyAttributeClass() const;

	FClassReflection* GetUIMinAttributeClass() const;

	FClassReflection* GetUIMaxAttributeClass() const;

	FClassReflection* GetUnitsAttributeClass() const;

	FClassReflection* GetForceUnitsAttributeClass() const;

	FClassReflection* GetUntrackedAttributeClass() const;

	FClassReflection* GetDevelopmentOnlyAttributeClass() const;

	FClassReflection* GetNeedsLatentFixupAttributeClass() const;

	FClassReflection* GetLatentCallbackTargetAttributeClass() const;

	FClassReflection* GetGetOptionsAttributeClass() const;

	FClassReflection* GetPinHiddenByDefaultAttributeClass() const;

	FClassReflection* GetValidEnumValuesAttributeClass() const;

	FClassReflection* GetInvalidEnumValuesAttributeClass() const;

	FClassReflection* GetOverridingInputPropertyAttributeClass() const;

	FClassReflection* GetRequiredInputAttributeClass() const;

	FClassReflection* GetNeverAsPinAttributeClass() const;

	FClassReflection* GetPinShownByDefaultAttributeClass() const;

	FClassReflection* GetAlwaysAsPinAttributeClass() const;

	FClassReflection* GetCustomizePropertyAttributeClass() const;

	FClassReflection* GetCallInEditorAttributeClass() const;

	FClassReflection* GetVariadicAttributeClass() const;

	FClassReflection* GetReturnDisplayNameAttributeClass() const;

	FClassReflection* GetInternalUseParamAttributeClass() const;

	FClassReflection* GetForceAsFunctionAttributeClass() const;

	FClassReflection* GetIgnoreTypePromotionAttributeClass() const;

	FClassReflection* GetArrayParmAttributeClass() const;

	FClassReflection* GetArrayTypeDependentParamsAttributeClass() const;

	FClassReflection* GetAutoCreateRefTermAttributeClass() const;

	FClassReflection* GetHideAssetPickerAttributeClass() const;

	FClassReflection* GetBlueprintInternalUseOnlyAttributeClass() const;

	FClassReflection* GetBlueprintProtectedAttributeClass() const;

	FClassReflection* GetCallableWithoutWorldContextAttributeClass() const;

	FClassReflection* GetCommutativeAssociativeBinaryOperatorAttributeClass() const;

	FClassReflection* GetCompactNodeTitleAttributeClass() const;

	FClassReflection* GetCustomStructureParamAttributeClass() const;

	FClassReflection* GetDefaultToSelfAttributeClass() const;

	FClassReflection* GetDeprecatedFunctionAttributeClass() const;

	FClassReflection* GetExpandEnumAsExecsAttributeClass() const;

	FClassReflection* GetExpandBoolAsExecsAttributeClass() const;

	FClassReflection* GetScriptMethodAttributeClass() const;

	FClassReflection* GetScriptMethodSelfReturnAttributeClass() const;

	FClassReflection* GetScriptOperatorAttributeClass() const;

	FClassReflection* GetScriptConstantAttributeClass() const;

	FClassReflection* GetScriptConstantHostAttributeClass() const;

	FClassReflection* GetHidePinAttributeClass() const;

	FClassReflection* GetHideSpawnParmsAttributeClass() const;

	FClassReflection* GetKeywordsAttributeClass() const;

	FClassReflection* GetLatentAttributeClass() const;

	FClassReflection* GetLatentInfoAttributeClass() const;

	FClassReflection* GetMaterialParameterCollectionFunctionAttributeClass() const;

	FClassReflection* GetNativeBreakFuncAttributeClass() const;

	FClassReflection* GetNativeMakeFuncAttributeClass() const;

	FClassReflection* GetUnsafeDuringActorConstructionAttributeClass() const;

	FClassReflection* GetWorldContextAttributeClass() const;

	FClassReflection* GetBlueprintAutoCastAttributeClass() const;

	FClassReflection* GetNotBlueprintThreadSafeAttributeClass() const;

	FClassReflection* GetDeterminesOutputTypeAttributeClass() const;

	FClassReflection* GetDynamicOutputParamAttributeClass() const;

	FClassReflection* GetDataTablePinAttributeClass() const;

	FClassReflection* GetSetParamAttributeClass() const;

	FClassReflection* GetMapParamAttributeClass() const;

	FClassReflection* GetMapKeyParamAttributeClass() const;

	FClassReflection* GetMapValueParamAttributeClass() const;

	FClassReflection* GetBitmaskAttributeClass() const;

	FClassReflection* GetBitmaskEnumAttributeClass() const;

	FClassReflection* GetBitflagsAttributeClass() const;

	FClassReflection* GetUseEnumValuesAsMaskValuesInEditorAttributeClass() const;

	FClassReflection* GetArrayParamAttributeClass() const;
#endif

private:
	static MonoClass* GetMonoClass(const TWeakObjectPtr<UField>& InField);

private:
	FClassReflection* UtilsClass{};

	FClassReflection* ByteClass{};

	FClassReflection* ObjectClass{};

	FClassReflection* UInt16Class{};

	FClassReflection* UInt32Class{};

	FClassReflection* UInt64Class{};

	FClassReflection* SByteClass{};

	FClassReflection* Int16Class{};

	FClassReflection* Int32Class{};

	FClassReflection* Int64Class{};

	FClassReflection* BooleanClass{};

	FClassReflection* SingleClass{};

	FClassReflection* EnumClass{};

	FClassReflection* DoubleClass{};

	FClassReflection* UClassClass{};

	FClassReflection* TSubclassOfClass{};

	FClassReflection* UObjectClass{};

	FClassReflection* NameClass{};

	FClassReflection* TScriptInterfaceClass{};

	FClassReflection* StringClass{};

#if UE_F_UTF8_STR_PROPERTY
	FClassReflection* Utf8StringClass{};
#endif

#if UE_F_ANSI_STR_PROPERTY
	FClassReflection* AnsiStringClass{};
#endif

	FClassReflection* TextClass{};

	FClassReflection* TWeakObjectPtrClass{};

	FClassReflection* TLazyObjectPtrClass{};

	FClassReflection* TSoftClassPtrClass{};

	FClassReflection* TSoftObjectPtrClass{};

	FClassReflection* TMapClass{};

	FClassReflection* TSetClass{};

	FClassReflection* TArrayClass{};

#if UE_F_OPTIONAL_PROPERTY
	FClassReflection* TOptionalClass{};
#endif

	FClassReflection* OverrideAttributeClass{};

	FClassReflection* UClassAttributeClass{};

	FClassReflection* UStructAttributeClass{};

	FClassReflection* UEnumAttributeClass{};

	FClassReflection* UInterfaceAttributeClass{};

	FClassReflection* UPropertyAttributeClass{};

	FClassReflection* UFunctionAttributeClass{};

	FClassReflection* VisibleInstanceOnlyAttributeClass{};

	FClassReflection* BlueprintCallableAttributeClass{};

	FClassReflection* BlueprintAuthorityOnlyAttributeClass{};

	FClassReflection* BlueprintGetterAttributeClass{};

	FClassReflection* BlueprintSetterAttributeClass{};

	FClassReflection* FieldNotifyAttributeClass{};

	FClassReflection* TransientAttributeClass{};

	FClassReflection* ConfigAttributeClass{};

	FClassReflection* BlueprintTypeAttributeClass{};

	FClassReflection* NotBlueprintTypeAttributeClass{};

	FClassReflection* BlueprintableAttributeClass{};

	FClassReflection* NotBlueprintableAttributeClass{};

	FClassReflection* NoExportAttributeClass{};

	FClassReflection* AbstractAttributeClass{};

	FClassReflection* ExperimentalAttributeClass{};

	FClassReflection* EditorConfigAttributeClass{};

	FClassReflection* ClassGroupAttributeClass{};

	FClassReflection* WithinAttributeClass{};

	FClassReflection* MinimalAPIAttributeClass{};

	FClassReflection* CustomConstructorAttributeClass{};

	FClassReflection* IntrinsicAttributeClass{};

	FClassReflection* NotPlaceableAttributeClass{};

	FClassReflection* DefaultToInstancedAttributeClass{};

	FClassReflection* ConstAttributeClass{};

	FClassReflection* DeprecatedAttributeClass{};

	FClassReflection* PerObjectConfigAttributeClass{};

	FClassReflection* ConfigDoNotCheckDefaultsAttributeClass{};

	FClassReflection* DefaultConfigAttributeClass{};

	FClassReflection* EditInlineNewAttributeClass{};

	FClassReflection* NotEditInlineNewAttributeClass{};

	FClassReflection* HideDropdownAttributeClass{};

	FClassReflection* ShowCategoriesAttributeClass{};

	FClassReflection* ComponentWrapperClassAttributeClass{};

	FClassReflection* HideFunctionsAttributeClass{};

	FClassReflection* AutoExpandCategoriesAttributeClass{};

	FClassReflection* AutoCollapseCategoriesAttributeClass{};

	FClassReflection* CollapseCategoriesAttributeClass{};

	FClassReflection* DontCollapseCategoriesAttributeClass{};

	FClassReflection* PrioritizeCategoriesAttributeClass{};

	FClassReflection* AdvancedClassDisplayAttributeClass{};

	FClassReflection* EarlyAccessPreviewAttributeClass{};

	FClassReflection* SparseClassDataTypeAttributeClass{};

	FClassReflection* GlobalConfigAttributeClass{};

	FClassReflection* LocalizedAttributeClass{};

	FClassReflection* DuplicateTransientAttributeClass{};

	FClassReflection* NonPIETransientAttributeClass{};

	FClassReflection* NonPIEDuplicateTransientAttributeClass{};

	FClassReflection* ExportAttributeClass{};

	FClassReflection* NoClearAttributeClass{};

	FClassReflection* EditFixedSizeAttributeClass{};

	FClassReflection* ReplicatedAttributeClass{};

	FClassReflection* ReplicatedUsingAttributeClass{};

	FClassReflection* NotReplicatedAttributeClass{};

	FClassReflection* InterpAttributeClass{};

	FClassReflection* NonTransactionalAttributeClass{};

	FClassReflection* InstancedAttributeClass{};

	FClassReflection* BlueprintAssignableAttributeClass{};

	FClassReflection* SimpleDisplayAttributeClass{};

	FClassReflection* AdvancedDisplayAttributeClass{};

	FClassReflection* EditAnywhereAttributeClass{};

	FClassReflection* EditInstanceOnlyAttributeClass{};

	FClassReflection* EditDefaultsOnlyAttributeClass{};

	FClassReflection* VisibleAnywhereAttributeClass{};

	FClassReflection* VisibleDefaultsOnlyAttributeClass{};

	FClassReflection* BlueprintReadOnlyAttributeClass{};

	FClassReflection* BlueprintReadWriteAttributeClass{};

	FClassReflection* AssetRegistrySearchableAttributeClass{};

	FClassReflection* SaveGameAttributeClass{};

	FClassReflection* TextExportTransientAttributeClass{};

	FClassReflection* SkipSerializationAttributeClass{};

	FClassReflection* DefaultSubObjectAttributeClass{};

	FClassReflection* RootComponentAttributeClass{};

	FClassReflection* AttachmentParentAttributeClass{};

	FClassReflection* AttachmentSocketNameAttributeClass{};

	FClassReflection* DefaultValueAttributeClass{};

	FClassReflection* BlueprintImplementableEventAttributeClass{};

	FClassReflection* BlueprintNativeEventAttributeClass{};

	FClassReflection* SealedEventAttributeClass{};

	FClassReflection* ExecAttributeClass{};

	FClassReflection* ServerAttributeClass{};

	FClassReflection* ClientAttributeClass{};

	FClassReflection* NetMulticastAttributeClass{};

	FClassReflection* ReliableAttributeClass{};

	FClassReflection* UnreliableAttributeClass{};

	FClassReflection* BlueprintPureAttributeClass{};

	FClassReflection* BlueprintCosmeticAttributeClass{};

	FClassReflection* CustomThunkAttributeClass{};

	FClassReflection* WithValidationAttributeClass{};

	FClassReflection* ServiceRequestAttributeClass{};

	FClassReflection* ServiceResponseAttributeClass{};

#if WITH_EDITOR
	FClassReflection* HideCategoriesAttributeClass{};

	FClassReflection* ConversionRootAttributeClass{};

	FClassReflection* CannotImplementInterfaceInBlueprintAttributeClass{};

	FClassReflection* ToolTipAttributeClass{};

	FClassReflection* ShortTooltipAttributeClass{};

	FClassReflection* DocumentationPolicyAttributeClass{};

	FClassReflection* BlueprintSpawnableComponentAttributeClass{};

	FClassReflection* ChildCanTickAttributeClass{};

	FClassReflection* ChildCannotTickAttributeClass{};

	FClassReflection* DebugTreeLeafAttributeClass{};

	FClassReflection* IgnoreCategoryKeywordsInSubclassesAttributeClass{};

	FClassReflection* DeprecatedNodeAttributeClass{};

	FClassReflection* DeprecationMessageAttributeClass{};

	FClassReflection* DisplayNameAttributeClass{};

	FClassReflection* ScriptNameAttributeClass{};

	FClassReflection* IsBlueprintBaseAttributeClass{};

	FClassReflection* KismetHideOverridesAttributeClass{};

	FClassReflection* LoadBehaviorAttributeClass{};

	FClassReflection* ProhibitedInterfacesAttributeClass{};

	FClassReflection* RestrictedToClassesAttributeClass{};

	FClassReflection* ShowWorldContextPinAttributeClass{};

	FClassReflection* DontUseGenericSpawnObjectAttributeClass{};

	FClassReflection* ExposedAsyncProxyAttributeClass{};

	FClassReflection* BlueprintThreadSafeAttributeClass{};

	FClassReflection* UsesHierarchyAttributeClass{};

	FClassReflection* HasNativeBreakAttributeClass{};

	FClassReflection* HasNativeMakeAttributeClass{};

	FClassReflection* HiddenByDefaultAttributeClass{};

	FClassReflection* DisableSplitPinAttributeClass{};

	FClassReflection* AllowAbstractAttributeClass{};

	FClassReflection* AllowAnyActorAttributeClass{};

	FClassReflection* AllowedClassesAttributeClass{};

	FClassReflection* AllowPreserveRatioAttributeClass{};

	FClassReflection* AllowPrivateAccessAttributeClass{};

	FClassReflection* ArrayClampAttributeClass{};

	FClassReflection* AssetBundlesAttributeClass{};

	FClassReflection* BlueprintBaseOnlyAttributeClass{};

	FClassReflection* BlueprintCompilerGeneratedDefaultsAttributeClass{};

	FClassReflection* ClampMinAttributeClass{};

	FClassReflection* ClampMaxAttributeClass{};

	FClassReflection* ConfigHierarchyEditableAttributeClass{};

	FClassReflection* ContentDirAttributeClass{};

	FClassReflection* DeltaAttributeClass{};

	FClassReflection* DeprecatedPropertyAttributeClass{};

	FClassReflection* DisallowedAssetDataTagsAttributeClass{};

	FClassReflection* DisallowedClassesAttributeClass{};

	FClassReflection* DisplayAfterAttributeClass{};

	FClassReflection* DisplayPriorityAttributeClass{};

	FClassReflection* DisplayThumbnailAttributeClass{};

	FClassReflection* EditConditionAttributeClass{};

	FClassReflection* EditConditionHidesAttributeClass{};

	FClassReflection* EditFixedOrderAttributeClass{};

	FClassReflection* CategoryAttributeClass{};

	FClassReflection* ExactClassAttributeClass{};

	FClassReflection* ExposeFunctionCategoriesAttributeClass{};

	FClassReflection* ExposeOnSpawnAttributeClass{};

	FClassReflection* FilePathFilterAttributeClass{};

	FClassReflection* RelativeToGameDirAttributeClass{};

	FClassReflection* FixedIncrementAttributeClass{};

	FClassReflection* ForceShowEngineContentAttributeClass{};

	FClassReflection* ForceShowPluginContentAttributeClass{};

	FClassReflection* HideAlphaChannelAttributeClass{};

	FClassReflection* HideInDetailPanelAttributeClass{};

	FClassReflection* HideViewOptionsAttributeClass{};

	FClassReflection* IgnoreForMemberInitializationTestAttributeClass{};

	FClassReflection* InlineEditConditionToggleAttributeClass{};

	FClassReflection* LinearDeltaSensitivityAttributeClass{};

	FClassReflection* LongPackageNameAttributeClass{};

	FClassReflection* MakeEditWidgetAttributeClass{};

	FClassReflection* MakeStructureDefaultValueAttributeClass{};

	FClassReflection* MetaClassAttributeClass{};

	FClassReflection* MustImplementAttributeClass{};

	FClassReflection* MultipleAttributeClass{};

	FClassReflection* MaxLengthAttributeClass{};

	FClassReflection* MultiLineAttributeClass{};

	FClassReflection* PasswordFieldAttributeClass{};

	FClassReflection* NoElementDuplicateAttributeClass{};

	FClassReflection* NoResetToDefaultAttributeClass{};

	FClassReflection* EditInlineAttributeClass{};

	FClassReflection* NoEditInlineAttributeClass{};

	FClassReflection* NoSpinboxAttributeClass{};

	FClassReflection* OnlyPlaceableAttributeClass{};

	FClassReflection* RelativePathAttributeClass{};

	FClassReflection* RelativeToGameContentDirAttributeClass{};

	FClassReflection* RequiredAssetDataTagsAttributeClass{};

	FClassReflection* ScriptNoExportAttributeClass{};

	FClassReflection* ShowOnlyInnerPropertiesAttributeClass{};

	FClassReflection* ShowTreeViewAttributeClass{};

	FClassReflection* SliderExponentAttributeClass{};

	FClassReflection* TitlePropertyAttributeClass{};

	FClassReflection* UIMinAttributeClass{};

	FClassReflection* UIMaxAttributeClass{};

	FClassReflection* UnitsAttributeClass{};

	FClassReflection* ForceUnitsAttributeClass{};

	FClassReflection* UntrackedAttributeClass{};

	FClassReflection* DevelopmentOnlyAttributeClass{};

	FClassReflection* NeedsLatentFixupAttributeClass{};

	FClassReflection* LatentCallbackTargetAttributeClass{};

	FClassReflection* GetOptionsAttributeClass{};

	FClassReflection* PinHiddenByDefaultAttributeClass{};

	FClassReflection* ValidEnumValuesAttributeClass{};

	FClassReflection* InvalidEnumValuesAttributeClass{};

	FClassReflection* OverridingInputPropertyAttributeClass{};

	FClassReflection* RequiredInputAttributeClass{};

	FClassReflection* NeverAsPinAttributeClass{};

	FClassReflection* PinShownByDefaultAttributeClass{};

	FClassReflection* AlwaysAsPinAttributeClass{};

	FClassReflection* CustomizePropertyAttributeClass{};

	FClassReflection* CallInEditorAttributeClass{};

	FClassReflection* VariadicAttributeClass{};

	FClassReflection* ReturnDisplayNameAttributeClass{};

	FClassReflection* InternalUseParamAttributeClass{};

	FClassReflection* ForceAsFunctionAttributeClass{};

	FClassReflection* IgnoreTypePromotionAttributeClass{};

	FClassReflection* ArrayParmAttributeClass{};

	FClassReflection* ArrayTypeDependentParamsAttributeClass{};

	FClassReflection* AutoCreateRefTermAttributeClass{};

	FClassReflection* HideAssetPickerAttributeClass{};

	FClassReflection* BlueprintInternalUseOnlyAttributeClass{};

	FClassReflection* BlueprintProtectedAttributeClass{};

	FClassReflection* CallableWithoutWorldContextAttributeClass{};

	FClassReflection* CommutativeAssociativeBinaryOperatorAttributeClass{};

	FClassReflection* CompactNodeTitleAttributeClass{};

	FClassReflection* CustomStructureParamAttributeClass{};

	FClassReflection* DefaultToSelfAttributeClass{};

	FClassReflection* DeprecatedFunctionAttributeClass{};

	FClassReflection* ExpandEnumAsExecsAttributeClass{};

	FClassReflection* ExpandBoolAsExecsAttributeClass{};

	FClassReflection* ScriptMethodAttributeClass{};

	FClassReflection* ScriptMethodSelfReturnAttributeClass{};

	FClassReflection* ScriptOperatorAttributeClass{};

	FClassReflection* ScriptConstantAttributeClass{};

	FClassReflection* ScriptConstantHostAttributeClass{};

	FClassReflection* HidePinAttributeClass{};

	FClassReflection* HideSpawnParmsAttributeClass{};

	FClassReflection* KeywordsAttributeClass{};

	FClassReflection* LatentAttributeClass{};

	FClassReflection* LatentInfoAttributeClass{};

	FClassReflection* MaterialParameterCollectionFunctionAttributeClass{};

	FClassReflection* NativeBreakFuncAttributeClass{};

	FClassReflection* NativeMakeFuncAttributeClass{};

	FClassReflection* UnsafeDuringActorConstructionAttributeClass{};

	FClassReflection* WorldContextAttributeClass{};

	FClassReflection* BlueprintAutoCastAttributeClass{};

	FClassReflection* NotBlueprintThreadSafeAttributeClass{};

	FClassReflection* DeterminesOutputTypeAttributeClass{};

	FClassReflection* DynamicOutputParamAttributeClass{};

	FClassReflection* DataTablePinAttributeClass{};

	FClassReflection* SetParamAttributeClass{};

	FClassReflection* MapParamAttributeClass{};

	FClassReflection* MapKeyParamAttributeClass{};

	FClassReflection* MapValueParamAttributeClass{};

	FClassReflection* BitmaskAttributeClass{};

	FClassReflection* BitmaskEnumAttributeClass{};

	FClassReflection* BitflagsAttributeClass{};

	FClassReflection* UseEnumValuesAsMaskValuesInEditorAttributeClass{};

	FClassReflection* ArrayParamAttributeClass{};
#endif

private:
	TMap<TWeakObjectPtr<UField>, FClassReflection*> Field2Class;

	TMap<MonoClass*, FClassReflection*> Class2Class;

	TMap<MonoReflectionType*, FClassReflection*> ReflectionType2Class;

	TMap<TPair<FString, FString>, FClassReflection*> NameNameSpace2Class;
};

#include "FReflectionRegistry.inl"
