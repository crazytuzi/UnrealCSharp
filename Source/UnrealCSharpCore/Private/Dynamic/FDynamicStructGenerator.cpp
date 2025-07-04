#include "Dynamic/FDynamicStructGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#if WITH_EDITOR
#include "K2Node_StructOperation.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "BlueprintActionDatabase.h"
#include "Dynamic/FDynamicBlueprintExtensionScope.h"
#endif
#include "UEVersion.h"

TMap<UDynamicScriptStruct*, FString> FDynamicStructGenerator::NamespaceMap;

TMap<FString, UDynamicScriptStruct*> FDynamicStructGenerator::DynamicStructMap;

TSet<UDynamicScriptStruct*> FDynamicStructGenerator::DynamicStructSet;

void FDynamicStructGenerator::Generator()
{
	FDynamicGeneratorCore::Generator(CLASS_U_STRUCT_ATTRIBUTE,
	                                 [](MonoClass* InMonoClass)
	                                 {
		                                 if (InMonoClass == nullptr)
		                                 {
			                                 return;
		                                 }

		                                 const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

		                                 auto Node = FDynamicDependencyGraph::FNode(ClassName, [InMonoClass]()
		                                 {
			                                 Generator(InMonoClass);
		                                 });

		                                 if (const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass))
		                                 {
			                                 if (FDynamicGeneratorCore::ClassHasAttr(
				                                 ParentMonoClass, CLASS_U_STRUCT_ATTRIBUTE))
			                                 {
				                                 const auto ParentClassName = FString(
					                                 FMonoDomain::Class_Get_Name(ParentMonoClass));

				                                 Node.Dependency(FDynamicDependencyGraph::FDependency{
					                                 ParentClassName, false
				                                 });
			                                 }
		                                 }

		                                 FDynamicGeneratorCore::GeneratorProperty(InMonoClass, Node);

		                                 FDynamicGeneratorCore::AddNode(Node);
	                                 });
}

#if WITH_EDITOR
void FDynamicStructGenerator::CodeAnalysisGenerator()
{
	FDynamicGeneratorCore::CodeAnalysisGenerator(DYNAMIC_STRUCT,
	                                             [](const FString& InNameSpace, const FString& InName)
	                                             {
		                                             if (!DynamicStructMap.Contains(InName))
		                                             {
			                                             GeneratorStruct(FDynamicGeneratorCore::GetOuter(),
			                                                             InNameSpace,
			                                                             InName,
			                                                             nullptr);
		                                             }
	                                             });
}

bool FDynamicStructGenerator::IsDynamicStruct(MonoClass* InMonoClass)
{
	return FDynamicGeneratorCore::IsDynamic(InMonoClass, CLASS_U_STRUCT_ATTRIBUTE);
}
#endif

void FDynamicStructGenerator::Generator(MonoClass* InMonoClass)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto ClassNamespace = FString(FMonoDomain::Class_Get_Namespace(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

#if WITH_EDITOR
	UDynamicScriptStruct* OldScriptStruct{};

	if (DynamicStructMap.Contains(ClassName))
	{
		OldScriptStruct = DynamicStructMap[ClassName];

		DynamicStructSet.Remove(OldScriptStruct);

		OldScriptStruct->Rename(
			*MakeUniqueObjectName(
				OldScriptStruct->GetOuter(),
				OldScriptStruct->GetClass(),
				*FDynamicGeneratorCore::DynamicReInstanceBaseName())
			.ToString(),
			nullptr,
			REN_DontCreateRedirectors);
	}
#endif

	UScriptStruct* ParentScriptStruct{};

	if (const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass))
	{
		if (ParentMonoClass != FMonoDomain::Get_Object_Class())
		{
			if (const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass))
			{
				if (const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType))
				{
					const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

					ParentScriptStruct = LoadObject<UScriptStruct>(nullptr, *ParentPathName);
				}
			}
		}
	}

	const auto ScriptStruct = GeneratorStruct(Outer, ClassNamespace, ClassName, ParentScriptStruct,
	                                          [InMonoClass](UDynamicScriptStruct* InScriptStruct)
	                                          {
		                                          ProcessGenerator(InMonoClass, InScriptStruct);
	                                          });

#if WITH_EDITOR
	if (OldScriptStruct != nullptr)
	{
		ScriptStruct->Guid = OldScriptStruct->Guid;

		ReInstance(OldScriptStruct, ScriptStruct);
	}
	else
	{
		ScriptStruct->Guid = FGuid::NewGuid();
	}
#endif

	FDynamicGeneratorCore::Completed(ClassName);
}

bool FDynamicStructGenerator::IsDynamicStruct(const UScriptStruct* InScriptStruct)
{
	return DynamicStructSet.Contains(Cast<UDynamicScriptStruct>(InScriptStruct));
}

FString FDynamicStructGenerator::GetNameSpace(const UScriptStruct* InScriptStruct)
{
	const auto FoundNameSpace = NamespaceMap.Find(Cast<UDynamicScriptStruct>(InScriptStruct));

	return FoundNameSpace != nullptr ? *FoundNameSpace : FString{};
}

void FDynamicStructGenerator::BeginGenerator(UDynamicScriptStruct* InScriptStruct,
                                             UScriptStruct* InParentScriptStruct)
{
	if (InParentScriptStruct != nullptr)
	{
		InScriptStruct->SetSuperStruct(InParentScriptStruct);
	}
}

void FDynamicStructGenerator::ProcessGenerator(MonoClass* InMonoClass, UDynamicScriptStruct* InScriptStruct)
{
	FDynamicGeneratorCore::SetFlags(InScriptStruct, FMonoDomain::Custom_Attrs_From_Class(InMonoClass));

	GeneratorProperty(InMonoClass, InScriptStruct);
}

void FDynamicStructGenerator::EndGenerator(UDynamicScriptStruct* InScriptStruct)
{
	InScriptStruct->Bind();

	InScriptStruct->StaticLink(true);

	if (InScriptStruct->GetPropertiesSize() == 0)
	{
		InScriptStruct->SetPropertiesSize(1);
	}

	InScriptStruct->SetInternalFlags(EInternalObjectFlags::Native);

	InScriptStruct->StructFlags = STRUCT_Native;

#if WITH_EDITOR
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InScriptStruct);

		ActionDatabase.RefreshAssetActions(InScriptStruct);
	}
#endif

#if UE_NOTIFY_REGISTRATION_EVENT
#if !WITH_EDITOR
	NotifyRegistrationEvent(*InScriptStruct->GetPackage()->GetName(),
	                        *InScriptStruct->GetName(),
	                        ENotifyRegistrationType::NRT_Class,
	                        ENotifyRegistrationPhase::NRP_Finished,
	                        nullptr,
	                        false,
	                        InScriptStruct);
#endif
#endif
}

void FDynamicStructGenerator::GeneratorStruct(const FString& InNameSpace, const FString& InName,
                                              UDynamicScriptStruct* InScriptStruct, UScriptStruct* InParentScriptStruct,
                                              const TFunction<void(UDynamicScriptStruct*)>& InProcessGenerator)
{
	NamespaceMap.Add(InScriptStruct, InNameSpace);

	DynamicStructMap.Add(InName, InScriptStruct);

	DynamicStructSet.Add(InScriptStruct);

	BeginGenerator(InScriptStruct, InParentScriptStruct);

	InProcessGenerator(InScriptStruct);

	EndGenerator(InScriptStruct);
}

UDynamicScriptStruct* FDynamicStructGenerator::GeneratorStruct(UPackage* InOuter, const FString& InNameSpace,
                                                               const FString& InName,
                                                               UScriptStruct* InParentScriptStruct)
{
	return GeneratorStruct(InOuter, InNameSpace, InName, InParentScriptStruct,
	                       [](UDynamicScriptStruct* InScriptStruct)
	                       {
	                       });
}

UDynamicScriptStruct* FDynamicStructGenerator::GeneratorStruct(UPackage* InOuter, const FString& InNameSpace,
                                                               const FString& InName,
                                                               UScriptStruct* InParentScriptStruct,
                                                               const TFunction<void(UDynamicScriptStruct*)>&
                                                               InProcessGenerator)
{
	const auto ScriptStruct = NewObject<UDynamicScriptStruct>(InOuter, *InName.RightChop(1), RF_Public);

	ScriptStruct->AddToRoot();

	GeneratorStruct(InNameSpace, InName, ScriptStruct, InParentScriptStruct, InProcessGenerator);

	return ScriptStruct;
}

#if WITH_EDITOR
void FDynamicStructGenerator::ReInstance(UDynamicScriptStruct* InOldScriptStruct,
                                         UDynamicScriptStruct* InNewScriptStruct)
{
	TArray<UClass*> DynamicClasses;

	TArray<UBlueprintGeneratedClass*> BlueprintGeneratedClasses;

	FDynamicGeneratorCore::IteratorObject<UClass>(
		[InOldScriptStruct](const TObjectIterator<UClass>& InClass)
		{
			for (TFieldIterator<FProperty> It(*InClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
			{
				if (const auto StructProperty = CastField<FStructProperty>(*It))
				{
					if (StructProperty->Struct == InOldScriptStruct)
					{
						return true;
					}
				}
			}

			return false;
		},
		[&DynamicClasses, &BlueprintGeneratedClasses](const TObjectIterator<UClass>& InClass)
		{
			if (FDynamicClassGenerator::IsDynamicClass(*InClass))
			{
				DynamicClasses.AddUnique(*InClass);
			}
			else if (const auto BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(*InClass))
			{
				if (!FUnrealCSharpFunctionLibrary::IsSpecialClass(*InClass))
				{
					BlueprintGeneratedClasses.AddUnique(BlueprintGeneratedClass);
				}
			}
		});

	FDynamicGeneratorCore::IteratorObject<UBlueprintGeneratedClass>(
		[](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			return FDynamicClassGenerator::IsDynamicBlueprintGeneratedSubClass(*InBlueprintGeneratedClass);
		},
		[&BlueprintGeneratedClasses](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			if (!FUnrealCSharpFunctionLibrary::IsSpecialClass(*InBlueprintGeneratedClass))
			{
				BlueprintGeneratedClasses.AddUnique(*InBlueprintGeneratedClass);
			}
		});

	for (const auto BlueprintGeneratedClass : BlueprintGeneratedClasses)
	{
		if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
		{
			FDynamicBlueprintExtensionScope DynamicBlueprintExtensionScope(Blueprint);

			auto bIsRefresh = false;

			TArray<UK2Node*> AllNodes;

			FBlueprintEditorUtils::GetAllNodesOfClass(Blueprint, AllNodes);

			for (const auto Node : AllNodes)
			{
				if (const auto StructOperation = Cast<UK2Node_StructOperation>(Node))
				{
					if (StructOperation->StructType == InOldScriptStruct)
					{
						StructOperation->StructType = InNewScriptStruct;

						bIsRefresh = true;
					}
				}
				else
				{
					for (const auto Pin : Node->Pins)
					{
						if (Pin->PinType.PinSubCategoryObject == InOldScriptStruct)
						{
							Pin->PinType.PinSubCategoryObject = InNewScriptStruct;

							Pin->Modify();

							bIsRefresh = true;
						}
					}
				}
			}

			for (auto& Variable : Blueprint->NewVariables)
			{
				if (Variable.VarType.PinSubCategoryObject == InOldScriptStruct)
				{
					Variable.VarType.PinSubCategoryObject = InNewScriptStruct;

					bIsRefresh = true;
				}
			}

			if (bIsRefresh)
			{
				FBlueprintEditorUtils::RefreshAllNodes(Blueprint);

				FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);

				constexpr auto BlueprintCompileOptions = EBlueprintCompileOptions::SkipGarbageCollection |
					EBlueprintCompileOptions::SkipSave;

				FKismetEditorUtilities::CompileBlueprint(Blueprint, BlueprintCompileOptions);
			}
		}
	}

	for (const auto DynamicClass : DynamicClasses)
	{
		if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(DynamicClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(DynamicClass)))
		{
			FDynamicClassGenerator::Generator(FoundMonoClass, EDynamicClassGeneratorType::ReInstance);
		}
	}

	InOldScriptStruct->RemoveFromRoot();

	InOldScriptStruct->MarkAsGarbage();
}
#endif

void FDynamicStructGenerator::GeneratorProperty(MonoClass* InMonoClass, UDynamicScriptStruct* InScriptStruct)
{
	FDynamicGeneratorCore::GeneratorProperty(InMonoClass, InScriptStruct,
	                                         [](const MonoProperty* InMonoProperty,
	                                            const MonoCustomAttrInfo* InMonoCustomAttrInfo,
	                                            const FProperty* InProperty)
	                                         {
	                                         });
}
