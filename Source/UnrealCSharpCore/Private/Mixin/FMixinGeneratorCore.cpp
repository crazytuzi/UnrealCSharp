#include "Mixin/FMixinGeneratorCore.h"

#include <Windows.UI.Input.h>

#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

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
	
	bool bHasSetterTag = false;
	bool bHasGetterTag = false;
	bool bFieldNotify = false;

	
//TODO:Flag Conflict
//TODO:For Const class ,should set all member property to BlueprintReadOnly
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
		InProperty->SetPropertyFlags( CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_SETTER_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags( CPF_BlueprintVisible); 
	}
	
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_READ_ONLY_ATTRIBUTE))
	{
		
		InProperty->SetPropertyFlags( CPF_BlueprintVisible | CPF_BlueprintReadOnly);
		//ImpliedFlags &= ~CPF_BlueprintReadOnly;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_GETTER_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags( CPF_BlueprintVisible);
	}
	
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_CONFIG_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags( CPF_Config);
	}
	
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_GLOBAL_CONFIG_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_GlobalConfig | CPF_Config);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_LOCALIZED_ATTRIBUTE))
	{
		//Be deprecated,TODO:Remove
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
		InProperty->SetPropertyFlags( CPF_TextExportTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NON_PIE_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NON_PIE_DUPLICATE_TRANSIENT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags( CPF_NonPIEDuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EXPORT_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_ExportObject);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_INLINE_ATTRIBUTE))
	{
		//Be deprecated,TODO:Remove
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
	//TODO
		// InProperty->Owner.GetOwnerClass()->SetFlags(RF_Public | RF_MarkAsNative | RF_Transient);
		// InProperty->SetPropertyFlags(CPF_Net | CPF_RepNotify | CPF_NativeAccessSpecifierPublic);
		// const auto MyProperty = new FStructProperty(InProperty->Owner.GetOwnerClass(), PropertyName, RF_Public | RF_MarkAsNative | RF_Transient,InClass->PropertiesSize
		// 	,CPF_Net | CPF_RepNotify | CPF_NativeAccessSpecifierPublic,PropertyStruct);
		//
		// UE_LOG(LogTemp, Log, TEXT("Replicated Property %s"), PropertyName);
		// InProperty->PropertyFlags|=CPF_Transient;
		// InProperty->PropertyLinkNext=InClass->PropertyLink;
		//InClass->PropertyLink=InProperty;
		
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REPLICATED_USING_ATTRIBUTE))
	{
		//TODO
	}
	
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NOT_REPLICATED_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_RepSkip);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_REP_RETRY_ATTRIBUTE))
	{
		//Be deprecated,TODO:Remove
	}
	
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_INTERP_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit);
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
		InProperty->SetPropertyFlags( CPF_Interp);
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
		//3519
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_GETTER_ATTRIBUTE))
	{
		//3534
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_FIELD_NOTIFY_ATTRIBUTE))
	{
		//3548
	}
	
}

enum EFunctionExportFlags
{
	FUNCEXPORT_Final			=0x00000001,	// function declaration included "final" keyword.  Used to differentiate between functions that have FUNC_Final only because they're private
	//							=0x00000002,
	//							=0x00000004,
	FUNCEXPORT_RequiredAPI		=0x00000008,	// Function should be exported as a public API function
	FUNCEXPORT_Inline			=0x00000010,	// export as an inline static C++ function
	FUNCEXPORT_CppStatic		=0x00000020,	// Export as a real C++ static function, causing thunks to call via ClassName::FuncName instead of this->FuncName
	FUNCEXPORT_CustomThunk		=0x00000040,	// Export no thunk function; the user will manually define a custom one
	//							=0x00000080,
	//							=0x00000100,
};

void FMixinGeneratorCore::SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InFunction == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}
	bool bSawPropertyAccessor = false;
	bool bSealedEvent= false;
	bool bSpecifiedUnreliable= false;
	bool bFieldNotify = false;

	uint32		FunctionExportFlags = 0;
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_NATIVE_EVENT_ATTRIBUTE))
	{
		if(InFunction->FunctionFlags & FUNC_Net)
		{
			//TODO Ouput Complie Error
			UE_LOG(LogTemp, Error, TEXT("BlueprintNativeEvent functions cannot be replicated!"));
		}
		else if((InFunction->FunctionFlags & FUNC_BlueprintEvent)&&!(InFunction->FunctionFlags & FUNC_Native))
		{
			UE_LOG(LogTemp, Error, TEXT("A function cannot be both BlueprintNativeEvent and BlueprintImplementableEvent!"));
		}
		else if(InFunction->FunctionFlags & FUNC_Private)
		{
			UE_LOG(LogTemp, Error, TEXT("A Private function cannot be a BlueprintNativeEvent!"));
		}
		//TODO A function cannot be both BlueprintNativeEvent and a Blueprint Property accessor 需要一次输入一个函数的所有Specifiers进行判断
		InFunction->FunctionFlags |= FUNC_Event;
		InFunction->FunctionFlags |= FUNC_BlueprintEvent;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_IMPLEMENTABLE_EVENT_ATTRIBUTE))
	{
		if(InFunction->FunctionFlags & FUNC_Net)
		{
			//TODO Ouput Complie Error
			UE_LOG(LogTemp, Error, TEXT("BlueprintImplementableEvent functions cannot be replicated!"));
		}
		else if((InFunction->FunctionFlags & FUNC_BlueprintEvent)&&!(InFunction->FunctionFlags & FUNC_Native))
		{
			UE_LOG(LogTemp, Error, TEXT("A function cannot be both BlueprintNativeEvent and BlueprintImplementableEvent!"));
		}
		else if(InFunction->FunctionFlags & FUNC_Private)
		{
			UE_LOG(LogTemp, Error, TEXT("A Private function cannot be a BlueprintImplementableEvent!"));
		}
		InFunction->FunctionFlags |= FUNC_Event;
		InFunction->FunctionFlags |= FUNC_BlueprintEvent;
		InFunction->FunctionFlags &= ~FUNC_Native;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EXEC_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_Exec;
		if(InFunction->FunctionFlags & FUNC_Net)
		{
			//TODO Ouput Complie Error
			UE_LOG(LogTemp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SEALED_EVENT_ATTRIBUTE))
	{
		bSealedEvent= true;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVER_ATTRIBUTE))
	{
		if((InFunction->FunctionFlags & FUNC_BlueprintEvent)!=0)
		{
			UE_LOG(LogTemp, Error, TEXT("BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as Client or Server"));
		}
		InFunction->FunctionFlags |= FUNC_Net;
		InFunction->FunctionFlags |= FUNC_NetServer;
		if(InFunction->FunctionFlags & FUNC_Exec)
		{
			UE_LOG(LogTemp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_CLIENT_ATTRIBUTE))
	{
		if((InFunction->FunctionFlags & FUNC_BlueprintEvent)!=0)
		{
			UE_LOG(LogTemp, Error, TEXT("BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as Client or Server"));
		}
		InFunction->FunctionFlags |= FUNC_Net;
		InFunction->FunctionFlags |= FUNC_NetClient;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_NET_MULTICAST_ATTRIBUTE))
	{
		if((InFunction->FunctionFlags & FUNC_BlueprintEvent)!=0)
		{
			UE_LOG(LogTemp, Error, TEXT("BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as Client or Server"));
		}
		InFunction->FunctionFlags |= FUNC_Net;
		InFunction->FunctionFlags |= FUNC_NetMulticast;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVICE_REQUEST_ATTRIBUTE))
	{
		if((InFunction->FunctionFlags & FUNC_BlueprintEvent)!=0)
		{
			UE_LOG(LogTemp, Error, TEXT("BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as a ServiceRequest"));
		}
		InFunction->FunctionFlags |= FUNC_Net;
		InFunction->FunctionFlags |= FUNC_NetReliable;
		InFunction->FunctionFlags |= FUNC_NetRequest;
		FunctionExportFlags |= FUNCEXPORT_CustomThunk;
		//TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values);
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_SERVICE_RESPONSE_ATTRIBUTE))
	{
		if(InFunction->FunctionFlags & FUNC_BlueprintEvent)
		{
			UE_LOG(LogTemp, Error, TEXT("BlueprintImplementableEvent or BlueprintNativeEvent functions cannot be declared as a ServiceResponse"));
		}
		InFunction->FunctionFlags |= FUNC_Net;
		InFunction->FunctionFlags |= FUNC_NetReliable;
		InFunction->FunctionFlags |= FUNC_NetResponse;
		//TODO 	ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values);
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
		FunctionExportFlags |= FUNCEXPORT_CustomThunk;
	}
	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_CALLABLE_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_GETTER_ATTRIBUTE))
	{
		if(InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogTemp, Error, TEXT("Function cannot be a blueprint event and a blueprint getter"));
		}	
		bSawPropertyAccessor = true;
		InFunction->FunctionFlags |=FUNC_BlueprintCallable;
		InFunction->FunctionFlags |= FUNC_BlueprintPure;
		//TODO MetaData.Add(NAME_BlueprintGetter);
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_SETTER_ATTRIBUTE))
	{
		if(InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogTemp, Error, TEXT("Function cannot be a blueprint event and a blueprint setter."));
		}
		bSawPropertyAccessor = true;
		InFunction->FunctionFlags |=FUNC_BlueprintCallable;
		//TODO MetaData.Add(NAME_BlueprintSetter);
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_PURE_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;
		InFunction->FunctionFlags |= FUNC_BlueprintPure;
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_AUTHORITY_ONLY_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintAuthorityOnly;
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_COSMETIC_ATTRIBUTE))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCosmetic;
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_WITH_VALIDATION_ATTRIBUTE))
	{
		InFunction->FunctionFlags |=FUNC_NetValidate;
	}
	if(AttrsHasAttr(InMonoCustomAttrInfo, CLASS_FIELD_NOTIFY_ATTRIBUTE))
	{
		bFieldNotify = true;
	}
	if(InFunction->FunctionFlags & FUNC_Net)
	{
		InFunction->FunctionFlags |=FUNC_Event;
		ensure(!(InFunction->FunctionFlags & (FUNC_BlueprintEvent | FUNC_Exec)));
		bool bIsNetService  = !!(InFunction->FunctionFlags & (FUNC_NetRequest | FUNC_NetResponse));
		bool bIsNetReliable = !!(InFunction->FunctionFlags & FUNC_NetReliable);
		if (InFunction->FunctionFlags & FUNC_Static)
		{
			UE_LOG(LogTemp, Error, TEXT("Static functions can't be replicated"));
		}

		if (!bIsNetReliable && !bSpecifiedUnreliable && !bIsNetService)
		{
			UE_LOG(LogTemp, Error, TEXT("Replicated function: 'reliable' or 'unreliable' is required"));
		}

		if (bIsNetReliable && bSpecifiedUnreliable && !bIsNetService)
		{
			UE_LOG(LogTemp, Error, TEXT("'reliable' and 'unreliable' are mutually exclusive"));
		}
	}
}

bool FMixinGeneratorCore:: AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName)
{
	if (const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), InAttributeName))
	{
		return !!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass);
	}

	return false;
}
