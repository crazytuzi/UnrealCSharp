#include "Dynamic/FDynamicGeneratorCore.h"
#include "Dynamic/FDynamicDependencyGraph.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassAttributeMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "CoreMacro/FunctionAttributeMacro.h"
#include "CoreMacro/GenericAttributeMacro.h"
#include "CoreMacro/MetaDataAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Log/UnrealCSharpLog.h"
#include "Template/TGetArrayLength.inl"
#include "mono/metadata/object.h"

#if WITH_EDITOR
TMap<FString, TArray<FString>> FDynamicGeneratorCore::DynamicMap;

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

TArray<FString> FDynamicGeneratorCore::InterfaceMetaDataAttrs =
{
	CLASS_CONVERSION_ROOT_ATTRIBUTE,
	CLASS_CANNOT_IMPLEMENT_INTERFACE_IN_BLUEPRINT_ATTRIBUTE
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
	CLASS_CATEGORY_ATTRIBUTE,
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
	CLASS_CATEGORY_ATTRIBUTE,
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
#endif

#if WITH_EDITOR
void FDynamicGeneratorCore::BeginCodeAnalysisGenerator()
{
	DynamicMap = FUnrealCSharpFunctionLibrary::LoadFileToArray(FString::Printf(TEXT(
		"%s/%s.json"
	),
	                                                                           *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
	                                                                           *DYNAMIC
	));
}

void FDynamicGeneratorCore::EndCodeAnalysisGenerator()
{
	DynamicMap.Empty();
}

void FDynamicGeneratorCore::CodeAnalysisGenerator(const FString& InName,
                                                  const TFunction<void(const FString&)>& InGenerator)
{
	if (const auto Names = DynamicMap.Find(InName))
	{
		for (const auto& Name : *Names)
		{
			InGenerator(Name);
		}
	}
}

bool FDynamicGeneratorCore::IsDynamic(MonoClass* InMonoClass, const FString& InAttribute)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), InAttribute);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

const FString& FDynamicGeneratorCore::DynamicReInstanceBaseName()
{
	static FString DynamicReInstance = TEXT("DYNAMIC_REINSTANCE");

	return DynamicReInstance;
}
#endif

void FDynamicGeneratorCore::AddNode(const FDynamicDependencyGraph::FNode& InNode)
{
	FDynamicDependencyGraph::Get().AddNode(InNode);
}

bool FDynamicGeneratorCore::IsCompleted(const FString& InName)
{
	return FDynamicDependencyGraph::Get().IsCompleted(InName);
}

void FDynamicGeneratorCore::Completed(const FString& InName)
{
	FDynamicDependencyGraph::Get().Completed(InName);
}

void FDynamicGeneratorCore::OnCompleted(const FString& InName, const TFunction<void()>& InOnCompleted)
{
	FDynamicDependencyGraph::Get().OnCompleted(InName, InOnCompleted);
}

void FDynamicGeneratorCore::Generator()
{
	FDynamicDependencyGraph::Get().Generator();
}

void FDynamicGeneratorCore::GeneratorField(MonoReflectionType* InMonoReflectionType,
                                           FDynamicDependencyGraph::FNode& OutNode)
{
	const auto InMonoType = FMonoDomain::Reflection_Type_Get_Type(
		FTypeBridge::GetType(InMonoReflectionType));

	const auto InMonoClass = FMonoDomain::Type_Get_Class(InMonoType);

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SUB_CLASS_OF))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()),
		FUnrealCSharpFunctionLibrary::GetFullClass(UObject::StaticClass())))
	{
		if (InMonoClass == FoundMonoClass ||
			FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			if (ClassHasAttr(InMonoClass, CLASS_U_CLASS_ATTRIBUTE))
			{
				OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, true});
			}

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SCRIPT_INTERFACE))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FMonoDomain::Get_Enum_Class(), false))
	{
		if (ClassHasAttr(InMonoClass, CLASS_U_ENUM_ATTRIBUTE))
		{
			OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, false});
		}

		return;
	}

	if (FMonoDomain::Class_Get_Method_From_Name(
		InMonoClass, FUNCTION_STATIC_STRUCT, 0))
	{
		if (ClassHasAttr(InMonoClass, CLASS_U_STRUCT_ATTRIBUTE))
		{
			OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, false});
		}

		return;
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_WEAK_OBJECT_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_LAZY_OBJECT_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_CLASS_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_OBJECT_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_MAP))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType, 1), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SET))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_ARRAY))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);
		}
	}
}

void FDynamicGeneratorCore::GeneratorProperty(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_PROPERTY_ATTRIBUTE);

	void* Iterator = nullptr;

	while (const auto Property = FMonoDomain::Class_Get_Properties(InMonoClass, &Iterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Property(InMonoClass, Property))
		{
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto PropertyType = FMonoDomain::Property_Get_Type(Property);

				const auto ReflectionType = FMonoDomain::Type_Get_Object(PropertyType);

				GeneratorField(ReflectionType, OutNode);
			}
		}
	}
}

void FDynamicGeneratorCore::GeneratorFunction(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_FUNCTION_ATTRIBUTE);

	void* MethodIterator = nullptr;

	while (const auto Method = FMonoDomain::Class_Get_Methods(InMonoClass, &MethodIterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Method(Method))
		{
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto Signature = FMonoDomain::Method_Signature(Method);

				void* ParamIterator = nullptr;

				while (const auto Param = FMonoDomain::Signature_Get_Params(Signature, &ParamIterator))
				{
					const auto ReflectionType = FMonoDomain::Type_Get_Object(Param);

					GeneratorField(ReflectionType, OutNode);
				}
			}
		}
	}
}

bool FDynamicGeneratorCore::ClassHasAttr(MonoClass* InMonoClass, const FString& InAttributeName)
{
	return AttrsHasAttr(FMonoDomain::Custom_Attrs_From_Class(InMonoClass), InAttributeName);
}

void FDynamicGeneratorCore::Generator(const FString& InAttribute, const TFunction<void(MonoClass*)>& InGenerator)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), InAttribute);

	const auto AttributeMonoType = FMonoDomain::Class_Get_Type(AttributeMonoClass);

	const auto AttributeMonoReflectionType = FMonoDomain::Type_Get_Object(AttributeMonoType);

	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

	auto bIsUEAssemblyGCHandle = true;

	for (const auto& AssemblyGCHandle : FMonoDomain::AssemblyGCHandles)
	{
		if (bIsUEAssemblyGCHandle)
		{
			bIsUEAssemblyGCHandle = false;
		}
		else
		{
			void* InParams[2] = {
				AttributeMonoReflectionType,
				FMonoDomain::GCHandle_Get_Target_V2(AssemblyGCHandle)
			};

			const auto GetTypesWithAttributeMethod = FMonoDomain::Class_Get_Method_From_Name(
				UtilsMonoClass, FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, TGetArrayLength(InParams));

			const auto Types = reinterpret_cast<MonoArray*>(FMonoDomain::Runtime_Invoke(
				GetTypesWithAttributeMethod, nullptr, InParams));

			const auto Length = FMonoDomain::Array_Length(Types);

			for (auto Index = 0; Index < Length; ++Index)
			{
				const auto ReflectionType = ARRAY_GET(Types, MonoReflectionType*, Index);

				const auto Type = FMonoDomain::Reflection_Type_Get_Type(ReflectionType);

				const auto Class = FMonoDomain::Type_Get_Class(Type);

				InGenerator(Class);
			}
		}
	}
}

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

#if WITH_EDITOR
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
#endif

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Net);

		if (const auto FoundMonoObject = AttrsGetAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_ATTRIBUTE))
		{
			if (const auto FoundProperty = FMonoDomain::Class_Get_Property_From_Name(
				FMonoDomain::Object_Get_Class(FoundMonoObject), PROPERTY_LIFETIME_CONDITION))
			{
				InProperty->SetBlueprintReplicationCondition(
					static_cast<ELifetimeCondition>(*static_cast<uint8*>(FMonoDomain::Object_Unbox(
						FMonoDomain::Property_Get_Value(FoundProperty, FoundMonoObject, nullptr, nullptr)))));
			}
		}
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_USING_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Net | CPF_RepNotify);

		if (const auto FoundMonoObject = AttrsGetAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_USING_ATTRIBUTE))
		{
			if (const auto FoundProperty = FMonoDomain::Class_Get_Property_From_Name(
				FMonoDomain::Object_Get_Class(FoundMonoObject), PROPERTY_LIFETIME_CONDITION))
			{
				InProperty->SetBlueprintReplicationCondition(
					static_cast<ELifetimeCondition>(*static_cast<uint8*>(FMonoDomain::Object_Unbox(
						FMonoDomain::Property_Get_Value(FoundProperty, FoundMonoObject, nullptr, nullptr)))));
			}

			if (const auto FoundProperty = FMonoDomain::Class_Get_Property_From_Name(
				FMonoDomain::Object_Get_Class(FoundMonoObject), PROPERTY_REP_CALLBACK_NAME))
			{
				InProperty->RepNotifyFunc = FName(UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(
					(MonoString*)FMonoDomain::Property_Get_Value(FoundProperty, FoundMonoObject, nullptr, nullptr))));
			}
		}
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NOT_REPLICATED_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_RepSkip);
	}

#if WITH_EDITOR
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
#endif

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

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SEALED_EVENT_ATTRIBUTE))
	{
	}
#endif

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVER_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetServer;

		if (InFunction->FunctionFlags & FUNC_Exec)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_CLIENT_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetClient;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NET_MULTICAST_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetMulticast;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVICE_REQUEST_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetRequest;

		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVICE_RESPONSE_ATTRIBUTE))
	{
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

#if WITH_EDITOR
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
#endif

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_WITH_VALIDATION_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_NetValidate;
	}

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_FIELD_NOTIFY_ATTRIBUTE))
	{
	}
#endif

	if (InFunction->FunctionFlags & FUNC_Net)
	{
		InFunction->FunctionFlags |= FUNC_Event;

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
void FDynamicGeneratorCore::SetMetaData(FField* InField, const FString& InAttribute, const FString& InValue)
{
	InField->SetMetaData(*InAttribute.LeftChop(9), *InValue);
}

void FDynamicGeneratorCore::SetMetaData(UField* InField, const FString& InAttribute, const FString& InValue)
{
	InField->SetMetaData(*InAttribute.LeftChop(9), *InValue);
}

template <typename T>
static void SetFieldMetaData(T InField, const TArray<FString>& InMetaDataAttrs,
                             MonoCustomAttrInfo* InMonoCustomAttrInfo, const TFunction<void()>& InSetMetaData)
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

			FDynamicGeneratorCore::SetMetaData(InField, MetaDataAttr,
			                                   FString(UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(
				                                   FMonoDomain::Object_To_String(Value,nullptr)))));
		}
	}

	InSetMetaData();
}

void FDynamicGeneratorCore::SetMetaData(MonoClass* InMonoClass, const FString& InAttribute,
                                        const TFunction<void(MonoCustomAttrInfo*)>& InSetMetaData)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), InAttribute);

	if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass))
	{
		if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
		{
			InSetMetaData(Attrs);
		}
	}
}

void FDynamicGeneratorCore::SetMetaData(MonoClass* InMonoClass, UClass* InClass, const FString& InAttribute)
{
	if (InMonoClass == nullptr || InClass == nullptr)
	{
		return;
	}

	SetMetaData(InMonoClass, InAttribute,
	            [InClass](MonoCustomAttrInfo* InMonoCustomAttrInfo)
	            {
		            SetFieldMetaData(InClass,
		                             InClass->IsChildOf(UInterface::StaticClass())
			                             ? InterfaceMetaDataAttrs
			                             : ClassMetaDataAttrs,
		                             InMonoCustomAttrInfo, [InClass, InMonoCustomAttrInfo]()
		                             {
			                             if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_MINIMAL_API_ATTRIBUTE))
			                             {
				                             SetMetaData(InClass, CLASS_MINIMAL_API_ATTRIBUTE, TEXT("true"));
			                             }

			                             if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_TYPE_ATTRIBUTE))
			                             {
				                             SetMetaData(InClass, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
			                             }

			                             if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINTABLE_ATTRIBUTE))
			                             {
				                             SetMetaData(InClass, CLASS_IS_BLUEPRINT_BASE_ATTRIBUTE, TEXT("true"));

				                             SetMetaData(InClass, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
			                             }
		                             });
	            });
}

void FDynamicGeneratorCore::SetMetaData(MonoClass* InMonoClass, UScriptStruct* InScriptStruct,
                                        const FString& InAttribute)
{
	if (InMonoClass == nullptr || InScriptStruct == nullptr)
	{
		return;
	}

	SetMetaData(InMonoClass, InAttribute,
	            [InScriptStruct](MonoCustomAttrInfo* InMonoCustomAttrInfo)
	            {
		            SetFieldMetaData(InScriptStruct, StructMetaDataAttrs, InMonoCustomAttrInfo,
		                             [InScriptStruct, InMonoCustomAttrInfo]()
		                             {
			                             if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_TYPE_ATTRIBUTE))
			                             {
				                             SetMetaData(InScriptStruct, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
			                             }
		                             });
	            });
}

void FDynamicGeneratorCore::SetMetaData(MonoClass* InMonoClass, UEnum* InEnum, const FString& InAttribute)
{
	if (InMonoClass == nullptr || InEnum == nullptr)
	{
		return;
	}

	SetMetaData(InMonoClass, InAttribute,
	            [InEnum](MonoCustomAttrInfo* InMonoCustomAttrInfo)
	            {
		            SetFieldMetaData(InEnum, EnumMetaDataAttrs, InMonoCustomAttrInfo,
		                             [InEnum, InMonoCustomAttrInfo]()
		                             {
			                             if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_TYPE_ATTRIBUTE))
			                             {
				                             SetMetaData(InEnum, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
			                             }
		                             });
	            });
}

void FDynamicGeneratorCore::SetMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InProperty, PropertyMetaDataAttrs, InMonoCustomAttrInfo, []()
	{
	});
}

void FDynamicGeneratorCore::SetMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InFunction, FunctionMetaDataAttrs, InMonoCustomAttrInfo, []()
	{
	});
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

MonoObject* FDynamicGeneratorCore::AttrsGetAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo,
                                                const FString& InAttributeName)
{
	if (const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), InAttributeName))
	{
		return FMonoDomain::Custom_Attrs_Get_Attr(InMonoCustomAttrInfo, AttributeMonoClass);
	}

	return nullptr;
}

void FDynamicGeneratorCore::GeneratorProperty(MonoClass* InMonoClass, UField* InField,
                                              const TFunction<void(const FProperty* InProperty)>& InGenerator)
{
	if (InMonoClass == nullptr || InField == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_PROPERTY_ATTRIBUTE);

	void* Iterator = nullptr;

	while (const auto Property = FMonoDomain::Class_Get_Properties(InMonoClass, &Iterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Property(InMonoClass, Property))
		{
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto PropertyName = FMonoDomain::Property_Get_Name(Property);

				const auto PropertyType = FMonoDomain::Property_Get_Type(Property);

				const auto ReflectionType = FMonoDomain::Type_Get_Object(PropertyType);

				const auto CppProperty = FTypeBridge::Factory<true>(ReflectionType, InField, PropertyName,
				                                                    EObjectFlags::RF_Public);

				SetPropertyFlags(CppProperty, Attrs);

				InField->AddCppProperty(CppProperty);

				InGenerator(CppProperty);
			}
		}
	}
}

void FDynamicGeneratorCore::GeneratorFunction(MonoClass* InMonoClass, UClass* InClass,
                                              const TFunction<void(const UFunction* InFunction)>& InGenerator)
{
	struct FParamDescriptor
	{
		MonoReflectionType* ReflectionType;

		FName Name;

		bool bIsRef;
	};

	if (InMonoClass == nullptr || InClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_FUNCTION_ATTRIBUTE);

	void* MethodIterator = nullptr;

	while (const auto Method = FMonoDomain::Class_Get_Methods(InMonoClass, &MethodIterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Method(Method))
		{
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto MethodName = FMonoDomain::Method_Get_Name(Method);

				const auto Signature = FMonoDomain::Method_Signature(Method);

				void* ParamIterator = nullptr;

				const auto ParamCount = FMonoDomain::Signature_Get_Param_Count(Signature);

				const auto ParamNames = static_cast<const char**>(FMemory_Alloca(ParamCount * sizeof(const char*)));

				FMonoDomain::Method_Get_Param_Names(Method, ParamNames);

				auto ParamIndex = 0;

				TArray<FParamDescriptor> ParamDescriptors;

				while (const auto Param = FMonoDomain::Signature_Get_Params(Signature, &ParamIterator))
				{
					ParamDescriptors.Add({
						FMonoDomain::Type_Get_Object(Param),
						ParamNames[ParamIndex++],
						!!FMonoDomain::Type_Is_ByRef(Param)
					});
				}

				auto Function = NewObject<UFunction>(InClass, MethodName, RF_Public | RF_Transient);

				if (!!!FMonoDomain::Signature_Is_Instance(Signature))
				{
					Function->FunctionFlags |= FUNC_Static;
				}

				Function->MinAlignment = 1;

				if (const auto ReturnParamType = FMonoDomain::Signature_Get_Return_Type(Signature))
				{
					const auto ReturnParamReflectionType = FMonoDomain::Type_Get_Object(ReturnParamType);

					if (const auto Property = FTypeBridge::Factory<true>(ReturnParamReflectionType, Function, "",
					                                                     RF_Public | RF_Transient))
					{
						Property->SetPropertyFlags(CPF_Parm | CPF_OutParm | CPF_ReturnParm);

						Function->AddCppProperty(Property);

						Function->FunctionFlags |= FUNC_HasOutParms;
					}
				}

				for (auto Index = ParamDescriptors.Num() - 1; Index >= 0; --Index)
				{
					const auto Property = FTypeBridge::Factory<true>(ParamDescriptors[Index].ReflectionType,
					                                                 Function,
					                                                 ParamDescriptors[Index].Name,
					                                                 RF_Public | RF_Transient);

					Property->SetPropertyFlags(CPF_Parm);

					if (ParamDescriptors[Index].bIsRef)
					{
						Property->SetPropertyFlags(CPF_OutParm | CPF_ReferenceParm);
					}

					Function->AddCppProperty(Property);
				}

				Function->Bind();

				Function->StaticLink(true);

				Function->Next = InClass->Children;

				InClass->Children = Function;

				SetFunctionFlags(Function, Attrs);

				InClass->AddFunctionToFunctionMap(Function, MethodName);

				InGenerator(Function);
			}
		}
	}
}
