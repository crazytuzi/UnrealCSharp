#include "Mixin/FMixinGeneratorCore.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "CoreMacro/FunctionAttributeMacro.h"
#include "CoreMacro/GenericAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Log/UnrealCSharpLog.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

UPackage* FMixinGeneratorCore::GetOuter()
{
	return UObject::StaticClass()->GetPackage();
}

FString FMixinGeneratorCore::GetClassNameSpace()
{
	return FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass());
}

void FMixinGeneratorCore::SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_INLINE_ATTRIBUTE))
	{
		// @TODO
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REP_RETRY_ATTRIBUTE))
	{
		// @TODO
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SETTER_ATTRIBUTE))
	{
		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_GETTER_ATTRIBUTE))
	{
		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_FIELD_NOTIFY_ATTRIBUTE))
	{
		// @TODO
	}
}

enum class EMixinFunctionExportFlags
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

void FMixinGeneratorCore::SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
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

		FunctionExportFlags |= static_cast<uint32>(EMixinFunctionExportFlags::FUNCEXPORT_CustomThunk);

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
		FunctionExportFlags |= static_cast<uint32>(EMixinFunctionExportFlags::FUNCEXPORT_CustomThunk);
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
}

#if WITH_EDITOR
TArray<FString> FMixinGeneratorCore::GetMixin(const FString& InFile, const FString& InField)
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

		TArray<FString> Mixin;

		const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

		FJsonSerializer::Deserialize(JsonReader, JsonObj);

		JsonObj->TryGetStringArrayField(InField, Mixin);

		return Mixin;
	}

	return {};
}
#endif

bool FMixinGeneratorCore::AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName)
{
	if (const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), InAttributeName))
	{
		return !!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass);
	}

	return false;
}
