#include "Dynamic/FDynamicStructGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Reflection/FReflectionRegistry.h"
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
	FDynamicGeneratorCore::Generator(FReflectionRegistry::Get().GetUStructAttributeClass(),
	                                 [](FClassReflection* InClassReflection)
	                                 {
		                                 if (InClassReflection == nullptr)
		                                 {
			                                 return;
		                                 }

		                                 auto Node = FDynamicDependencyGraph::FNode(
			                                 InClassReflection->GetName(), [InClassReflection]()
			                                 {
				                                 Generator(InClassReflection);
			                                 });

		                                 if (const auto ParentClassReflection = InClassReflection->
			                                 GetParent())
		                                 {
			                                 if (ParentClassReflection->HasAttribute(
				                                 FReflectionRegistry::Get().GetUStructAttributeClass()))
			                                 {
				                                 Node.Dependency(FDynamicDependencyGraph::FDependency{
					                                 ParentClassReflection->GetName(), false
				                                 });
			                                 }
		                                 }

		                                 FDynamicGeneratorCore::GeneratorProperty(InClassReflection, Node);

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
#endif

void FDynamicStructGenerator::Generator(FClassReflection* InClassReflection)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	const auto ClassName = InClassReflection->GetName();

	const auto ClassNamespace = InClassReflection->GetNameSpace();

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

	if (const auto Parent = InClassReflection->GetParent())
	{
		if (Parent != FReflectionRegistry::Get().GetObjectClass())
		{
			const auto ParentPathName = Parent->GetPathName();

			ParentScriptStruct = LoadObject<UScriptStruct>(nullptr, *ParentPathName);
		}
	}

	const auto ScriptStruct = GeneratorStruct(Outer, ClassNamespace, ClassName, ParentScriptStruct,
	                                          [InClassReflection](UDynamicScriptStruct* InScriptStruct)
	                                          {
		                                          ProcessGenerator(InClassReflection, InScriptStruct);
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

bool FDynamicStructGenerator::IsDynamicStruct(const UField* InField)
{
	return DynamicStructSet.Contains(Cast<UDynamicScriptStruct>(InField));
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

void FDynamicStructGenerator::ProcessGenerator(FClassReflection* InClassReflection,
                                               UDynamicScriptStruct* InScriptStruct)
{
	FDynamicGeneratorCore::SetFlags(InClassReflection, InScriptStruct);

	GeneratorProperty(InClassReflection, InScriptStruct);
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
		if (const auto FoundClass = FReflectionRegistry::Get().GetClass(DynamicClass))
		{
			FDynamicClassGenerator::Generator(FoundClass, EDynamicClassGeneratorType::ReInstance);
		}
	}

	InOldScriptStruct->RemoveFromRoot();

	InOldScriptStruct->MarkAsGarbage();
}
#endif

void FDynamicStructGenerator::GeneratorProperty(const FClassReflection* InClassReflection,
                                                UDynamicScriptStruct* InScriptStruct)
{
	FDynamicGeneratorCore::GeneratorProperty(InClassReflection, InScriptStruct,
	                                         [](FPropertyReflection* InPropertyReflection,
	                                            const FProperty* InProperty)
	                                         {
	                                         });
}
