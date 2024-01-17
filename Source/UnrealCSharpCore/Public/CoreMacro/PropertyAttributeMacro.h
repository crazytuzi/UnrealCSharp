#pragma once

#define CLASS_U_PROPERTY_ATTRIBUTE FString(TEXT("UPropertyAttribute"))

#define CLASS_EDIT_ANYWHERE_ATTRIBUTE FString(TEXT("EditAnywhereAttribute"))

#define CLASS_EDIT_INSTANCE_ONLY_ATTRIBUTE FString(TEXT("EditInstanceOnlyAttribute"))

#define CLASS_EDIT_DEFAULTS_ONLY_ATTRIBUTE FString(TEXT("EditDefaultsOnlyAttribute"))

#define CLASS_VISIBLE_ANYWHERE_ATTRIBUTE FString(TEXT("VisibleAnywhereAttribute"))

#define CLASS_VISIBLE_DEFAULTS_ONLY_ATTRIBUTE FString(TEXT("VisibleDefaultsOnlyAttribute"))

#define CLASS_BLUEPRINT_READ_WRITE_ATTRIBUTE FString(TEXT("BlueprintReadWriteAttribute"))

#define CLASS_BLUEPRINT_READ_ONLY_ATTRIBUTE FString(TEXT("BlueprintReadOnlyAttribute"))

#define CLASS_CONFIG_ATTRIBUTE FString(TEXT("ConfigAttribute"))

#define CLASS_GLOBAL_CONFIG_ATTRIBUTE FString(TEXT("GlobalConfigAttribute"))

#define CLASS_LOCALIZED_ATTRIBUTE FString(TEXT("LocalizedAttribute"))

#define CLASS_TRANSIENT_ATTRIBUTE FString(TEXT("TransientAttribute"))

#define CLASS_DUPLICATE_TRANSIENT_ATTRIBUTE FString(TEXT("DuplicateTransientAttribute"))

#define CLASS_TEXT_EXPORT_TRANSIENT_ATTRIBUTE FString(TEXT("TextExportTransientAttribute"))

#define CLASS_NON_PIE_TRANSIENT_ATTRIBUTE FString(TEXT("NonPIETransientAttribute"))

#define CLASS_NON_PIE_DUPLICATE_TRANSIENT_ATTRIBUTE FString(TEXT("NonPIEDuplicateTransientAttribute"))

#define CLASS_EXPORT_ATTRIBUTE FString(TEXT("ExportAttribute"))

#define CLASS_EDIT_INLINE_ATTRIBUTE FString(TEXT("EditInlineAttribute"))

#define CLASS_NO_CLEAR_ATTRIBUTE FString(TEXT("NoClearAttribute"))

#define CLASS_EDIT_FIXED_SIZE_ATTRIBUTE FString(TEXT("EditFixedSizeAttribute"))

#define CLASS_REPLICATED_ATTRIBUTE FString(TEXT("ReplicatedAttribute"))

#define CLASS_REPLICATED_USING_ATTRIBUTE FString(TEXT("ReplicatedUsingAttribute"))

#define CLASS_NOT_REPLICATED_ATTRIBUTE FString(TEXT("NotReplicatedAttribute"))

#define CLASS_REP_RETRY_ATTRIBUTE FString(TEXT("RepRetryAttribute"))

#define CLASS_INTERP_ATTRIBUTE FString(TEXT("InterpAttribute"))

#define CLASS_NON_TRANSACTIONAL_ATTRIBUTE FString(TEXT("NonTransactionalAttribute"))

#define CLASS_INSTANCED_ATTRIBUTE FString(TEXT("InstancedAttribute"))

#define CLASS_BLUEPRINT_ASSIGNABLE_ATTRIBUTE FString(TEXT("BlueprintAssignableAttribute"))

#define CLASS_BLUEPRINT_AUTHORITY_ONLY_ATTRIBUTE FString(TEXT("BlueprintAuthorityOnlyAttribute"))

#define CLASS_ASSET_REGISTRY_SEARCHABLE_ATTRIBUTE FString(TEXT("AssetRegistrySearchableAttribute"))

#define CLASS_SIMPLE_DISPLAY_ATTRIBUTE FString(TEXT("SimpleDisplayAttribute"))

#define CLASS_ADVANCED_DISPLAY_ATTRIBUTE FString(TEXT("AdvancedDisplayAttribute"))

#define CLASS_SAVE_GAME_ATTRIBUTE FString(TEXT("SaveGameAttribute"))

#define CLASS_SKIP_SERIALIZATION_ATTRIBUTE FString(TEXT("SkipSerializationAttribute"))

#define CLASS_SETTER_ATTRIBUTE FString(TEXT("SetterAttribute"))

#define CLASS_GETTER_ATTRIBUTE FString(TEXT("GetterAttribute"))

TArray<FString>PropertyMetadata={
	"DeprecationMessageAttribute",
	"DisplayNameAttribute",
	"ScriptNameAttribute",
	"LoadBehaviorAttribute",
	"AllowAbstractAttribute",
	"AllowAnyActorAttribute",
	"AllowedClassesAttribute",
	"AllowPreserveRatioAttribute",
	"AllowPrivateAccessAttribute",
	"ArrayClampAttribute",
	"AssetBundlesAttribute",
	"BlueprintBaseOnlyAttribute",
	"BlueprintCompilerGeneratedDefaultsAttribute",
	"ClampMinAttribute",
	"ClampMaxAttribute",
	"ConfigHierarchyEditableAttribute",
	"ContentDirAttribute",
	"DeltaAttribute",
	"DeprecatedPropertyAttribute",
	"DisallowedAssetDataTagsAttribute",
	"DisallowedClassesAttribute",
	"DisplayAfterAttribute",
	"DisplayPriorityAttribute",
	"DisplayThumbnailAttribute",
	"EditConditionAttribute",
	"EditConditionHidesAttribute",
	"EditFixedOrderAttribute",
	"ExactClassAttribute",
	"ExposeFunctionCategoriesAttribute",
	"ExposeOnSpawnAttribute",
	"FilePathFilterAttribute",
	"RelativeToGameDirAttribute",
	"FixedIncrementAttribute",
	"ForceShowEngineContentAttribute",
	"ForceShowPluginContentAttribute",
	"HideAlphaChannelAttribute",
	"HideInDetailPanelAttribute",
	"HideViewOptionsAttribute",
	"IgnoreForMemberInitializationTestAttribute",
	"InlineEditConditionToggleAttribute",
	"LinearDeltaSensitivityAttribute",
	"LongPackageNameAttribute",
	"MakeEditWidgetAttribute",
	"MakeStructureDefaultValueAttribute",
	"MetaClassAttribute",
	"MustImplementAttribute",
	"MultipleAttribute",
	"MaxLengthAttribute",
	"MultiLineAttribute",
	"PasswordFieldAttribute",
	"NoElementDuplicateAttribute",
	"NoResetToDefaultAttribute",
	"NoEditInlineAttribute",
	"NoSpinboxAttribute",
	"OnlyPlaceableAttribute",
	"RelativePathAttribute",
	"RelativeToGameContentDirAttribute",
	"RequiredAssetDataTagsAttribute",
	"ScriptNoExportAttribute",
	"ShowOnlyInnerPropertiesAttribute",
	"ShowTreeViewAttribute",
	"SliderExponentAttribute",
	"TitlePropertyAttribute",
	"UIMinAttribute",
	"UIMaxAttribute",
	"UnitsAttribute",
	"ForceUnitsAttribute",
	"UntrackedAttribute",
	"DevelopmentOnlyAttribute",
	"NeedsLatentFixupAttribute",
	"LatentCallbackTargetAttribute",
	"GetOptionsAttribute",
	"PinHiddenByDefaultAttribute",
	"ValidEnumValuesAttribute",
	"InvalidEnumValuesAttribute",
	"OverridingInputPropertyAttribute",
	"RequiredInputAttribute",
	"NeverAsPinAttribute",
	"PinShownByDefaultAttribute",
	"AlwaysAsPinAttribute",
	"CustomizePropertyAttribute",
};

TArray<FString>ClassMetadata={
	"BlueprintSpawnableComponentAttribute",
	"ChildCanTickAttribute",
	"ChildCannotTickAttribute",
	"DebugTreeLeafAttribute",
	"IgnoreCategoryKeywordsInSubclassesAttribute",
	"DeprecatedNodeAttribute",
	"DeprecationMessageAttribute",
	"DisplayNameAttribute",
	"ScriptNameAttribute",
	"IsBlueprintBaseAttribute",
	"KismetHideOverridesAttribute",
	"LoadBehaviorAttribute",
	"ProhibitedInterfacesAttribute",
	"RestrictedToClassesAttribute",
	"ShowWorldContextPinAttribute",
	"DontUseGenericSpawnObjectAttribute",
	"ExposedAsyncProxyAttribute",
	"BlueprintThreadSafeAttribute",
	"UsesHierarchyAttribute"
};

TArray<FString>FunctionMetadata={
	"CallInEditorAttribute",
	"VariadicAttribute",
	"ReturnDisplayNameAttribute",
	"InternalUseParamAttribute",
	"ForceAsFunctionAttribute",
	"IgnoreTypePromotionAttribute",
	"DeprecationMessageAttribute",
	"DisplayNameAttribute",
	"ScriptNameAttribute",
	"ScriptNoExportAttribute",
	"AdvancedDisplayAttribute",
	"ArrayParmAttribute",
	"ArrayTypeDependentParamsAttribute",
	"AutoCreateRefTermAttribute",
	"HideAssetPickerAttribute",
	"BlueprintInternalUseOnlyAttribute",
	"BlueprintProtectedAttribute",
	"CallableWithoutWorldContextAttribute",
	"CommutativeAssociativeBinaryOperatorAttribute",
	"CompactNodeTitleAttribute",
	"CustomStructureParamAttribute",
	"DefaultToSelfAttribute",
	"DeprecatedFunctionAttribute",
	"ExpandEnumAsExecsAttribute",
	"ExpandBoolAsExecsAttribute",
	"ScriptMethodAttribute",
	"ScriptMethodSelfReturnAttribute",
	"ScriptOperatorAttribute",
	"ScriptConstantAttribute",
	"ScriptConstantHostAttribute",
	"HidePinAttribute",
	"HideSpawnParmsAttribute",
	"KeywordsAttribute",
	"LatentAttribute",
	"LatentInfoAttribute",
	"MaterialParameterCollectionFunctionAttribute",
	"NativeBreakFuncAttribute",
	"NativeMakeFuncAttribute",
	"UnsafeDuringActorConstructionAttribute",
	"WorldContextAttribute",
	"BlueprintAutocastAttribute",
	"NotBlueprintThreadSafeAttribute",
	"DeterminesOutputTypeAttribute",
	"DynamicOutputParamAttribute",
	"DataTablePinAttribute",
	"SetParamAttribute",
	"MapParamAttribute",
	"MapKeyParamAttribute",
	"MapValueParamAttribute",
	"BitmaskAttribute",
	"BitmaskEnumAttribute",
	"ArrayParamAttribute"
};
