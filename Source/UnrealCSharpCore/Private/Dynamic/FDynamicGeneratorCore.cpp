#include "Dynamic/FDynamicGeneratorCore.h"
#include "Dynamic/FDynamicDependencyGraph.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/Macro.h"
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

void FDynamicGeneratorCore::GeneratorField(MonoReflectionType* InMonoReflectionType,
                                           FDynamicDependencyGraph::FNode& OutNode)
{
	GeneratorField(nullptr, InMonoReflectionType, OutNode);
}

void FDynamicGeneratorCore::GeneratorField(MonoCustomAttrInfo* InMonoCustomAttrInfo,
                                           MonoReflectionType* InMonoReflectionType,
                                           FDynamicDependencyGraph::FNode& OutNode)
{
	const auto InMonoType = FMonoDomain::Reflection_Type_Get_Type(
		FTypeBridge::GetType(InMonoReflectionType));

	const auto InMonoClass = FMonoDomain::Type_Get_Class(InMonoType);

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSubclassOf_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_UObject_Class())
	{
		if (InMonoClass == FoundMonoClass ||
			FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			if (ClassHasAttr(InMonoClass, CLASS_U_CLASS_ATTRIBUTE))
			{
				const auto bIsSoftReference =
					!(AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetDefaultSubObjectAttribute_Class()) ||
						AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetRootComponentAttribute_Class()));

				OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, bIsSoftReference});
			}

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TScriptInterface_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FReflectionRegistry::Get().Get_Enum_Class(), false))
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

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TWeakObjectPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TLazyObjectPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSoftClassPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSoftObjectPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TMap_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType, 1), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSet_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);

			return;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().GetTArray_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			GeneratorField(InMonoCustomAttrInfo, FTypeBridge::GetGenericArgument(InMonoReflectionType), OutNode);
		}
	}
}

void FDynamicGeneratorCore::GeneratorProperty(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUPropertyAttribute_Class();

	void* Iterator = nullptr;

	while (const auto Property = FMonoDomain::Class_Get_Properties(InMonoClass, &Iterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Property(InMonoClass, Property))
		{
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto PropertyType = FMonoDomain::Property_Get_Type(Property);

				const auto ReflectionType = FMonoDomain::Type_Get_Object(PropertyType);

				GeneratorField(Attrs, ReflectionType, OutNode);
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

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUFunctionAttribute_Class();

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

void FDynamicGeneratorCore::GeneratorInterface(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUInterfaceAttribute_Class();

	void* Iterator = nullptr;

	while (const auto Interface = FMonoDomain::Class_Get_Interfaces(InMonoClass, &Iterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(Interface))
		{
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto ClassName = FString(FMonoDomain::Class_Get_Name(IInterfaceToUInterface(Interface)));

				OutNode.Dependency(FDynamicDependencyGraph::FDependency{ClassName, false});
			}
		}
	}
}

bool FDynamicGeneratorCore::ClassHasAttr(MonoClass* InMonoClass, const FString& InAttributeName)
{
	return AttrsHasAttr(FMonoDomain::Custom_Attrs_From_Class(InMonoClass), InAttributeName);
}

void FDynamicGeneratorCore::Generator(MonoClass* InAttributeMonoClass, const TFunction<void(MonoClass*)>& InGenerator)
{
	const auto AttributeMonoType = FMonoDomain::Class_Get_Type(InAttributeMonoClass);

	const auto AttributeMonoReflectionType = FMonoDomain::Type_Get_Object(AttributeMonoType);

	const auto UtilsMonoClass = FReflectionRegistry::Get().Get_Utils_Class();

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

			const auto GetTypesWithAttributeMethod = UtilsMonoClass->Get_Method_From_Name(
				FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, TGetArrayLength(InParams));

			const auto Types = reinterpret_cast<MonoArray*>(FMonoDomain::Runtime_Invoke(
				GetTypesWithAttributeMethod->GetMethod(), nullptr, InParams));

			const auto Length = FMonoDomain::Array_Length(Types);

			for (auto Index = 0; Index < Length; ++Index)
			{
				const auto ReflectionType = FMonoDomain::Array_Get<MonoReflectionType*>(Types, Index);

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

void FDynamicGeneratorCore::SetFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InProperty == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetEditAnywhereAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Edit);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetEditInstanceOnlyAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnTemplate);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetEditDefaultsOnlyAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnInstance);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetVisibleAnywhereAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetVisibleInstanceOnlyAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst | CPF_DisableEditOnTemplate);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintReadWriteAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintSetterAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintReadOnlyAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible | CPF_BlueprintReadOnly);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintGetterAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetConfigAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Config);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetGlobalConfigAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_GlobalConfig | CPF_Config);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetLocalizedAttribute_Class()))
	{
		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetTransientAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Transient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetDuplicateTransientAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_DuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetTextExportTransientAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_TextExportTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetNonPIETransientAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetNonPIEDuplicateTransientAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_NonPIEDuplicateTransient);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetExportAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_ExportObject);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().NoClearAttribute_Class))
	{
		InProperty->SetPropertyFlags(CPF_NoClear);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetEditFixedSizeAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_EditFixedSize);
	}
#endif

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetReplicatedAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Net);

		if (const auto FoundMonoObject = AttrsGetAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetReplicatedAttribute_Class()))
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetReplicatedUsingAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Net | CPF_RepNotify);

		if (const auto FoundMonoObject = AttrsGetAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetReplicatedUsingAttribute_Class()))
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetNotReplicatedAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_RepSkip);
	}

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetInterpAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_Interp);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetNonTransactionalAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_NonTransactional);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetInstancedAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_PersistentInstance | CPF_ExportObject | CPF_InstancedReference);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintAssignableAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintAssignable);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintCallableAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintCallable);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintAuthorityOnlyAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintAuthorityOnly);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetAssetRegistrySearchableAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_AssetRegistrySearchable);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetSimpleDisplayAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_SimpleDisplay);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetAdvancedDisplayAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_AdvancedDisplay);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetSaveGameAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_SaveGame);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetSkipSerializationAttribute_Class()))
	{
		InProperty->SetPropertyFlags(CPF_SkipSerialization);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetFieldNotifyAttribute_Class()))
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

void FDynamicGeneratorCore::SetFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InFunction == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	auto bSpecifiedUnreliable = false;

	auto FunctionExportFlags = 0u;

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintNativeEventAttribute_Class()))
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintImplementableEventAttribute_Class()))
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetExecAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_Exec;

		if (InFunction->FunctionFlags & FUNC_Net)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetSealedEventAttribute_Class()))
	{
	}
#endif

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetServerAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetServer;

		if (InFunction->FunctionFlags & FUNC_Exec)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Exec functions cannot be replicated!"));
		}
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetClientAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetClient;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetNetMulticastAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetMulticast;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetServiceRequestAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetRequest;

		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetServiceResponseAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_Net;

		InFunction->FunctionFlags |= FUNC_NetReliable;

		InFunction->FunctionFlags |= FUNC_NetResponse;

		// @TODO ParseNetServiceIdentifiers(HeaderParser, FuncInfo, Specifier.Values)
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetReliableAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_NetReliable;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetUnreliableAttribute_Class()))
	{
		bSpecifiedUnreliable = true;
	}

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetCustomThunkAttribute_Class()))
	{
		FunctionExportFlags |= static_cast<uint32>(EDynamicFunctionExportFlags::FUNCEXPORT_CustomThunk);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintCallableAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCallable;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintGetterAttribute_Class()))
	{
		if (InFunction->FunctionFlags & FUNC_Event)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("Function cannot be a blueprint event and a blueprint getter"));
		}

		InFunction->FunctionFlags |= FUNC_BlueprintCallable;

		InFunction->FunctionFlags |= FUNC_BlueprintPure;

		// @TODO
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintSetterAttribute_Class()))
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

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintAuthorityOnlyAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintAuthorityOnly;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintPureAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_BlueprintCosmetic;
	}
#endif

	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetWithValidationAttribute_Class()))
	{
		InFunction->FunctionFlags |= FUNC_NetValidate;
	}

#if WITH_EDITOR
	if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetFieldNotifyAttribute_Class()))
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

void FDynamicGeneratorCore::SetFlags(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InClass == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = InClass->HasAnyClassFlags(CLASS_Interface)
	? FReflectionRegistry::Get().GetUInterfaceAttribute_Class()
	: FReflectionRegistry::Get().GetUClassAttribute_Class();
	
	if (!!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass))
	{
#if WITH_EDITOR
		if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetNotPlaceableAttribute_Class()))
		{
			InClass->ClassFlags |= CLASS_NotPlaceable;
		}
#endif

#if WITH_EDITOR
		SetMetaData(InClass, InMonoCustomAttrInfo);
#endif
	}
}

void FDynamicGeneratorCore::SetFlags(UScriptStruct* InScriptStruct, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InScriptStruct == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUStructAttribute_Class();

	if (!!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass))
	{
#if WITH_EDITOR
		SetMetaData(InScriptStruct, InMonoCustomAttrInfo);
#endif
	}
}

void FDynamicGeneratorCore::SetFlags(UEnum* InEnum, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InEnum == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUEnumAttribute_Class();

	if (!!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass))
	{
#if WITH_EDITOR
		SetMetaData(InEnum, InMonoCustomAttrInfo);
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
static void SetFieldMetaData(T InField, const TArray<FClassReflection*>& InMetaDataAttrs,
							 MonoCustomAttrInfo* InMonoCustomAttrInfo, const TFunction<void()>& InSetMetaData)
{
	for (const auto& MetaDataAttr : InMetaDataAttrs)
	{
		if (FDynamicGeneratorCore::AttrsHasAttr(InMonoCustomAttrInfo, MetaDataAttr->GetClass()))
		{
			FDynamicGeneratorCore::SetMetaData(InField, MetaDataAttr->GetName(),
											   FDynamicGeneratorCore::AttrGetValue(InMonoCustomAttrInfo, MetaDataAttr->GetClass()));
		}
	}

	InSetMetaData();
}

void FDynamicGeneratorCore::SetMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InProperty, GetPropertyMetaDataAttrs(), InMonoCustomAttrInfo, []()
	{
	});
}

void FDynamicGeneratorCore::SetMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InFunction, GetFunctionMetaDataAttrs(), InMonoCustomAttrInfo, []()
	{
	});
}

void FDynamicGeneratorCore::SetMetaData(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	SetFieldMetaData(InClass, InClass->IsChildOf(UInterface::StaticClass())
		                          ? GetInterfaceMetaDataAttrs()
		                          : GetClassMetaDataAttrs(),
	                 InMonoCustomAttrInfo, [InClass, InMonoCustomAttrInfo]()
	                 {
		                 if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetClassGroupAttribute_Class()))
		                 {
			                 SetMetaData(InClass, FString(TEXT("ClassGroupNamesAttribute")),
			                             *AttrGetValue(InMonoCustomAttrInfo,
			                                           FReflectionRegistry::Get().GetClassGroupAttribute_Class()));
		                 }

		                 if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetMinimalAPIAttribute_Class()))
		                 {
			                 SetMetaData(InClass, CLASS_MINIMAL_API_ATTRIBUTE, TEXT("true"));
		                 }

		                 if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintTypeAttribute_Class()))
		                 {
			                 SetMetaData(InClass, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
		                 }

		                 if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintableAttribute_Class()))
		                 {
			                 SetMetaData(InClass, CLASS_IS_BLUEPRINT_BASE_ATTRIBUTE, TEXT("true"));

			                 SetMetaData(InClass, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
		                 }
	                 });
}

void FDynamicGeneratorCore::SetMetaData(UScriptStruct* InScriptStruct, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InScriptStruct == nullptr || InScriptStruct == nullptr)
	{
		return;
	}

	SetFieldMetaData(InScriptStruct, GetStructMetaDataAttrs(), InMonoCustomAttrInfo, [InScriptStruct, InMonoCustomAttrInfo]()
	{
		if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintTypeAttribute_Class()))
		{
			SetMetaData(InScriptStruct, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
		}
	});
}

void FDynamicGeneratorCore::SetMetaData(UEnum* InEnum, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InEnum == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	SetFieldMetaData(InEnum, GetEnumMetaDataAttrs(), InMonoCustomAttrInfo,
	                 [InEnum, InMonoCustomAttrInfo]()
	                 {
		                 if (AttrsHasAttr(InMonoCustomAttrInfo, FReflectionRegistry::Get().GetBlueprintTypeAttribute_Class()))
		                 {
			                 SetMetaData(InEnum, CLASS_BLUEPRINT_TYPE_ATTRIBUTE, TEXT("true"));
		                 }
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

bool FDynamicGeneratorCore::AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass)
{
	return !!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, InMonoClass);
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

MonoObject* FDynamicGeneratorCore::AttrsGetAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass)
{
	return FMonoDomain::Custom_Attrs_Get_Attr(InMonoCustomAttrInfo, InMonoClass);
}

FString FDynamicGeneratorCore::AttrGetValue(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName)
{
	const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), InAttributeName);

	const auto FoundMonoObject = FMonoDomain::Custom_Attrs_Get_Attr(InMonoCustomAttrInfo, FoundMonoClass);

	const auto FoundMonoProperty = FMonoDomain::Class_Get_Property_From_Name(FoundMonoClass, TEXT("Value"));

	const auto Value = FMonoDomain::Property_Get_Value(FoundMonoProperty, FoundMonoObject, nullptr, nullptr);

	return FString(UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(FMonoDomain::Object_To_String(Value,nullptr))));
}

FString FDynamicGeneratorCore::AttrGetValue(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass)
{
	const auto FoundMonoObject = FMonoDomain::Custom_Attrs_Get_Attr(InMonoCustomAttrInfo, InMonoClass);

	const auto FoundMonoProperty = FMonoDomain::Class_Get_Property_From_Name(InMonoClass, TEXT("Value"));

	const auto Value = FMonoDomain::Property_Get_Value(FoundMonoProperty, FoundMonoObject, nullptr, nullptr);

	return FString(UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(FMonoDomain::Object_To_String(Value,nullptr))));
}

void FDynamicGeneratorCore::GeneratorProperty(MonoClass* InMonoClass, UField* InField,
                                              const TFunction<void(const MonoProperty*,
                                                                   MonoCustomAttrInfo*,
                                                                   const FProperty*)>& InGenerator)
{
	if (InMonoClass == nullptr || InField == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUPropertyAttribute_Class();

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

				SetFlags(CppProperty, Attrs);

				InField->AddCppProperty(CppProperty);

				InGenerator(Property, Attrs, CppProperty);
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

	const auto AttributeMonoClass = FReflectionRegistry::Get().GetUFunctionAttribute_Class();

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

				SetFlags(Function, Attrs);

				InClass->AddFunctionToFunctionMap(Function, MethodName);

				InGenerator(Function);
			}
		}
	}
}

MonoClass* FDynamicGeneratorCore::UInterfaceToIInterface(MonoClass* InMonoClass)
{
	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto NameSpace = FString(FMonoDomain::Class_Get_Namespace(InMonoClass));

	return FReflectionRegistry::Get().GetClassReflection(NameSpace,
	                                    FString::Printf(TEXT(
		                                    "I%s"
	                                    ),
	                                                    *ClassName.RightChop(1)
	                                    ))->GetClass();
}

MonoClass* FDynamicGeneratorCore::IInterfaceToUInterface(MonoClass* InMonoClass)
{
	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto NameSpace = FString(FMonoDomain::Class_Get_Namespace(InMonoClass));

	return FReflectionRegistry::Get().GetClassReflection(NameSpace,
	                                    FString::Printf(TEXT(
		                                    "U%s"
	                                    ),
	                                                    *ClassName.RightChop(1)
	                                    ))->GetClass();
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

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetClassMetaDataAttrs()
{
	static auto& Registry = FReflectionRegistry::Get();
	static TArray<FClassReflection*> ClassMetaDataAttrs = {
		Registry.GetHideCategoriesAttribute_Class(),
		Registry.GetToolTipAttribute_Class(),
		Registry.GetBlueprintSpawnableComponentAttribute_Class(),
		Registry.GetChildCanTickAttribute_Class(),
		Registry.GetChildCannotTickAttribute_Class(),
		Registry.GetDebugTreeLeafAttribute_Class(),
		Registry.GetIgnoreCategoryKeywordsInSubclassesAttribute_Class(),
		Registry.GetDeprecatedNodeAttribute_Class(),
		Registry.GetDeprecationMessageAttribute_Class(),
		Registry.GetDisplayNameAttribute_Class(),
		Registry.GetScriptNameAttribute_Class(),
		Registry.GetIsBlueprintBaseAttribute_Class(),
		Registry.GetKismetHideOverridesAttribute_Class(),
		Registry.GetLoadBehaviorAttribute_Class(),
		Registry.GetProhibitedInterfacesAttribute_Class(),
		Registry.GetRestrictedToClassesAttribute_Class(),
		Registry.GetShowWorldContextPinAttribute_Class(),
		Registry.GetDontUseGenericSpawnObjectAttribute_Class(),
		Registry.GetExposedAsyncProxyAttribute_Class(),
		Registry.GetBlueprintThreadSafeAttribute_Class(),
		Registry.GetUsesHierarchyAttribute_Class()
	};
	return ClassMetaDataAttrs;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetStructMetaDataAttrs()
{
	static auto& Registry = FReflectionRegistry::Get();
	static TArray<FClassReflection*> StructMetaDataAttrs = {
		Registry.GetToolTipAttribute_Class(),
		Registry.GetHasNativeBreakAttribute_Class(),
		Registry.GetHasNativeMakeAttribute_Class(),
		Registry.GetHiddenByDefaultAttribute_Class(),
		Registry.GetDisableSplitPinAttribute_Class()
	};
	return StructMetaDataAttrs;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetEnumMetaDataAttrs()
{
	static auto& Registry = FReflectionRegistry::Get();
	static TArray<FClassReflection*> EnumMetaDataAttrs = {
		Registry.GetToolTipAttribute_Class(),
		Registry.GetBitflagsAttribute_Class(),
		Registry.GetUseEnumValuesAsMaskValuesInEditorAttribute_Class()
	};
	return EnumMetaDataAttrs;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetInterfaceMetaDataAttrs()
{
	static auto& Registry = FReflectionRegistry::Get();
	static TArray<FClassReflection*> InterfaceMetaDataAttrs = {
		Registry.GetConversionRootAttribute_Class(),
		Registry.GetCannotImplementInterfaceInBlueprintAttribute_Class(),
		Registry.GetToolTipAttribute_Class()
	};
	return InterfaceMetaDataAttrs;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetPropertyMetaDataAttrs()
{
	static auto& Registry = FReflectionRegistry::Get();
	static TArray<FClassReflection*> PropertyMetaDataAttrs = {
		Registry.GetToolTipAttribute_Class(),
		Registry.GetDeprecationMessageAttribute_Class(),
		Registry.GetDisplayNameAttribute_Class(),
		Registry.GetScriptNameAttribute_Class(),
		Registry.GetLoadBehaviorAttribute_Class(),
		Registry.GetAllowAbstractAttribute_Class(),
		Registry.GetAllowAnyActorAttribute_Class(),
		Registry.GetAllowedClassesAttribute_Class(),
		Registry.GetAllowPreserveRatioAttribute_Class(),
		Registry.GetAllowPrivateAccessAttribute_Class(),
		Registry.GetArrayClampAttribute_Class(),
		Registry.GetAssetBundlesAttribute_Class(),
		Registry.GetBlueprintBaseOnlyAttribute_Class(),
		Registry.GetBlueprintCompilerGeneratedDefaultsAttribute_Class(),
		Registry.GetClampMinAttribute_Class(),
		Registry.GetClampMaxAttribute_Class(),
		Registry.GetConfigHierarchyEditableAttribute_Class(),
		Registry.GetContentDirAttribute_Class(),
		Registry.GetDeltaAttribute_Class(),
		Registry.GetDeprecatedPropertyAttribute_Class(),
		Registry.GetDisallowedAssetDataTagsAttribute_Class(),
		Registry.GetDisallowedClassesAttribute_Class(),
		Registry.GetDisplayAfterAttribute_Class(),
		Registry.GetDisplayPriorityAttribute_Class(),
		Registry.GetDisplayThumbnailAttribute_Class(),
		Registry.GetEditConditionAttribute_Class(),
		Registry.GetEditConditionHidesAttribute_Class(),
		Registry.GetEditFixedOrderAttribute_Class(),
		Registry.GetCategoryAttribute_Class(),
		Registry.GetExactClassAttribute_Class(),
		Registry.GetExposeFunctionCategoriesAttribute_Class(),
		Registry.GetExposeOnSpawnAttribute_Class(),
		Registry.GetFilePathFilterAttribute_Class(),
		Registry.GetRelativeToGameDirAttribute_Class(),
		Registry.GetFixedIncrementAttribute_Class(),
		Registry.GetForceShowEngineContentAttribute_Class(),
		Registry.GetForceShowPluginContentAttribute_Class(),
		Registry.GetHideAlphaChannelAttribute_Class(),
		Registry.GetHideInDetailPanelAttribute_Class(),
		Registry.GetHideViewOptionsAttribute_Class(),
		Registry.GetIgnoreForMemberInitializationTestAttribute_Class(),
		Registry.GetInlineEditConditionToggleAttribute_Class(),
		Registry.GetLinearDeltaSensitivityAttribute_Class(),
		Registry.GetLongPackageNameAttribute_Class(),
		Registry.GetMakeEditWidgetAttribute_Class(),
		Registry.GetMakeStructureDefaultValueAttribute_Class(),
		Registry.GetMetaClassAttribute_Class(),
		Registry.GetMustImplementAttribute_Class(),
		Registry.GetMultipleAttribute_Class(),
		Registry.GetMaxLengthAttribute_Class(),
		Registry.GetMultiLineAttribute_Class(),
		Registry.GetPasswordFieldAttribute_Class(),
		Registry.GetNoElementDuplicateAttribute_Class(),
		Registry.GetNoResetToDefaultAttribute_Class(),
		Registry.GetNoEditInlineAttribute_Class(),
		Registry.GetNoSpinboxAttribute_Class(),
		Registry.GetOnlyPlaceableAttribute_Class(),
		Registry.GetRelativePathAttribute_Class(),
		Registry.GetRelativeToGameContentDirAttribute_Class(),
		Registry.GetRequiredAssetDataTagsAttribute_Class(),
		Registry.GetScriptNoExportAttribute_Class(),
		Registry.GetShowOnlyInnerPropertiesAttribute_Class(),
		Registry.GetShowTreeViewAttribute_Class(),
		Registry.GetSliderExponentAttribute_Class(),
		Registry.GetTitlePropertyAttribute_Class(),
		Registry.GetUIMinAttribute_Class(),
		Registry.GetUIMaxAttribute_Class(),
		Registry.GetUnitsAttribute_Class(),
		Registry.GetForceUnitsAttribute_Class(),
		Registry.GetUntrackedAttribute_Class(),
		Registry.GetDevelopmentOnlyAttribute_Class(),
		Registry.GetNeedsLatentFixupAttribute_Class(),
		Registry.GetLatentCallbackTargetAttribute_Class(),
		Registry.GetGetOptionsAttribute_Class(),
		Registry.GetPinHiddenByDefaultAttribute_Class(),
		Registry.GetValidEnumValuesAttribute_Class(),
		Registry.GetInvalidEnumValuesAttribute_Class(),
		Registry.GetOverridingInputPropertyAttribute_Class(),
		Registry.GetRequiredInputAttribute_Class(),
		Registry.GetNeverAsPinAttribute_Class(),
		Registry.GetPinShownByDefaultAttribute_Class(),
		Registry.GetAlwaysAsPinAttribute_Class(),
		Registry.GetCustomizePropertyAttribute_Class()
	};
	return PropertyMetaDataAttrs;
}

const TArray<FClassReflection*>& FDynamicGeneratorCore::GetFunctionMetaDataAttrs()
{
	static auto& Registry = FReflectionRegistry::Get();
	static TArray<FClassReflection*> FunctionMetaDataAttrs = {
		Registry.GetCallInEditorAttribute_Class(),
		Registry.GetToolTipAttribute_Class(),
		Registry.GetCategoryAttribute_Class(),
		Registry.GetVariadicAttribute_Class(),
		Registry.GetReturnDisplayNameAttribute_Class(),
		Registry.GetInternalUseParamAttribute_Class(),
		Registry.GetForceAsFunctionAttribute_Class(),
		Registry.GetIgnoreTypePromotionAttribute_Class(),
		Registry.GetDeprecationMessageAttribute_Class(),
		Registry.GetDisplayNameAttribute_Class(),
		Registry.GetScriptNameAttribute_Class(),
		Registry.GetScriptNoExportAttribute_Class(),
		Registry.GetArrayParmAttribute_Class(),
		Registry.GetArrayTypeDependentParamsAttribute_Class(),
		Registry.GetAutoCreateRefTermAttribute_Class(),
		Registry.GetHideAssetPickerAttribute_Class(),
		Registry.GetBlueprintInternalUseOnlyAttribute_Class(),
		Registry.GetBlueprintProtectedAttribute_Class(),
		Registry.GetCallableWithoutWorldContextAttribute_Class(),
		Registry.GetCommutativeAssociativeBinaryOperatorAttribute_Class(),
		Registry.GetCompactNodeTitleAttribute_Class(),
		Registry.GetCustomStructureParamAttribute_Class(),
		Registry.GetDefaultToSelfAttribute_Class(),
		Registry.GetDeprecatedFunctionAttribute_Class(),
		Registry.GetExpandEnumAsExecsAttribute_Class(),
		Registry.GetExpandBoolAsExecsAttribute_Class(),
		Registry.GetScriptMethodAttribute_Class(),
		Registry.GetScriptMethodSelfReturnAttribute_Class(),
		Registry.GetScriptOperatorAttribute_Class(),
		Registry.GetScriptConstantAttribute_Class(),
		Registry.GetScriptConstantHostAttribute_Class(),
		Registry.GetHidePinAttribute_Class(),
		Registry.GetHideSpawnParmsAttribute_Class(),
		Registry.GetKeywordsAttribute_Class(),
		Registry.GetLatentAttribute_Class(),
		Registry.GetLatentInfoAttribute_Class(),
		Registry.GetMaterialParameterCollectionFunctionAttribute_Class(),
		Registry.GetNativeBreakFuncAttribute_Class(),
		Registry.GetNativeMakeFuncAttribute_Class(),
		Registry.GetUnsafeDuringActorConstructionAttribute_Class(),
		Registry.GetWorldContextAttribute_Class(),
		Registry.GetBlueprintAutoCastAttribute_Class(),
		Registry.GetNotBlueprintThreadSafeAttribute_Class(),
		Registry.GetDeterminesOutputTypeAttribute_Class(),
		Registry.GetDynamicOutputParamAttribute_Class(),
		Registry.GetDataTablePinAttribute_Class(),
		Registry.GetSetParamAttribute_Class(),
		Registry.GetMapParamAttribute_Class(),
		Registry.GetMapKeyParamAttribute_Class(),
		Registry.GetMapValueParamAttribute_Class(),
		Registry.GetBitmaskAttribute_Class(),
		Registry.GetBitmaskEnumAttribute_Class(),
		Registry.GetArrayParamAttribute_Class()
	};
	return FunctionMetaDataAttrs;
}
#endif
