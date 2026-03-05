#include "Dynamic/FDynamicGeneratorCore.h"
#include "Kismet/KismetStringLibrary.h"
#include "Dynamic/FDynamicDependencyGraph.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/GenericAttributeMacro.h"
#include "CoreMacro/MetaDataAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Log/UnrealCSharpLog.h"
#include "Template/TGetArrayLength.inl"
#include "Reflection/FReflectionRegistry.h"

#if WITH_EDITOR
TMap<FString, TArray<FString>> FDynamicGeneratorCore::DynamicMap;
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
                                                  const TFunction<void(const FString&, const FString&)>& InGenerator)
{
	if (const auto Names = DynamicMap.Find(InName))
	{
		for (const auto& Name : *Names)
		{
			if (auto Index = 0; Name.FindLastChar(TEXT('.'), Index))
			{
				InGenerator(Name.Left(Index), Name.Right(Name.Len() - Index - 1));
			}
		}
	}
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

void FDynamicGeneratorCore::GeneratorField(FReflection* InReflection,
                                           const FClassReflection* InClassReflection,
                                           FDynamicDependencyGraph::FNode& OutNode)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	const auto ClassName = InClassReflection->GetName();

	switch (FTypeBridge::GetPropertyType(InClassReflection))
	{
	case EPropertyTypeExtent::SubclassOfReference:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::ObjectReference:
		{
			if (InClassReflection->HasAttribute(FReflectionRegistry::Get().GetUClassAttributeClass()))
			{
				const auto bIsSoftReference =
					!(InReflection->HasAttribute(FReflectionRegistry::Get().GetDefaultSubObjectAttributeClass()) ||
						InReflection->HasAttribute(FReflectionRegistry::Get().GetRootComponentAttributeClass()));

				OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, bIsSoftReference});
			}
		}
		break;
	case EPropertyTypeExtent::Interface:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::Enum:
		{
			if (InClassReflection->HasAttribute(FReflectionRegistry::Get().GetUEnumAttributeClass()))
			{
				OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, false});
			}
		}
		break;
	case EPropertyTypeExtent::Struct:
		{
			if (InClassReflection->HasAttribute(FReflectionRegistry::Get().GetUStructAttributeClass()))
			{
				OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, false});
			}
		}
		break;
	case EPropertyTypeExtent::WeakObjectReference:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::LazyObjectReference:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::SoftClassReference:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::SoftObjectReference:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::Map:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);

			GeneratorField(InReflection, InClassReflection->GetGenericArgument(1), OutNode);
		}
		break;
	case EPropertyTypeExtent::Set:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	case EPropertyTypeExtent::Array:
		{
			GeneratorField(InReflection, InClassReflection->GetGenericArgument(), OutNode);
		}
		break;
	default: ;
	}
}

void FDynamicGeneratorCore::GeneratorProperty(const FClassReflection* InClassReflection,
                                              FDynamicDependencyGraph::FNode& OutNode)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	for (const auto& [Name, Property] : InClassReflection->GetProperties())
	{
		if (Property->IsUProperty())
		{
			GeneratorField(Property, Property->GetReflectionType(), OutNode);
		}
	}
}

void FDynamicGeneratorCore::GeneratorFunction(const FClassReflection* InClassReflection,
                                              FDynamicDependencyGraph::FNode& OutNode)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	for (const auto& [PLACEHOLDER, Method] : InClassReflection->GetMethods())
	{
		if (Method->IsUFunction())
		{
			for (const auto Param : Method->GetParams())
			{
				GeneratorField(Param, Param->GetReflectionType(), OutNode);
			}
		}
	}
}

void FDynamicGeneratorCore::GeneratorInterface(const FClassReflection* InClassReflection,
                                               FDynamicDependencyGraph::FNode& OutNode)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	const auto AttributeClass = FReflectionRegistry::Get().GetUInterfaceAttributeClass();

	for (const auto Interface : InClassReflection->GetInterfaces())
	{
		if (Interface->HasAttribute(AttributeClass))
		{
			OutNode.Dependency(FDynamicDependencyGraph::FDependency{
				IInterfaceToUInterface(Interface)->GetName(), false
			});
		}
	}
}

void FDynamicGeneratorCore::Generator(const FClassReflection* InClassReflection,
                                      const TFunction<void(FClassReflection*)>& InGenerator)
{
	const auto AttributeReflectionType = InClassReflection->GetReflectionType();

	const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass();

	auto bIsUEAssemblyGCHandle = true;

	for (const auto& AssemblyGCHandle : FMonoDomain::GetAssemblyGCHandles())
	{
		if (bIsUEAssemblyGCHandle)
		{
			bIsUEAssemblyGCHandle = false;
		}
		else
		{
			int32 OutLength{};

			void* InParams[3] = {
				AttributeReflectionType,
				FMonoDomain::GCHandle_Get_Target_V2(AssemblyGCHandle),
				&OutLength
			};

			const auto GetTypesWithAttributeMethod = UtilsClass->GetMethod(
				FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, TGetArrayLength(InParams));

			const auto Types = reinterpret_cast<MonoArray*>(GetTypesWithAttributeMethod->Runtime_Invoke(
				nullptr, InParams));

			for (auto Index = 0; Index < OutLength; ++Index)
			{
				const auto ReflectionType = FMonoDomain::Array_Get<MonoReflectionType*>(Types, Index);

				InGenerator(FReflectionRegistry::Get().GetClass(ReflectionType));
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

void FDynamicGeneratorCore::SetFlags(FProperty* InProperty, FReflection* InReflection)
{
	if (InProperty == nullptr || InReflection == nullptr)
	{
		return;
	}

#if WITH_EDITOR
	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetEditAnywhereAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Edit);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetEditInstanceOnlyAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnTemplate);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetEditDefaultsOnlyAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnInstance);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetVisibleAnywhereAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetVisibleInstanceOnlyAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst | CPF_DisableEditOnTemplate);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintReadWriteAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintSetterAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintReadOnlyAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible | CPF_BlueprintReadOnly);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintGetterAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetConfigAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Config);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetGlobalConfigAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_GlobalConfig | CPF_Config);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetLocalizedAttributeClass()))
	{
		// @TODO
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetTransientAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Transient);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetDuplicateTransientAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_DuplicateTransient);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetTextExportTransientAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_TextExportTransient);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetNonPIETransientAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetNonPIEDuplicateTransientAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetExportAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_ExportObject);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetNoClearAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_NoClear);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetEditFixedSizeAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_EditFixedSize);
	}
#endif

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetReplicatedAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Net);

		InProperty->SetBlueprintReplicationCondition(static_cast<ELifetimeCondition>(
			UKismetStringLibrary::Conv_StringToInt(
				InReflection->GetAttributeValue(FReflectionRegistry::Get().GetReplicatedUsingAttributeClass(), 0))));
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetReplicatedUsingAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Net | CPF_RepNotify);

		InProperty->RepNotifyFunc = FName(
			InReflection->GetAttributeValue(FReflectionRegistry::Get().GetReplicatedUsingAttributeClass(), 0));

		InProperty->SetBlueprintReplicationCondition(static_cast<ELifetimeCondition>(
			UKismetStringLibrary::Conv_StringToInt(
				InReflection->GetAttributeValue(FReflectionRegistry::Get().GetReplicatedUsingAttributeClass(), 1))));
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetNotReplicatedAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_RepSkip);
	}

#if WITH_EDITOR
	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetInterpAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_Interp);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetNonTransactionalAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_NonTransactional);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetInstancedAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_PersistentInstance | CPF_ExportObject | CPF_InstancedReference);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintAssignableAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintAssignable);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintCallableAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintCallable);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintAuthorityOnlyAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintAuthorityOnly);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetAssetRegistrySearchableAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_AssetRegistrySearchable);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetSimpleDisplayAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_SimpleDisplay);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetAdvancedDisplayAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_AdvancedDisplay);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetSaveGameAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_SaveGame);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetSkipSerializationAttributeClass()))
	{
		InProperty->SetPropertyFlags(CPF_SkipSerialization);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetFieldNotifyAttributeClass()))
	{
		// @TODO
	}
#endif

#if WITH_EDITOR
	SetMetaData(InProperty, InReflection);
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

void FDynamicGeneratorCore::SetFlags(UFunction* InFunction, FReflection* InReflection)
{
	if (InFunction == nullptr || InReflection == nullptr)
	{
		return;
	}

	auto bSpecifiedUnreliable = false;

	auto FunctionExportFlags = 0u;

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintNativeEventAttributeClass()))
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

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintImplementableEventAttributeClass()))
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

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetExecAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_Exec;

		if (InFunction->FunctionFlags & FUNC_Net)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}

#if WITH_EDITOR
	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetSealedEventAttributeClass()))
	{
	}
#endif

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetServerAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetServer;

		if (InFunction->FunctionFlags & FUNC_Exec)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetClientAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetClient;
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetNetMulticastAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetMulticast;
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetServiceRequestAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetRequest;

		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetServiceResponseAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetResponse;

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetReliableAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_NetReliable;
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetUnreliableAttributeClass()))
	{
		bSpecifiedUnreliable = true;
	}

#if WITH_EDITOR
	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetCustomThunkAttributeClass()))
	{
		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintCallableAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintGetterAttributeClass()))
	{
		if (InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Function cannot be a blueprint event and a blueprint getter"));
		}

		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		InFunction->FunctionFlags |= FUNC_BlueprintPure;

		// @TODO
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintSetterAttributeClass()))
	{
		if (InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Function cannot be a blueprint event and a blueprint setter."));
		}

		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		// @TODO
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintPureAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		InFunction->FunctionFlags |= FUNC_BlueprintPure;
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintAuthorityOnlyAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintAuthorityOnly;
	}

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintPureAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCosmetic;
	}
#endif

	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetWithValidationAttributeClass()))
	{
		InFunction->FunctionFlags |= FUNC_NetValidate;
	}

#if WITH_EDITOR
	if (InReflection->HasAttribute(FReflectionRegistry::Get().GetFieldNotifyAttributeClass()))
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
	SetMetaData(InFunction, InReflection);
#endif
}

void FDynamicGeneratorCore::SetFlags(FClassReflection* InClassReflection, UClass* InClass)
{
	if (InClassReflection == nullptr || InClass == nullptr)
	{
		return;
	}

	const auto AttributeClass = InClass->HasAnyClassFlags(CLASS_Interface)
		                            ? FReflectionRegistry::Get().GetUInterfaceAttributeClass()
		                            : FReflectionRegistry::Get().GetUClassAttributeClass();

	if (InClassReflection->HasAttribute(AttributeClass))
	{
#if WITH_EDITOR
		if (InClassReflection->HasAttribute(FReflectionRegistry::Get().GetNotPlaceableAttributeClass()))
		{
			InClass->ClassFlags |= CLASS_NotPlaceable;
		}
#endif

#if WITH_EDITOR
		SetMetaData(InClass, InClassReflection);
#endif
	}
}

void FDynamicGeneratorCore::SetFlags(FClassReflection* InClassReflection, UScriptStruct* InScriptStruct)
{
	if (InClassReflection == nullptr || InScriptStruct == nullptr)
	{
		return;
	}

	if (const auto AttributeClass = FReflectionRegistry::Get().GetUStructAttributeClass();
		InClassReflection->HasAttribute(AttributeClass))
	{
#if WITH_EDITOR
		SetMetaData(InScriptStruct, InClassReflection);
#endif
	}
}

void FDynamicGeneratorCore::SetFlags(FClassReflection* InClassReflection, UEnum* InEnum)
{
	if (InClassReflection == nullptr || InEnum == nullptr)
	{
		return;
	}

	if (const auto AttributeClass = FReflectionRegistry::Get().GetUEnumAttributeClass();
		InClassReflection->HasAttribute(AttributeClass))
	{
#if WITH_EDITOR
		SetMetaData(InEnum, InClassReflection);
#endif
	}
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
static void SetFieldMetaData(T InField, const TArray<FClassReflection*>& InMetaDataAttributes,
                             FReflection* InReflection, const TFunction<void()>& InSetMetaData)
{
	for (const auto& MetaDataAttribute : InMetaDataAttributes)
	{
		if (InReflection->HasAttribute(MetaDataAttribute))
		{
			FDynamicGeneratorCore::SetMetaData(InField, MetaDataAttribute->GetName(),
			                                   InReflection->GetAttributeValue(MetaDataAttribute));
		}
	}

	InSetMetaData();
}

void FDynamicGeneratorCore::SetMetaData(FProperty* InProperty, FReflection* InReflection)
{
	SetFieldMetaData(InProperty, GetPropertyMetaDataAttributes(), InReflection, []()
	{
	});
}

void FDynamicGeneratorCore::SetMetaData(UFunction* InFunction, FReflection* InReflection)
{
	SetFieldMetaData(InFunction, GetFunctionMetaDataAttributes(), InReflection, []()
	{
	});
}

void FDynamicGeneratorCore::SetMetaData(UClass* InClass, FReflection* InReflection)
{
	SetFieldMetaData(InClass, InClass->IsChildOf(UInterface::StaticClass())
		                          ? GetInterfaceMetaDataAttributes()
		                          : GetClassMetaDataAttributes(),
	                 InReflection, [InClass, InReflection]()
	                 {
		                 if (const auto ClassGroupAttributeClass = FReflectionRegistry::Get().
			                 GetClassGroupAttributeClass())
		                 {
			                 if (InReflection->HasAttribute(ClassGroupAttributeClass))
			                 {
				                 SetMetaData(InClass, ClassGroupAttributeClass->GetName(),
				                             *InReflection->GetAttributeValue(ClassGroupAttributeClass));
			                 }
		                 }

		                 if (const auto MinimalAPIAttributeClass = FReflectionRegistry::Get().
			                 GetMinimalAPIAttributeClass())
		                 {
			                 if (InReflection->HasAttribute(MinimalAPIAttributeClass))
			                 {
				                 SetMetaData(InClass, MinimalAPIAttributeClass->GetName(),TEXT("true"));
			                 }
		                 }

		                 if (const auto BlueprintTypeAttributeClass = FReflectionRegistry::Get().
			                 GetBlueprintTypeAttributeClass())
		                 {
			                 if (InReflection->HasAttribute(BlueprintTypeAttributeClass))
			                 {
				                 SetMetaData(InClass, BlueprintTypeAttributeClass->GetName(),TEXT("true"));
			                 }
		                 }

		                 if (InReflection->HasAttribute(FReflectionRegistry::Get().GetBlueprintableAttributeClass()))
		                 {
			                 SetMetaData(InClass, CLASS_IS_BLUEPRINT_BASE_ATTRIBUTE, TEXT("true"));

			                 SetMetaData(InClass, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
		                 }
	                 });
}

void FDynamicGeneratorCore::SetMetaData(UScriptStruct* InScriptStruct, FReflection* InReflection)
{
	if (InScriptStruct == nullptr || InScriptStruct == nullptr)
	{
		return;
	}

	SetFieldMetaData(InScriptStruct, GetStructMetaDataAttributes(), InReflection, [InScriptStruct, InReflection]()
	{
		if (const auto BlueprintTypeAttributeClass = FReflectionRegistry::Get().GetBlueprintTypeAttributeClass())
		{
			if (InReflection->HasAttribute(BlueprintTypeAttributeClass))
			{
				SetMetaData(InScriptStruct, BlueprintTypeAttributeClass->GetName(), TEXT("true"));
			}
		}
	});
}

void FDynamicGeneratorCore::SetMetaData(UEnum* InEnum, FReflection* InReflection)
{
	if (InEnum == nullptr || InReflection == nullptr)
	{
		return;
	}

	SetFieldMetaData(InEnum, GetEnumMetaDataAttributes(), InReflection,
	                 [InEnum, InReflection]()
	                 {
		                 if (const auto BlueprintTypeAttributeClass = FReflectionRegistry::Get().
			                 GetBlueprintTypeAttributeClass())
		                 {
			                 if (InReflection->HasAttribute(BlueprintTypeAttributeClass))
			                 {
				                 SetMetaData(InEnum, BlueprintTypeAttributeClass->GetName(), TEXT("true"));
			                 }
		                 }
	                 });
}
#endif

void FDynamicGeneratorCore::GeneratorProperty(const FClassReflection* InClassReflection, UField* InField,
                                              const TFunction<void(FPropertyReflection*, const FProperty*)>&
                                              InGenerator)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	for (const auto& [Name, Property] : InClassReflection->GetProperties())
	{
		if (Property != nullptr)
		{
			if (Property->IsUProperty())
			{
				const auto CppProperty = FTypeBridge::Factory<true>(
					Property->GetReflectionType(), InField, FName(Name),
					EObjectFlags::RF_Public);

				SetFlags(CppProperty, Property);

				InField->AddCppProperty(CppProperty);

				InGenerator(Property, CppProperty);
			}
		}
	}
}

void FDynamicGeneratorCore::GeneratorFunction(const FClassReflection* InClassReflection, UClass* InClass,
                                              const TFunction<void(FMethodReflection*, const UFunction* InFunction)>&
                                              InGenerator)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	for (const auto& [Pair, Method] : InClassReflection->GetMethods())
	{
		if (Method->IsUFunction())
		{
			auto Function = NewObject<UFunction>(InClass, FName(Pair.Key), RF_Public | RF_Transient);

			if (Method->IsStatic())
			{
				Function->FunctionFlags |= FUNC_Static;
			}

			Function->MinAlignment = 1;

			if (const auto Return = Method->GetReturn())
			{
				if (const auto Property = FTypeBridge::Factory<true>(Return, Function, "",
				                                                     RF_Public | RF_Transient))
				{
					Property->SetPropertyFlags(CPF_Parm | CPF_OutParm | CPF_ReturnParm);

					Function->AddCppProperty(Property);

					Function->FunctionFlags |= FUNC_HasOutParms;
				}
			}

			const auto& Params = Method->GetParams();

			for (auto Index = Method->GetParamCount() - 1; Index >= 0; --Index)
			{
				const auto Property = FTypeBridge::Factory<true>(
					Params[Index]->GetReflectionType(),
					Function,
					FName(Params[Index]->GetName()),
					RF_Public | RF_Transient);

				Property->SetPropertyFlags(CPF_Parm);

				if (Params[Index]->IsRef())
				{
					Property->SetPropertyFlags(CPF_OutParm | CPF_ReferenceParm);
				}

				Function->AddCppProperty(Property);
			}

			Function->Bind();

			Function->StaticLink(true);

			Function->Next = InClass->Children;

			InClass->Children = Function;

			SetFlags(Function, Method);

			InClass->AddFunctionToFunctionMap(Function, FName(Method->GetName()));

			InGenerator(Method, Function);
		}
	}
}

FClassReflection* FDynamicGeneratorCore::UInterfaceToIInterface(const FClassReflection* InClassReflection)
{
	return FReflectionRegistry::Get().GetClass(InClassReflection->GetNameSpace(),
	                                           FString::Printf(TEXT(
		                                           "I%s"
	                                           ),
	                                                           *InClassReflection->GetName().RightChop(1)
	                                           ));
}

FClassReflection* FDynamicGeneratorCore::IInterfaceToUInterface(const FClassReflection* InClassReflection)
{
	return FReflectionRegistry::Get().GetClass(InClassReflection->GetNameSpace(),
	                                           FString::Printf(TEXT(
		                                           "U%s"
	                                           ),
	                                                           *InClassReflection->GetName().RightChop(1)
	                                           ));
}

#if WITH_EDITOR
EDynamicType FDynamicGeneratorCore::GetDynamicType(const FString& InName)
{
	if (DynamicMap.Contains(DYNAMIC_CLASS) && DynamicMap[DYNAMIC_CLASS].Contains(InName))
	{
		return EDynamicType::Class;
	}

	if (DynamicMap.Contains(DYNAMIC_STRUCT) && DynamicMap[DYNAMIC_STRUCT].Contains(InName))
	{
		return EDynamicType::Struct;
	}

	if (DynamicMap.Contains(DYNAMIC_ENUM) && DynamicMap[DYNAMIC_ENUM].Contains(InName))
	{
		return EDynamicType::Enum;
	}

	if (DynamicMap.Contains(DYNAMIC_INTERFACE) && DynamicMap[DYNAMIC_INTERFACE].Contains(InName))
	{
		return EDynamicType::Interface;
	}

	return EDynamicType::None;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetClassMetaDataAttributes()
{
	static auto& ReflectionRegistry = FReflectionRegistry::Get();

	static TArray<FClassReflection*> ClassMetaDataAttributes = {
		ReflectionRegistry.GetHideCategoriesAttributeClass(),
		ReflectionRegistry.GetToolTipAttributeClass(),
		ReflectionRegistry.GetBlueprintSpawnableComponentAttributeClass(),
		ReflectionRegistry.GetChildCanTickAttributeClass(),
		ReflectionRegistry.GetChildCannotTickAttributeClass(),
		ReflectionRegistry.GetDebugTreeLeafAttributeClass(),
		ReflectionRegistry.GetIgnoreCategoryKeywordsInSubclassesAttributeClass(),
		ReflectionRegistry.GetDeprecatedNodeAttributeClass(),
		ReflectionRegistry.GetDeprecationMessageAttributeClass(),
		ReflectionRegistry.GetDisplayNameAttributeClass(),
		ReflectionRegistry.GetScriptNameAttributeClass(),
		ReflectionRegistry.GetIsBlueprintBaseAttributeClass(),
		ReflectionRegistry.GetKismetHideOverridesAttributeClass(),
		ReflectionRegistry.GetLoadBehaviorAttributeClass(),
		ReflectionRegistry.GetProhibitedInterfacesAttributeClass(),
		ReflectionRegistry.GetRestrictedToClassesAttributeClass(),
		ReflectionRegistry.GetShowWorldContextPinAttributeClass(),
		ReflectionRegistry.GetDontUseGenericSpawnObjectAttributeClass(),
		ReflectionRegistry.GetExposedAsyncProxyAttributeClass(),
		ReflectionRegistry.GetBlueprintThreadSafeAttributeClass(),
		ReflectionRegistry.GetUsesHierarchyAttributeClass()
	};

	return ClassMetaDataAttributes;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetStructMetaDataAttributes()
{
	static auto& ReflectionRegistry = FReflectionRegistry::Get();

	static TArray<FClassReflection*> StructMetaDataAttributes = {
		ReflectionRegistry.GetToolTipAttributeClass(),
		ReflectionRegistry.GetHasNativeBreakAttributeClass(),
		ReflectionRegistry.GetHasNativeMakeAttributeClass(),
		ReflectionRegistry.GetHiddenByDefaultAttributeClass(),
		ReflectionRegistry.GetDisableSplitPinAttributeClass()
	};

	return StructMetaDataAttributes;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetEnumMetaDataAttributes()
{
	static auto& ReflectionRegistry = FReflectionRegistry::Get();

	static TArray<FClassReflection*> EnumMetaDataAttrs = {
		ReflectionRegistry.GetToolTipAttributeClass(),
		ReflectionRegistry.GetBitflagsAttributeClass(),
		ReflectionRegistry.GetUseEnumValuesAsMaskValuesInEditorAttributeClass()
	};

	return EnumMetaDataAttrs;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetInterfaceMetaDataAttributes()
{
	static auto& ReflectionRegistry = FReflectionRegistry::Get();

	static TArray<FClassReflection*> InterfaceMetaDataAttributes = {
		ReflectionRegistry.GetConversionRootAttributeClass(),
		ReflectionRegistry.GetCannotImplementInterfaceInBlueprintAttributeClass(),
		ReflectionRegistry.GetToolTipAttributeClass()
	};

	return InterfaceMetaDataAttributes;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetPropertyMetaDataAttributes()
{
	static auto& ReflectionRegistry = FReflectionRegistry::Get();

	static TArray<FClassReflection*> PropertyMetaDataAttributes = {
		ReflectionRegistry.GetToolTipAttributeClass(),
		ReflectionRegistry.GetDeprecationMessageAttributeClass(),
		ReflectionRegistry.GetDisplayNameAttributeClass(),
		ReflectionRegistry.GetScriptNameAttributeClass(),
		ReflectionRegistry.GetLoadBehaviorAttributeClass(),
		ReflectionRegistry.GetAllowAbstractAttributeClass(),
		ReflectionRegistry.GetAllowAnyActorAttributeClass(),
		ReflectionRegistry.GetAllowedClassesAttributeClass(),
		ReflectionRegistry.GetAllowPreserveRatioAttributeClass(),
		ReflectionRegistry.GetAllowPrivateAccessAttributeClass(),
		ReflectionRegistry.GetArrayClampAttributeClass(),
		ReflectionRegistry.GetAssetBundlesAttributeClass(),
		ReflectionRegistry.GetBlueprintBaseOnlyAttributeClass(),
		ReflectionRegistry.GetBlueprintCompilerGeneratedDefaultsAttributeClass(),
		ReflectionRegistry.GetClampMinAttributeClass(),
		ReflectionRegistry.GetClampMaxAttributeClass(),
		ReflectionRegistry.GetConfigHierarchyEditableAttributeClass(),
		ReflectionRegistry.GetContentDirAttributeClass(),
		ReflectionRegistry.GetDeltaAttributeClass(),
		ReflectionRegistry.GetDeprecatedPropertyAttributeClass(),
		ReflectionRegistry.GetDisallowedAssetDataTagsAttributeClass(),
		ReflectionRegistry.GetDisallowedClassesAttributeClass(),
		ReflectionRegistry.GetDisplayAfterAttributeClass(),
		ReflectionRegistry.GetDisplayPriorityAttributeClass(),
		ReflectionRegistry.GetDisplayThumbnailAttributeClass(),
		ReflectionRegistry.GetEditConditionAttributeClass(),
		ReflectionRegistry.GetEditConditionHidesAttributeClass(),
		ReflectionRegistry.GetEditFixedOrderAttributeClass(),
		ReflectionRegistry.GetCategoryAttributeClass(),
		ReflectionRegistry.GetExactClassAttributeClass(),
		ReflectionRegistry.GetExposeFunctionCategoriesAttributeClass(),
		ReflectionRegistry.GetExposeOnSpawnAttributeClass(),
		ReflectionRegistry.GetFilePathFilterAttributeClass(),
		ReflectionRegistry.GetRelativeToGameDirAttributeClass(),
		ReflectionRegistry.GetFixedIncrementAttributeClass(),
		ReflectionRegistry.GetForceShowEngineContentAttributeClass(),
		ReflectionRegistry.GetForceShowPluginContentAttributeClass(),
		ReflectionRegistry.GetHideAlphaChannelAttributeClass(),
		ReflectionRegistry.GetHideInDetailPanelAttributeClass(),
		ReflectionRegistry.GetHideViewOptionsAttributeClass(),
		ReflectionRegistry.GetIgnoreForMemberInitializationTestAttributeClass(),
		ReflectionRegistry.GetInlineEditConditionToggleAttributeClass(),
		ReflectionRegistry.GetLinearDeltaSensitivityAttributeClass(),
		ReflectionRegistry.GetLongPackageNameAttributeClass(),
		ReflectionRegistry.GetMakeEditWidgetAttributeClass(),
		ReflectionRegistry.GetMakeStructureDefaultValueAttributeClass(),
		ReflectionRegistry.GetMetaClassAttributeClass(),
		ReflectionRegistry.GetMustImplementAttributeClass(),
		ReflectionRegistry.GetMultipleAttributeClass(),
		ReflectionRegistry.GetMaxLengthAttributeClass(),
		ReflectionRegistry.GetMultiLineAttributeClass(),
		ReflectionRegistry.GetPasswordFieldAttributeClass(),
		ReflectionRegistry.GetNoElementDuplicateAttributeClass(),
		ReflectionRegistry.GetNoResetToDefaultAttributeClass(),
		ReflectionRegistry.GetNoEditInlineAttributeClass(),
		ReflectionRegistry.GetNoSpinboxAttributeClass(),
		ReflectionRegistry.GetOnlyPlaceableAttributeClass(),
		ReflectionRegistry.GetRelativePathAttributeClass(),
		ReflectionRegistry.GetRelativeToGameContentDirAttributeClass(),
		ReflectionRegistry.GetRequiredAssetDataTagsAttributeClass(),
		ReflectionRegistry.GetScriptNoExportAttributeClass(),
		ReflectionRegistry.GetShowOnlyInnerPropertiesAttributeClass(),
		ReflectionRegistry.GetShowTreeViewAttributeClass(),
		ReflectionRegistry.GetSliderExponentAttributeClass(),
		ReflectionRegistry.GetTitlePropertyAttributeClass(),
		ReflectionRegistry.GetUIMinAttributeClass(),
		ReflectionRegistry.GetUIMaxAttributeClass(),
		ReflectionRegistry.GetUnitsAttributeClass(),
		ReflectionRegistry.GetForceUnitsAttributeClass(),
		ReflectionRegistry.GetUntrackedAttributeClass(),
		ReflectionRegistry.GetDevelopmentOnlyAttributeClass(),
		ReflectionRegistry.GetNeedsLatentFixupAttributeClass(),
		ReflectionRegistry.GetLatentCallbackTargetAttributeClass(),
		ReflectionRegistry.GetGetOptionsAttributeClass(),
		ReflectionRegistry.GetPinHiddenByDefaultAttributeClass(),
		ReflectionRegistry.GetValidEnumValuesAttributeClass(),
		ReflectionRegistry.GetInvalidEnumValuesAttributeClass(),
		ReflectionRegistry.GetOverridingInputPropertyAttributeClass(),
		ReflectionRegistry.GetRequiredInputAttributeClass(),
		ReflectionRegistry.GetNeverAsPinAttributeClass(),
		ReflectionRegistry.GetPinShownByDefaultAttributeClass(),
		ReflectionRegistry.GetAlwaysAsPinAttributeClass(),
		ReflectionRegistry.GetCustomizePropertyAttributeClass()
	};

	return PropertyMetaDataAttributes;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetFunctionMetaDataAttributes()
{
	static auto& ReflectionRegistry = FReflectionRegistry::Get();

	static TArray<FClassReflection*> FunctionMetaDataAttributes = {
		ReflectionRegistry.GetCallInEditorAttributeClass(),
		ReflectionRegistry.GetToolTipAttributeClass(),
		ReflectionRegistry.GetCategoryAttributeClass(),
		ReflectionRegistry.GetVariadicAttributeClass(),
		ReflectionRegistry.GetReturnDisplayNameAttributeClass(),
		ReflectionRegistry.GetInternalUseParamAttributeClass(),
		ReflectionRegistry.GetForceAsFunctionAttributeClass(),
		ReflectionRegistry.GetIgnoreTypePromotionAttributeClass(),
		ReflectionRegistry.GetDeprecationMessageAttributeClass(),
		ReflectionRegistry.GetDisplayNameAttributeClass(),
		ReflectionRegistry.GetScriptNameAttributeClass(),
		ReflectionRegistry.GetScriptNoExportAttributeClass(),
		ReflectionRegistry.GetArrayParmAttributeClass(),
		ReflectionRegistry.GetArrayTypeDependentParamsAttributeClass(),
		ReflectionRegistry.GetAutoCreateRefTermAttributeClass(),
		ReflectionRegistry.GetHideAssetPickerAttributeClass(),
		ReflectionRegistry.GetBlueprintInternalUseOnlyAttributeClass(),
		ReflectionRegistry.GetBlueprintProtectedAttributeClass(),
		ReflectionRegistry.GetCallableWithoutWorldContextAttributeClass(),
		ReflectionRegistry.GetCommutativeAssociativeBinaryOperatorAttributeClass(),
		ReflectionRegistry.GetCompactNodeTitleAttributeClass(),
		ReflectionRegistry.GetCustomStructureParamAttributeClass(),
		ReflectionRegistry.GetDefaultToSelfAttributeClass(),
		ReflectionRegistry.GetDeprecatedFunctionAttributeClass(),
		ReflectionRegistry.GetExpandEnumAsExecsAttributeClass(),
		ReflectionRegistry.GetExpandBoolAsExecsAttributeClass(),
		ReflectionRegistry.GetScriptMethodAttributeClass(),
		ReflectionRegistry.GetScriptMethodSelfReturnAttributeClass(),
		ReflectionRegistry.GetScriptOperatorAttributeClass(),
		ReflectionRegistry.GetScriptConstantAttributeClass(),
		ReflectionRegistry.GetScriptConstantHostAttributeClass(),
		ReflectionRegistry.GetHidePinAttributeClass(),
		ReflectionRegistry.GetHideSpawnParmsAttributeClass(),
		ReflectionRegistry.GetKeywordsAttributeClass(),
		ReflectionRegistry.GetLatentAttributeClass(),
		ReflectionRegistry.GetLatentInfoAttributeClass(),
		ReflectionRegistry.GetMaterialParameterCollectionFunctionAttributeClass(),
		ReflectionRegistry.GetNativeBreakFuncAttributeClass(),
		ReflectionRegistry.GetNativeMakeFuncAttributeClass(),
		ReflectionRegistry.GetUnsafeDuringActorConstructionAttributeClass(),
		ReflectionRegistry.GetWorldContextAttributeClass(),
		ReflectionRegistry.GetBlueprintAutoCastAttributeClass(),
		ReflectionRegistry.GetNotBlueprintThreadSafeAttributeClass(),
		ReflectionRegistry.GetDeterminesOutputTypeAttributeClass(),
		ReflectionRegistry.GetDynamicOutputParamAttributeClass(),
		ReflectionRegistry.GetDataTablePinAttributeClass(),
		ReflectionRegistry.GetSetParamAttributeClass(),
		ReflectionRegistry.GetMapParamAttributeClass(),
		ReflectionRegistry.GetMapKeyParamAttributeClass(),
		ReflectionRegistry.GetMapValueParamAttributeClass(),
		ReflectionRegistry.GetBitmaskAttributeClass(),
		ReflectionRegistry.GetBitmaskEnumAttributeClass(),
		ReflectionRegistry.GetArrayParamAttributeClass()
	};

	return FunctionMetaDataAttributes;
}
#endif
