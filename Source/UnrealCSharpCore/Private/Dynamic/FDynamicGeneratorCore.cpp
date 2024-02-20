#include "Dynamic/FDynamicGeneratorCore.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "CoreMacro/FunctionAttributeMacro.h"
#include "CoreMacro/GenericAttributeMacro.h"
#include "CoreMacro/MetaDataAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Log/UnrealCSharpLog.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

TArray<FString> FDynamicGeneratorCore::ClassMetaDataAttrs =
{
	CLASS_BLUEPRINT_SPAWNABLE_COMPONENT_ATTRIBUTE,
	CLASS_CHILD_CAN_TICK_ATTRIBUTE,
	CLASS_CHILD_CANNOT_TICK_ATTRIBUTE,
	CLASS_DEBUG_TREE_LEAF_ATTRIBUTE,
	CLASS_IGNORE_CATEGORY_KEYWORDS_IN_SUBCLASSES_ATTRIBUTE,
	CLASS_DEPRECATED_NODE_ATTRIBUTE,
	CLASS_DEPRECATION_MESSAGE_ATTRIBUTE,
	CLASS_DISPLAY_NAME_ATTRIBUTE,
	CLASS_SCRIPT_NAME_ATTRIBUTE,
	CLASS_IS_BLUEPRINT_BASE_ATTRIBUTE,
	CLASS_KISMET_HIDE_OVERRIDES_ATTRIBUTE,
	CLASS_LOAD_BEHAVIOR_ATTRIBUTE,
	CLASS_PROHIBITED_INTERFACES_ATTRIBUTE,
	CLASS_RESTRICTED_TO_CLASSES_ATTRIBUTE,
	CLASS_SHOW_WORLD_CONTEXT_PIN_ATTRIBUTE,
	CLASS_DONT_USE_GENERIC_SPAWN_OBJECT_ATTRIBUTE,
	CLASS_EXPOSED_ASYNC_PROXY_ATTRIBUTE,
	CLASS_BLUEPRINT_THREAD_SAFE_ATTRIBUTE,
	CLASS_USES_HIERARCHY_ATTRIBUTE
};

TArray<FString> FDynamicGeneratorCore::StructMetaDataAttrs =
{
	CLASS_HAS_NATIVE_BREAK_ATTRIBUTE,
	CLASS_HAS_NATIVE_MAKE_ATTRIBUTE,
	CLASS_HIDDEN_BY_DEFAULT_ATTRIBUTE,
	CLASS_DISABLE_SPLIT_PIN_ATTRIBUTE
};

TArray<FString> FDynamicGeneratorCore::EnumMetaDataAttrs =
{
	CLASS_BITFLAGS_ATTRIBUTE,
	CLASS_USE_ENUM_VALUES_AS_MASK_VALUES_IN_EDITOR
};

TArray<FString> FDynamicGeneratorCore::PropertyMetaDataAttrs =
{
	CLASS_DEPRECATION_MESSAGE_ATTRIBUTE,
	CLASS_DISPLAY_NAME_ATTRIBUTE,
	CLASS_SCRIPT_NAME_ATTRIBUTE,
	CLASS_LOAD_BEHAVIOR_ATTRIBUTE,
	CLASS_ALLOW_ABSTRACT_ATTRIBUTE,
	CLASS_ALLOW_ANY_ACTOR_ATTRIBUTE,
	CLASS_ALLOWED_CLASSES_ATTRIBUTE,
	CLASS_ALLOW_PRESERVE_RATIO_ATTRIBUTE,
	CLASS_ALLOW_PRIVATE_ACCESS_ATTRIBUTE,
	CLASS_ARRAY_CLAMP_ATTRIBUTE,
	CLASS_ASSET_BUNDLES_ATTRIBUTE,
	CLASS_BLUEPRINT_BASE_ONLY_ATTRIBUTE,
	CLASS_BLUEPRINT_COMPILER_GENERATED_DEFAULTS_ATTRIBUTE,
	CLASS_CLAMP_MIN_ATTRIBUTE,
	CLASS_CLAMP_MAX_ATTRIBUTE,
	CLASS_CONFIG_HIERARCHY_EDITABLE_ATTRIBUTE,
	CLASS_CONTENT_DIR_ATTRIBUTE,
	CLASS_DELTA_ATTRIBUTE,
	CLASS_DEPRECATED_PROPERTY_ATTRIBUTE,
	CLASS_DISALLOWED_ASSET_DATA_TAGS_ATTRIBUTE,
	CLASS_DISALLOWED_CLASSES_ATTRIBUTE,
	CLASS_DISPLAY_AFTER_ATTRIBUTE,
	CLASS_DISPLAY_PRIORITY_ATTRIBUTE,
	CLASS_DISPLAY_THUMBNAIL_ATTRIBUTE,
	CLASS_EDIT_CONDITION_ATTRIBUTE,
	CLASS_EDIT_CONDITION_HIDES_ATTRIBUTE,
	CLASS_EDIT_FIXED_ORDER_ATTRIBUTE,
	CLASS_EXACT_CLASS_ATTRIBUTE,
	CLASS_EXPOSE_FUNCTION_CATEGORIES_ATTRIBUTE,
	CLASS_EXPOSE_ON_SPAWN_ATTRIBUTE,
	CLASS_FILE_PATH_FILTER_ATTRIBUTE,
	CLASS_RELATIVE_TO_GAME_DIR_ATTRIBUTE,
	CLASS_FIXED_INCREMENT_ATTRIBUTE,
	CLASS_FORCE_SHOW_ENGINE_CONTENT_ATTRIBUTE,
	CLASS_FORCE_SHOW_PLUGIN_CONTENT_ATTRIBUTE,
	CLASS_HIDE_ALPHA_CHANNEL_ATTRIBUTE,
	CLASS_HIDE_IN_DETAIL_PANEL_ATTRIBUTE,
	CLASS_HIDE_VIEW_OPTIONS_ATTRIBUTE,
	CLASS_IGNORE_FOR_MEMBER_INITIALIZATION_TEST_ATTRIBUTE,
	CLASS_INLINE_EDIT_CONDITION_TOGGLE_ATTRIBUTE,
	CLASS_LINEAR_DELTA_SENSITIVITY_ATTRIBUTE,
	CLASS_LONG_PACKAGE_NAME_ATTRIBUTE,
	CLASS_MAKE_EDIT_WIDGET_ATTRIBUTE,
	CLASS_MAKE_STRUCTURE_DEFAULT_VALUE_ATTRIBUTE,
	CLASS_META_CLASS_ATTRIBUTE,
	CLASS_MUST_IMPLEMENT_ATTRIBUTE,
	CLASS_MULTIPLE_ATTRIBUTE,
	CLASS_MAX_LENGTH_ATTRIBUTE,
	CLASS_MULTILINE_ATTRIBUTE,
	CLASS_PASSWORD_FIELD_ATTRIBUTE,
	CLASS_NO_ELEMENT_DUPLICATE_ATTRIBUTE,
	CLASS_NO_RESET_TO_DEFAULT_ATTRIBUTE,
	CLASS_NO_EDIT_INLINE_ATTRIBUTE,
	CLASS_NO_SPIN_BOX_ATTRIBUTE,
	CLASS_ONLY_PLACEABLE_ATTRIBUTE,
	CLASS_RELATIVE_PATH_ATTRIBUTE,
	CLASS_RELATIVE_TO_GAME_CONTENT_DIR_ATTRIBUTE,
	CLASS_REQUIRED_ASSET_DATA_TAGS_ATTRIBUTE,
	CLASS_SCRIPT_NO_EXPORT_ATTRIBUTE,
	CLASS_SHOW_ONLY_INNER_PROPERTIES_ATTRIBUTE,
	CLASS_SHOW_TREE_VIEW_ATTRIBUTE,
	CLASS_SLIDER_EXPONENT_ATTRIBUTE,
	CLASS_TITLE_PROPERTY_ATTRIBUTE,
	CLASS_UI_MIN_ATTRIBUTE,
	CLASS_UI_MAX_ATTRIBUTE,
	CLASS_UNITS_ATTRIBUTE,
	CLASS_FORCE_UNITS_ATTRIBUTE,
	CLASS_UNTRACKED_ATTRIBUTE,
	CLASS_DEVELOPMENT_ONLY_ATTRIBUTE,
	CLASS_NEEDS_LATENT_FIXUP_ATTRIBUTE,
	CLASS_LATENT_CALLBACK_TARGET_ATTRIBUTE,
	CLASS_GET_OPTIONS_ATTRIBUTE,
	CLASS_PIN_HIDDEN_BY_DEFAULT_ATTRIBUTE,
	CLASS_VALID_ENUM_VALUES_ATTRIBUTE,
	CLASS_INVALID_ENUM_VALUES_ATTRIBUTE,
	CLASS_OVERRIDING_INPUT_PROPERTY_ATTRIBUTE,
	CLASS_REQUIRED_INPUT_ATTRIBUTE,
	CLASS_NEVER_AS_PIN_ATTRIBUTE,
	CLASS_PIN_SHOWN_BY_DEFAULT_ATTRIBUTE,
	CLASS_ALWAYS_AS_PIN_ATTRIBUTE,
	CLASS_CUSTOMIZE_PROPERTY_ATTRIBUTE
};

TArray<FString> FDynamicGeneratorCore::FunctionMetaDataAttrs =
{
	CLASS_CALL_IN_EDITOR_ATTRIBUTE,
	CLASS_VARIADIC_ATTRIBUTE,
	CLASS_RETURN_DISPLAY_NAME_ATTRIBUTE,
	CLASS_INTERNAL_USE_PARAM_ATTRIBUTE,
	CLASS_FORCE_AS_FUNCTION_ATTRIBUTE,
	CLASS_IGNORE_TYPE_PROMOTION_ATTRIBUTE,
	CLASS_DEPRECATION_MESSAGE_ATTRIBUTE,
	CLASS_DISPLAY_NAME_ATTRIBUTE,
	CLASS_SCRIPT_NAME_ATTRIBUTE,
	CLASS_SCRIPT_NO_EXPORT_ATTRIBUTE,
	CLASS_ADVANCED_DISPLAY_ATTRIBUTE,
	CLASS_ARRAY_PARM_ATTRIBUTE,
	CLASS_ARRAY_TYPE_DEPENDENT_PARAMS_ATTRIBUTE,
	CLASS_AUTO_CREATE_REF_TERM_ATTRIBUTE,
	CLASS_HIDE_ASSET_PICKER_ATTRIBUTE,
	CLASS_BLUEPRINT_INTERNAL_USE_ONLY_ATTRIBUTE,
	CLASS_BLUEPRINT_PROTECTED_ATTRIBUTE,
	CLASS_CALLABLE_WITHOUT_WORLD_CONTEXT_ATTRIBUTE,
	CLASS_COMMUTATIVE_ASSOCIATIVE_BINARY_OPERATOR_ATTRIBUTE,
	CLASS_COMPACT_NODE_TITLE_ATTRIBUTE,
	CLASS_CUSTOM_STRUCTURE_PARAM_ATTRIBUTE,
	CLASS_DEFAULT_TO_SELF_ATTRIBUTE,
	CLASS_DEPRECATED_FUNCTION_ATTRIBUTE,
	CLASS_EXPAND_ENUM_AS_EXECS_ATTRIBUTE,
	CLASS_EXPAND_BOOL_AS_EXECS_ATTRIBUTE,
	CLASS_SCRIPT_METHOD_ATTRIBUTE,
	CLASS_SCRIPT_METHOD_SELF_RETURN_ATTRIBUTE,
	CLASS_SCRIPT_OPERATOR_ATTRIBUTE,
	CLASS_SCRIPT_CONSTANT_ATTRIBUTE,
	CLASS_SCRIPT_CONSTANT_HOST_ATTRIBUTE,
	CLASS_HIDE_PIN_ATTRIBUTE,
	CLASS_HIDE_SPAWN_PARMS_ATTRIBUTE,
	CLASS_KEYWORDS_ATTRIBUTE,
	CLASS_LATENT_ATTRIBUTE,
	CLASS_LATENT_INFO_ATTRIBUTE,
	CLASS_MATERIAL_PARAMETER_COLLECTION_FUNCTION_ATTRIBUTE,
	CLASS_NATIVE_BREAK_FUNC_ATTRIBUTE,
	CLASS_NATIVE_MAKE_FUNC_ATTRIBUTE,
	CLASS_UNSAFE_DURING_ACTOR_CONSTRUCTION_ATTRIBUTE,
	CLASS_WORLD_CONTEXT_ATTRIBUTE,
	CLASS_BLUEPRINT_AUTO_CAST_ATTRIBUTE,
	CLASS_BLUEPRINT_THREAD_SAFE_ATTRIBUTE,
	CLASS_NOT_BLUEPRINT_THREAD_SAFE_ATTRIBUTE,
	CLASS_DETERMINES_OUTPUT_TYPE_ATTRIBUTE,
	CLASS_DYNAMIC_OUTPUT_PARAM_ATTRIBUTE,
	CLASS_DATA_TABLE_PIN_ATTRIBUTE,
	CLASS_SET_PARAM_ATTRIBUTE,
	CLASS_MAP_PARAM_ATTRIBUTE,
	CLASS_MAP_KEY_PARAM_ATTRIBUTE,
	CLASS_MAP_VALUE_PARAM_ATTRIBUTE,
	CLASS_BIT_MASK_ATTRIBUTE,
	CLASS_BIT_MASK_ENUM_ATTRIBUTE,
	CLASS_ARRAY_PARAM_ATTRIBUTE
};

UPackage* FDynamicGeneratorCore::GetOuter()
{
	return UObject::StaticClass()->GetPackage();
}

FString FDynamicGeneratorCore::GetClassNameSpace()
{
	return FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass());
}

void FDynamicGeneratorCore::SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InProperty == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_ANYWHERE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_INSTANCE_ONLY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnTemplate);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_DEFAULTS_ONLY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnInstance);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_VISIBLE_ANYWHERE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_VISIBLE_INSTANCE_ONLY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst | CPF_DisableEditOnTemplate);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_READ_WRITE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_SETTER_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_READ_ONLY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible | CPF_BlueprintReadOnly);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_GETTER_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_CONFIG_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Config);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_GLOBAL_CONFIG_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_GlobalConfig | CPF_Config);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_LOCALIZED_ATTRIBUTE))
	{
		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Transient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_DUPLICATE_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_DuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_TEXT_EXPORT_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_TextExportTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NON_PIE_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NON_PIE_DUPLICATE_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EXPORT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_ExportObject);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NO_CLEAR_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_NoClear);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_FIXED_SIZE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_EditFixedSize);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_ATTRIBUTE))
	{
		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_USING_ATTRIBUTE))
	{
		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NOT_REPLICATED_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_RepSkip);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_INTERP_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_Interp);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NON_TRANSACTIONAL_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_NonTransactional);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_INSTANCED_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_PersistentInstance | CPF_ExportObject | CPF_InstancedReference);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_ASSIGNABLE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintAssignable);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_CALLABLE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintCallable);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_AUTHORITY_ONLY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintAuthorityOnly);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_ASSET_REGISTRY_SEARCHABLE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_AssetRegistrySearchable);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SIMPLE_DISPLAY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_SimpleDisplay);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_ADVANCED_DISPLAY_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_AdvancedDisplay);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SAVE_GAME_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_SaveGame);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SKIP_SERIALIZATION_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_SkipSerialization);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_FIELD_NOTIFY_ATTRIBUTE))
	{
		// @TODO
	}

#if WITH_EDITOR
	SetMetaData(InProperty, InMonoCustomAttrInfo);
#endif
}

enum class EDynamicFunctionExportFlags
{
	// function declaration included "final" keyword.  Used to differentiate between functions that have FUNC_Final only because they're private
	FUNCEXPORT_Final = 0x00000001,
	//									= 0x00000002,
	//									= 0x00000004,
	// Function should be exported as a public API function
	FUNCEXPORT_RequiredAPI = 0x00000008,
	// export as an inline static C++ function
	FUNCEXPORT_Inline = 0x00000010,
	// Export as a real C++ static function, causing thunks to call via ClassName::FuncName instead of this->FuncName
	FUNCEXPORT_CppStatic = 0x00000020,
	// Export no thunk function; the user will manually define a custom one
	FUNCEXPORT_CustomThunk = 0x00000040,
	//									= 0x00000080,
	//									= 0x00000100,
};

void FDynamicGeneratorCore::SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InFunction == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	auto bSpecifiedUnreliable = false;

	auto FunctionExportFlags = 0u;

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_NATIVE_EVENT_ATTRIBUTE))
	{
		if (InFunction->FunctionFlags & FUNC_Net)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("BlueprintNativeEvent functions cannot be replicated!"));
		}
		else if ((InFunction->FunctionFlags & FUNC_BlueprintEvent) && !(InFunction->FunctionFlags & FUNC_Native))
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT("A function cannot be both BlueprintNativeEvent and BlueprintImplementableEvent!"));
		}
		else if (InFunction->FunctionFlags & FUNC_Private)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("A Private function cannot be a BlueprintNativeEvent!"));
		}

		// @TODO A function cannot be both BlueprintNativeEvent and a Blueprint Property accessor!

		InFunction->FunctionFlags |= FUNC_Event;

		InFunction->FunctionFlags |= FUNC_BlueprintEvent;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_IMPLEMENTABLE_EVENT_ATTRIBUTE))
	{
		if (InFunction->FunctionFlags & FUNC_Net)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("BlueprintImplementableEvent functions cannot be replicated!"));
		}
		else if ((InFunction->FunctionFlags & FUNC_BlueprintEvent) && !(InFunction->FunctionFlags & FUNC_Native))
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT("A function cannot be both BlueprintNativeEvent and BlueprintImplementableEvent!"));
		}
		else if (InFunction->FunctionFlags & FUNC_Private)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("A Private function cannot be a BlueprintImplementableEvent!"));
		}

		InFunction->FunctionFlags |= FUNC_Event;

		InFunction->FunctionFlags |= FUNC_BlueprintEvent;

		InFunction->FunctionFlags &= ~FUNC_Native;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EXEC_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_Exec;

		if (InFunction->FunctionFlags & FUNC_Net)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SEALED_EVENT_ATTRIBUTE))
	{
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVER_ATTRIBUTE))
	{
		if ((InFunction->FunctionFlags & FUNC_BlueprintEvent) != 0)
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT(
				       "BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as Client or Server"
			       ));
		}

		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetServer;

		if (InFunction->FunctionFlags & FUNC_Exec)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_CLIENT_ATTRIBUTE))
	{
		if ((InFunction->FunctionFlags & FUNC_BlueprintEvent) != 0)
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT(
				       "BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as Client or Server"
			       ));
		}

		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetClient;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NET_MULTICAST_ATTRIBUTE))
	{
		if ((InFunction->FunctionFlags & FUNC_BlueprintEvent) != 0)
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT(
				       "BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as Client or Server"
			       ));
		}

		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetMulticast;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVICE_REQUEST_ATTRIBUTE))
	{
		if ((InFunction->FunctionFlags & FUNC_BlueprintEvent) != 0)
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT(
				       "BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as a ServiceRequest"
			       ));
		}

		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetRequest;

		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVICE_RESPONSE_ATTRIBUTE))
	{
		if (InFunction->FunctionFlags & FUNC_BlueprintEvent)
		{
			UE_LOG(LogUnrealCSharp, Error,
			       TEXT(
				       "BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as a ServiceResponse"
			       ));
		}

		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetResponse;

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_RELIABLE_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_NetReliable;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_UNRELIABLE_ATTRIBUTE))
	{
		bSpecifiedUnreliable = true;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_CUSTOM_THUNK_ATTRIBUTE))
	{
		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_CALLABLE_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_GETTER_ATTRIBUTE))
	{
		if (InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Function cannot be a blueprint event and a blueprint getter"));
		}

		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		InFunction->FunctionFlags |= FUNC_BlueprintPure;

		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_SETTER_ATTRIBUTE))
	{
		if (InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Function cannot be a blueprint event and a blueprint setter."));
		}

		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_PURE_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		InFunction->FunctionFlags |= FUNC_BlueprintPure;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_AUTHORITY_ONLY_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintAuthorityOnly;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_COSMETIC_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCosmetic;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_WITH_VALIDATION_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_NetValidate;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_FIELD_NOTIFY_ATTRIBUTE))
	{
	}

	if (InFunction->FunctionFlags & FUNC_Net)
	{
		InFunction->FunctionFlags |= FUNC_Event;

		ensure(!(InFunction->FunctionFlags & (FUNC_BlueprintEvent | FUNC_Exec)));

		const auto bIsNetService = !!(InFunction->FunctionFlags & (FUNC_NetRequest | FUNC_NetResponse));

		const auto bIsNetReliable = !!(InFunction->FunctionFlags & FUNC_NetReliable);

		if (InFunction->FunctionFlags & FUNC_Static)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Static functions can't be replicated"));
		}

		if (!bIsNetReliable && !bSpecifiedUnreliable && !bIsNetService)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Replicated function: 'reliable' or 'unreliable' is required"));
		}

		if (bIsNetReliable && bSpecifiedUnreliable && !bIsNetService)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("'reliable' and 'unreliable' are mutually exclusive"));
		}
	}

#if WITH_EDITOR
	SetMetaData(InFunction, InMonoCustomAttrInfo);
#endif
}

#if WITH_EDITOR
template <typename T>
static void SetFieldMetaData(T InField, const TArray<FString>& InMetaDataAttrs,
                             MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	for (const auto& MetaDataAttr : InMetaDataAttrs)
	{
		if (FDynamicGeneratorCore::AttrsHasAttr(InMonoCustomAttrInfo, MetaDataAttr))
		{
			const auto FoundMonoClass = FMonoDomain::Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), MetaDataAttr);

			const auto FoundMonoObject = FMonoDomain::Custom_Attrs_Get_Attr(InMonoCustomAttrInfo, FoundMonoClass);

			const auto FoundMonoProperty = FMonoDomain::Class_Get_Property_From_Name(FoundMonoClass, TEXT("Value"));

			const auto Value = FMonoDomain::Property_Get_Value(FoundMonoProperty, FoundMonoObject, nullptr, nullptr);

			InField->SetMetaData(*MetaDataAttr.LeftChop(9),
			                     *FString(UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(
				                     FMonoDomain::Object_To_String(Value, nullptr)))));
		}
	}
}

void FDynamicGeneratorCore::SetMetaData(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InClass, ClassMetaDataAttrs, InMonoCustomAttrInfo);
}

void FDynamicGeneratorCore::SetMetaData(UScriptStruct* InScriptStruct, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InScriptStruct, StructMetaDataAttrs, InMonoCustomAttrInfo);
}

void FDynamicGeneratorCore::SetMetaData(UEnum* InEnum, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InEnum, EnumMetaDataAttrs, InMonoCustomAttrInfo);
}

void FDynamicGeneratorCore::SetMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InProperty, PropertyMetaDataAttrs, InMonoCustomAttrInfo);
}

void FDynamicGeneratorCore::SetMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InFunction, FunctionMetaDataAttrs, InMonoCustomAttrInfo);
}

TArray<FString> FDynamicGeneratorCore::GetDynamic(const FString& InFile, const FString& InField)
{
	auto& FileManager = IFileManager::Get();

	if (!FileManager.FileExists(*InFile))
	{
		return {};
	}

	FString JsonStr;

	if (FFileHelper::LoadFileToString(JsonStr, *InFile))
	{
		TSharedPtr<FJsonObject> JsonObj;

		TArray<FString> Dynamic;

		const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

		FJsonSerializer::Deserialize(JsonReader, JsonObj);

		JsonObj->TryGetStringArrayField(InField, Dynamic);

		return Dynamic;
	}

	return {};
}
#endif

bool FDynamicGeneratorCore::AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName)
{
	if (const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), InAttributeName))
	{
		return !!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass);
	}

	return false;
}
