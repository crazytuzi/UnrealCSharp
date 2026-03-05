#include "Dynamic/FDynamicClassGenerator.h"
#include "Engine/SCS_Node.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Reflection/FReflectionRegistry.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/InheritableComponentHandler.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Dynamic/FDynamicBlueprintExtensionScope.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#endif
#include "UEVersion.h"

TSet<UClass::ClassConstructorType> FDynamicClassGenerator::ClassConstructorSet
{
	&FDynamicClassGenerator::ClassConstructor
};

TMap<UClass*, FString> FDynamicClassGenerator::NamespaceMap;

TMap<UClass*, TArray<FDynamicClassGenerator::FDefaultSubObjectInfo>> FDynamicClassGenerator::DefaultSubObjectInfoMap;

TMap<FString, UClass*> FDynamicClassGenerator::DynamicClassMap;

TSet<UClass*> FDynamicClassGenerator::DynamicClassSet;

TMap<UClass*, TArray<TTuple<const FProperty*, FString>>> FDynamicClassGenerator::DefaultValueMap;

void FDynamicClassGenerator::Generator()
{
	FDynamicGeneratorCore::Generator(FReflectionRegistry::Get().GetUClassAttributeClass(),
	                                 [](FClassReflection* InClassReflection)
	                                 {
		                                 if (InClassReflection == nullptr)
		                                 {
			                                 return;
		                                 }

		                                 if (!InClassReflection->IsClass())
		                                 {
			                                 return;
		                                 }

		                                 auto Node = FDynamicDependencyGraph::FNode(
			                                 InClassReflection->GetName(), [InClassReflection]()
			                                 {
				                                 Generator(InClassReflection,
				                                           EDynamicClassGeneratorType::DependencyGraph);
			                                 });

		                                 if (const auto Parent = InClassReflection->GetParent())
		                                 {
			                                 if (Parent->HasAttribute(
				                                 FReflectionRegistry::Get().GetUClassAttributeClass()))
			                                 {
				                                 Node.Dependency(FDynamicDependencyGraph::FDependency{
					                                 Parent->GetName(), false
				                                 });
			                                 }
		                                 }

		                                 FDynamicGeneratorCore::GeneratorProperty(InClassReflection, Node);

		                                 FDynamicGeneratorCore::GeneratorFunction(InClassReflection, Node);

		                                 FDynamicGeneratorCore::GeneratorInterface(InClassReflection, Node);

		                                 FDynamicGeneratorCore::AddNode(Node);
	                                 });
}

#if WITH_EDITOR
void FDynamicClassGenerator::CodeAnalysisGenerator()
{
	FDynamicGeneratorCore::CodeAnalysisGenerator(DYNAMIC_CLASS,
	                                             [](const FString& InNameSpace, const FString& InName)
	                                             {
		                                             if (!DynamicClassMap.Contains(InName))
		                                             {
			                                             if (IsDynamicBlueprintGeneratedClass(InName))
			                                             {
				                                             GeneratorBlueprintGeneratedClass(
					                                             FDynamicGeneratorCore::GetOuter(),
					                                             InNameSpace,
					                                             InName,
					                                             AActor::StaticClass());
			                                             }
			                                             else
			                                             {
				                                             GeneratorClass(
					                                             FDynamicGeneratorCore::GetOuter(),
					                                             InNameSpace,
					                                             InName,
					                                             AActor::StaticClass());
			                                             }
		                                             }
	                                             });

	FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.Broadcast();
}

void FDynamicClassGenerator::OnPrePIEEnded(const bool bIsSimulating)
{
	FDynamicGeneratorCore::IteratorObject<UBlueprintGeneratedClass>(
		[](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			for (const auto& [PLACEHOLDER, Value] : DynamicClassMap)
			{
				if (InBlueprintGeneratedClass->IsChildOf(Value))
				{
					return true;
				}
			}

			return false;
		},
		[](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			InBlueprintGeneratedClass->ClassConstructor = &FDynamicClassGenerator::ClassConstructor;
		});
}

const TSet<UClass*>& FDynamicClassGenerator::GetDynamicClasses()
{
	return DynamicClassSet;
}
#endif

void FDynamicClassGenerator::Generator(FClassReflection* InClassReflection,
                                       EDynamicClassGeneratorType InDynamicClassGeneratorType)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	if (!InClassReflection->IsClass())
	{
		return;
	}

	const auto ClassName = InClassReflection->GetName();

	const auto ClassNamespace = InClassReflection->GetNameSpace();

	const auto Outer = FDynamicGeneratorCore::GetOuter();

	UClass* ParentClass{};

	if (const auto Parent = InClassReflection->GetParent())
	{
		ParentClass = LoadClass<UObject>(nullptr, *Parent->GetPathName());
	}

	UClass* Class{};

#if WITH_EDITOR
	UClass* OldClass{};

	if (DynamicClassMap.Contains(ClassName))
	{
		OldClass = DynamicClassMap[ClassName];

		DynamicClassSet.Remove(OldClass);

		if (const auto BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(OldClass))
		{
			if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
			{
				Blueprint->Rename(
					*MakeUniqueObjectName(
						BlueprintGeneratedClass->GetOuter(),
						BlueprintGeneratedClass->GetClass(),
						*FDynamicGeneratorCore::DynamicReInstanceBaseName())
					.ToString(),
					nullptr,
					REN_DontCreateRedirectors);
			}
		}
		else
		{
			OldClass->Rename(
				*MakeUniqueObjectName(
					OldClass->GetOuter(),
					OldClass->GetClass(),
					*FDynamicGeneratorCore::DynamicReInstanceBaseName())
				.ToString(),
				nullptr,
				REN_DontCreateRedirectors);
		}
	}
#endif

	if (IsDynamicBlueprintGeneratedClass(ClassName))
	{
		Class = GeneratorBlueprintGeneratedClass(Outer, ClassNamespace, ClassName, ParentClass,
		                                         [InClassReflection](UClass* InClass)
		                                         {
			                                         ProcessGenerator(InClassReflection, InClass);
		                                         });
	}
	else
	{
		Class = GeneratorClass(Outer, ClassNamespace, ClassName, ParentClass,
		                       [InClassReflection](UClass* InClass)
		                       {
			                       ProcessGenerator(InClassReflection, InClass);
		                       });
	}

#if WITH_EDITOR
	if (OldClass != nullptr)
	{
		ReInstance(OldClass, Class);
	}
#endif

	FDynamicGeneratorCore::Completed(ClassName);

#if WITH_EDITOR
	FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.Broadcast();
#endif
}

bool FDynamicClassGenerator::IsDynamicClass(const UClass* InClass)
{
	return DynamicClassSet.Contains(InClass);
}

bool FDynamicClassGenerator::IsDynamicClass(const UField* InField)
{
	return DynamicClassSet.Contains(Cast<UClass>(InField));
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(const UField* InField)
{
	return IsDynamicBlueprintGeneratedClass(Cast<UBlueprintGeneratedClass>(InField));
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(const UBlueprintGeneratedClass* InClass)
{
	return IsDynamicClass(InClass);
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedSubClass(const UBlueprintGeneratedClass* InClass)
{
	for (const auto DynamicClass : DynamicClassSet)
	{
		if (InClass->IsChildOf(DynamicClass) && InClass != DynamicClass)
		{
			return true;
		}
	}

	return false;
}

UClass* FDynamicClassGenerator::GetDynamicClass(const FClassReflection* InClassReflection)
{
	const auto FoundDynamicClass = DynamicClassMap.Find(InClassReflection->GetName());

	return FoundDynamicClass != nullptr ? *FoundDynamicClass : nullptr;
}

FString FDynamicClassGenerator::GetNameSpace(const UClass* InClass)
{
	const auto FoundNameSpace = NamespaceMap.Find(InClass);

	return FoundNameSpace != nullptr ? *FoundNameSpace : FString{};
}

void FDynamicClassGenerator::BeginGenerator(UClass* InClass, UClass* InParentClass)
{
	InClass->PropertyLink = InParentClass->PropertyLink;

	InClass->ClassWithin = InParentClass->ClassWithin;

	InClass->ClassConfigName = InParentClass->ClassConfigName;

	InClass->SetSuperStruct(InParentClass);

#if UE_U_CLASS_ADD_REFERENCED_OBJECTS
	InClass->ClassAddReferencedObjects = InParentClass->ClassAddReferencedObjects;
#endif

	InClass->ClassFlags |= CLASS_Native;

	InClass->ClassCastFlags |= InParentClass->ClassCastFlags;

	InClass->ClassConstructor = &FDynamicClassGenerator::ClassConstructor;
}

void FDynamicClassGenerator::BeginGenerator(UBlueprintGeneratedClass* InClass, UClass* InParentClass)
{
	BeginGenerator(static_cast<UClass*>(InClass), InParentClass);

#if WITH_EDITOR
	Cast<UBlueprint>(InClass->ClassGeneratedBy)->ParentClass = InParentClass;
#endif

	InClass->ClassFlags &= ~CLASS_Native;
}

void FDynamicClassGenerator::ProcessGenerator(FClassReflection* InClassReflection, UClass* InClass)
{
	FDynamicGeneratorCore::SetFlags(InClassReflection, InClass);

	GeneratorProperty(InClassReflection, InClass);

	GeneratorFunction(InClassReflection, InClass);

	GeneratorInterface(InClassReflection, InClass);
}

void FDynamicClassGenerator::EndGenerator(UClass* InClass)
{
	InClass->ClearInternalFlags(EInternalObjectFlags::Native);

	InClass->Bind();

	InClass->StaticLink(true);

	InClass->AssembleReferenceTokenStream();

	FUnrealCSharpFunctionLibrary::SetClassDefaultObject(InClass);

	(*InClass->ClassConstructor)(FObjectInitializer(InClass->GetDefaultObject(false),
	                                                InClass->GetSuperClass()->GetDefaultObject(),
	                                                EObjectInitializerOptions::None));

	InClass->SetInternalFlags(EInternalObjectFlags::Native);

#if WITH_EDITOR
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InClass);

		ActionDatabase.RefreshClassActions(InClass);
	}
#endif

#if UE_NOTIFY_REGISTRATION_EVENT
#if !WITH_EDITOR
	NotifyRegistrationEvent(*InClass->GetDefaultObject(false)->GetPackage()->GetName(),
	                        *InClass->GetDefaultObject(false)->GetName(),
	                        ENotifyRegistrationType::NRT_ClassCDO,
	                        ENotifyRegistrationPhase::NRP_Finished,
	                        nullptr,
	                        false,
	                        InClass->GetDefaultObject(false));


	NotifyRegistrationEvent(*InClass->GetPackage()->GetName(),
	                        *InClass->GetName(),
	                        ENotifyRegistrationType::NRT_Class,
	                        ENotifyRegistrationPhase::NRP_Finished,
	                        nullptr,
	                        false,
	                        InClass);
#endif
#endif
}

UClass* FDynamicClassGenerator::GeneratorClass(UPackage* InOuter, const FString& InNameSpace,
                                               const FString& InName, UClass* InParentClass)
{
	return GeneratorClass(InOuter, InNameSpace, InName, InParentClass,
	                      [](UClass* InClass)
	                      {
	                      });
}

UClass* FDynamicClassGenerator::GeneratorClass(UPackage* InOuter, const FString& InNameSpace,
                                               const FString& InName, UClass* InParentClass,
                                               const TFunction<void(UClass*)>& InProcessGenerator)
{
	const auto Class = NewObject<UClass>(InOuter, *InName.RightChop(1), RF_Public);

	Class->AddToRoot();

	GeneratorClass(InNameSpace, InName, Class, InParentClass, InProcessGenerator);

	return Class;
}

UBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorBlueprintGeneratedClass(
	UPackage* InOuter, const FString& InNameSpace, const FString& InName, UClass* InParentClass)
{
	return GeneratorBlueprintGeneratedClass(InOuter, InNameSpace, InName, InParentClass,
	                                        [](UClass* InClass)
	                                        {
	                                        });
}

UBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorBlueprintGeneratedClass(
	UPackage* InOuter, const FString& InNameSpace, const FString& InName, UClass* InParentClass,
	const TFunction<void(UClass*)>& InProcessGenerator)
{
	auto Class = NewObject<UBlueprintGeneratedClass>(InOuter, *InName, RF_Public);

	Class->UpdateCustomPropertyListForPostConstruction();

	const auto Blueprint = NewObject<UBlueprint>(Class, *InName.LeftChop(2));

	Blueprint->AddToRoot();

	Blueprint->SkeletonGeneratedClass = Class;

	Blueprint->GeneratedClass = Class;

#if WITH_EDITOR
	Class->ClassGeneratedBy = Blueprint;
#endif

	GeneratorClass(InNameSpace, InName, Class, InParentClass, InProcessGenerator);

	return Class;
}

#if WITH_EDITOR
void FDynamicClassGenerator::ReInstance(UClass* InOldClass, UClass* InNewClass)
{
	InOldClass->ClassFlags |= CLASS_NewerVersionExists;

#if UE_F_REPLACE_INSTANCES_OF_CLASS_F_REPLACE_INSTANCES_OF_CLASS_PARAMETERS
	FReplaceInstancesOfClassParameters ReplaceInstancesOfClassParameters;

	ReplaceInstancesOfClassParameters.OriginalCDO = InOldClass->GetDefaultObject(false);

	FBlueprintCompileReinstancer::ReplaceInstancesOfClass(InOldClass, InNewClass, ReplaceInstancesOfClassParameters);
#else
	FBlueprintCompileReinstancer::ReplaceInstancesOfClass(InOldClass, InNewClass, InOldClass->ClassDefaultObject);
#endif

	TArray<UBlueprintGeneratedClass*> BlueprintGeneratedClasses;

	FDynamicGeneratorCore::IteratorObject<UBlueprintGeneratedClass>(
		[InOldClass](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			return InBlueprintGeneratedClass->IsChildOf(InOldClass) && *InBlueprintGeneratedClass != InOldClass;
		},
		[&BlueprintGeneratedClasses](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			if (!FUnrealCSharpFunctionLibrary::IsSpecialClass(*InBlueprintGeneratedClass))
			{
				BlueprintGeneratedClasses.AddUnique(*InBlueprintGeneratedClass);
			}
		});

	FUnrealCSharpFunctionLibrary::SetClassDefaultObject(InOldClass, nullptr);

	(void)InOldClass->GetDefaultObject(true);

	for (const auto BlueprintGeneratedClass : BlueprintGeneratedClasses)
	{
		if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
		{
			FDynamicBlueprintExtensionScope DynamicBlueprintExtensionScope(Blueprint);

			Blueprint->Modify();

			if (const auto SimpleConstructionScript = Blueprint->SimpleConstructionScript)
			{
				SimpleConstructionScript->Modify();

				const auto& AllNodes = SimpleConstructionScript->GetAllNodes();

				for (const auto& Node : AllNodes)
				{
					Node->Modify();
				}
			}

			Blueprint->ParentClass = InNewClass;

			if (FDynamicGenerator::IsFullGenerator())
			{
				const auto OriginalBlueprintType = Blueprint->BlueprintType;

				Blueprint->BlueprintType = BPTYPE_MacroLibrary;

				FBlueprintEditorUtils::RefreshAllNodes(Blueprint);

				Blueprint->BlueprintType = OriginalBlueprintType;

				TArray<UK2Node*> AllNodes;

				FBlueprintEditorUtils::GetAllNodesOfClass(Blueprint, AllNodes);

				for (const auto Node : AllNodes)
				{
					for (const auto Pin : Node->Pins)
					{
						if (Pin->PinType.PinSubCategoryObject == InOldClass)
						{
							Pin->PinType.PinSubCategoryObject = InNewClass;
						}
					}
				}
			}
			else
			{
				FBlueprintEditorUtils::RefreshAllNodes(Blueprint);
			}

			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);

			constexpr auto BlueprintCompileOptions = EBlueprintCompileOptions::SkipGarbageCollection |
				EBlueprintCompileOptions::SkipSave;

			FKismetEditorUtilities::CompileBlueprint(Blueprint, BlueprintCompileOptions);
		}
	}

	if (const auto BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InOldClass))
	{
		if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
		{
			Blueprint->RemoveFromRoot();

			Blueprint->MarkAsGarbage();
		}
	}
	else
	{
		InOldClass->RemoveFromRoot();

		InOldClass->MarkAsGarbage();
	}
}
#endif

void FDynamicClassGenerator::GeneratorProperty(const FClassReflection* InClassReflection, UClass* InClass)
{
	FDynamicGeneratorCore::GeneratorProperty(InClassReflection, InClass,
	                                         [InClass](FPropertyReflection* InPropertyReflection,
	                                                   const FProperty* InProperty)
	                                         {
		                                         if (InProperty->HasAnyPropertyFlags(CPF_Net))
		                                         {
			                                         if (const auto BlueprintGeneratedClass = Cast<
				                                         UBlueprintGeneratedClass>(InClass))
			                                         {
				                                         BlueprintGeneratedClass->NumReplicatedProperties++;
			                                         }
		                                         }
#if WITH_EDITOR
		                                         if (const auto Blueprint = Cast<UBlueprint>(InClass->ClassGeneratedBy))
		                                         {
			                                         auto bExisted = false;

			                                         for (const auto& Variable : Blueprint->NewVariables)
			                                         {
				                                         if (Variable.VarName == InProperty->GetFName())
				                                         {
					                                         bExisted = true;

					                                         break;
				                                         }
			                                         }

			                                         if (!bExisted)
			                                         {
				                                         FBPVariableDescription BPVariableDescription;

				                                         BPVariableDescription.VarName = InProperty->GetFName();

				                                         BPVariableDescription.VarGuid = FGuid::NewGuid();

				                                         Blueprint->NewVariables.Add(BPVariableDescription);
			                                         }
		                                         }

#endif

		                                         if (IsDynamicBlueprintGeneratedClass(InClass))
		                                         {
			                                         if (InPropertyReflection->HasAttribute(
				                                         FReflectionRegistry::Get().
				                                         GetDefaultSubObjectAttributeClass()))
			                                         {
				                                         FDefaultSubObjectInfo DefaultSubObject;

				                                         DefaultSubObject.Property = CastField<FObjectProperty>(
					                                         InProperty);

				                                         DefaultSubObject.bIsRootComponent =
					                                         InPropertyReflection->HasAttribute(
						                                         FReflectionRegistry::Get().
						                                         GetRootComponentAttributeClass());

				                                         DefaultSubObject.Parent = InPropertyReflection->HasAttribute(
						                                         FReflectionRegistry::Get().
						                                         GetAttachmentParentAttributeClass())
						                                         ? InPropertyReflection->GetAttributeValue(
							                                         FReflectionRegistry::Get().
							                                         GetAttachmentParentAttributeClass())
						                                         : FString{};

				                                         DefaultSubObject.Socket = InPropertyReflection->HasAttribute(
						                                         FReflectionRegistry::Get().
						                                         GetAttachmentSocketNameAttributeClass())
						                                         ? InPropertyReflection->GetAttributeValue(
							                                         FReflectionRegistry::Get().
							                                         GetAttachmentSocketNameAttributeClass())
						                                         : FString{};

				                                         DefaultSubObjectInfoMap.FindOrAdd(InClass).Add(
					                                         DefaultSubObject);
			                                         }
		                                         }

		                                         if (InPropertyReflection->HasAttribute(
			                                         FReflectionRegistry::Get().
			                                         GetDefaultValueAttributeClass()))
		                                         {
			                                         const auto DefaultValue = InPropertyReflection->GetAttributeValue(
				                                         FReflectionRegistry::Get().
				                                         GetDefaultValueAttributeClass());

			                                         DefaultValueMap.FindOrAdd(InClass, {}).Emplace(
				                                         MakeTuple(InProperty, DefaultValue));
		                                         }
	                                         });

	if (IsDynamicBlueprintGeneratedClass(InClass))
	{
		if (DefaultSubObjectInfoMap.Contains(InClass))
		{
			DefaultSubObjectInfoMap[InClass].StableSort(
				[](const FDefaultSubObjectInfo& A, const FDefaultSubObjectInfo& B)
				{
					return A.bIsRootComponent;
				});
		}
	}
}

void FDynamicClassGenerator::GeneratorFunction(const FClassReflection* InClassReflection, UClass* InClass)
{
	FDynamicGeneratorCore::GeneratorFunction(InClassReflection, InClass,
	                                         [](FMethodReflection* InMethodReflection, const UFunction* InFunction)
	                                         {
	                                         });
}

void FDynamicClassGenerator::GeneratorInterface(const FClassReflection* InClassReflection, UClass* InClass)
{
	if (InClassReflection == nullptr || InClass == nullptr)
	{
		return;
	}

	for (const auto Interface : InClassReflection->GetInterfaces())
	{
		if (const auto InterfacePathName = Interface->GetPathName();
			!InterfacePathName.IsEmpty())
		{
			if (const auto InterfaceClass = LoadClass<UObject>(nullptr, *InterfacePathName))
			{
				if (InterfaceClass != UInterface::StaticClass())
				{
					InClass->Interfaces.Emplace(InterfaceClass, 0, true);
				}
			}
		}
	}
}

void FDynamicClassGenerator::ClassConstructor(const FObjectInitializer& InObjectInitializer)
{
	const auto Object = InObjectInitializer.GetObj();

	auto Class = InObjectInitializer.GetClass();

	while (Class != nullptr)
	{
		if (IsDynamicClass(Class))
		{
			for (TFieldIterator<FProperty> It(Class, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
			{
				It->InitializeValue(It->ContainerPtrToValuePtr<void>(Object));
			}

			if (auto DefaultValues = DefaultValueMap.Find(Class))
			{
				for (const auto& [Property, Value] : *DefaultValues)
				{
#if UE_F_PROPERTY_IMPORT_TEXT_DIRECT
					Property->ImportText_Direct(*Value,
					                            Property->ContainerPtrToValuePtr<uint8>(Object),
					                            Object,
					                            0);
#else
					Property->ImportText(*Value,
					                     Property->ContainerPtrToValuePtr<uint8>(Object),
					                     0,
					                     Object);
#endif
				}
			}
		}

		Class = Class->GetSuperClass();
	}

	Class = InObjectInitializer.GetClass();

	while (Class != nullptr)
	{
		if (Class->ClassConstructor != nullptr && !ClassConstructorSet.Contains(Class->ClassConstructor))
		{
			Class->ClassConstructor(InObjectInitializer);

			break;
		}

		Class = Class->GetSuperClass();
	}

	Class = InObjectInitializer.GetClass();

	if (Class->IsChildOf(AActor::StaticClass()))
	{
		if (DefaultSubObjectInfoMap.Contains(Class))
		{
			if (IsDynamicBlueprintGeneratedClass(Class))
			{
				const auto BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(Class);

				auto SimpleConstructionScript = BlueprintGeneratedClass->SimpleConstructionScript.Get();

				TArray<TPair<USCS_Node*, FName>> NodeParents;

				for (const auto& DefaultSubObjectInfo : DefaultSubObjectInfoMap[BlueprintGeneratedClass])
				{
					if (!IsValid(SimpleConstructionScript))
					{
						SimpleConstructionScript = NewObject<USimpleConstructionScript>(
							BlueprintGeneratedClass, NAME_None, RF_Transient);

						BlueprintGeneratedClass->SimpleConstructionScript = SimpleConstructionScript;
					}

					auto PropertyClass = DefaultSubObjectInfo.Property->PropertyClass;

					const auto Name = FName(DefaultSubObjectInfo.Property->GetName());

					auto Node = SimpleConstructionScript->FindSCSNode(Name);

					if (!Node)
					{
						Node = NewNode(SimpleConstructionScript, BlueprintGeneratedClass, PropertyClass, Name);
					}
					else if (PropertyClass != Node->ComponentClass)
					{
#if WITH_EDITOR
						RemoveComponentTemplate(BlueprintGeneratedClass, Node);
#endif

						NewComponentTemplate(Node, BlueprintGeneratedClass, PropertyClass, Name);
					}

					auto Parent = DefaultSubObjectInfo.Parent.IsEmpty()
						              ? NAME_None
						              : FName(DefaultSubObjectInfo.Parent);

					const auto bHasParent = Parent != NAME_None;

					Node->AttachToName = bHasParent ? FName(DefaultSubObjectInfo.Socket) : NAME_None;

					if (bHasParent)
					{
						NodeParents.Emplace(Node, Parent);
					}
				}

				for (const auto& [Node, Parent] : NodeParents)
				{
					auto ParentNode = SimpleConstructionScript->FindSCSNode(Parent);

					if (!ParentNode)
					{
						ParentNode = SimpleConstructionScript->GetRootNodes()[0];
					}

					if (ParentNode->ChildNodes.Contains(Node))
					{
						continue;
					}

					ParentNode->AddChildNode(Node);

					Node->bIsParentComponentNative = false;

					Node->ParentComponentOrVariableName = Parent;

					Node->ParentComponentOwnerClassName = BlueprintGeneratedClass->SimpleConstructionScript->GetFName();

					for (const auto ExistingNode : SimpleConstructionScript->GetAllNodes())
					{
						if (ExistingNode != Node &&
							ExistingNode->ChildNodes.Contains(Node) &&
							ExistingNode->GetVariableName() != Parent)
						{
							ExistingNode->RemoveChildNode(Node, false);

							break;
						}
					}
				}
			}
		}
	}
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(const FString& InName)
{
	return InName.EndsWith(TEXT("_C"));
}

void FDynamicClassGenerator::NewComponentTemplate(USCS_Node* InNode, UObject* InOuter, UClass* InClass,
                                                  const FName& InName)
{
	if (InNode != nullptr)
	{
		auto ComponentTemplate = NewObject<UActorComponent>(GetTransientPackage(), InClass, NAME_None,
		                                                    RF_ArchetypeObject | RF_Public);

		const auto Name = InName.ToString() + USimpleConstructionScript::ComponentTemplateNameSuffix;

		auto ExistingObject = FindObject<UObject>(InOuter, *Name);

		while (ExistingObject)
		{
			ExistingObject->Rename(nullptr, GetTransientPackage(), REN_DoNotDirty | REN_DontCreateRedirectors);

			ExistingObject = FindObject<UObject>(InOuter, *Name);
		}

		ComponentTemplate->Rename(*Name, InOuter, REN_DoNotDirty | REN_DontCreateRedirectors);

		InNode->ComponentClass = InClass;

		InNode->ComponentTemplate = ComponentTemplate;
	}
}

#if WITH_EDITOR
void FDynamicClassGenerator::RemoveComponentTemplate(const UBlueprintGeneratedClass* InBlueprintGeneratedClass,
                                                     const USCS_Node* InNode)
{
	const FComponentKey ComponentKey(InNode);

	TArray<UClass*> DerivedClasses;

	GetDerivedClasses(InBlueprintGeneratedClass, DerivedClasses);

	for (const auto Class : DerivedClasses)
	{
		if (const auto Blueprint = Cast<UBlueprint>(Class->ClassGeneratedBy))
		{
			if (const auto ComponentTemplate = Blueprint->InheritableComponentHandler->GetOverridenComponentTemplate(
				ComponentKey))
			{
				ComponentTemplate->Rename(nullptr, GetTransientPackage(), REN_DoNotDirty | REN_DontCreateRedirectors);

				ComponentTemplate->ClearFlags(RF_Standalone);

				ComponentTemplate->RemoveFromRoot();

				Blueprint->InheritableComponentHandler->RemoveOverridenComponentTemplate(ComponentKey);
			}
		}
	}
}
#endif

USCS_Node* FDynamicClassGenerator::NewNode(USimpleConstructionScript* InSimpleConstructionScript, UObject* InOuter,
                                           UClass* InClass, const FName& InName)
{
	const auto Node = NewObject<USCS_Node>(InSimpleConstructionScript,
	                                       MakeUniqueObjectName(InSimpleConstructionScript, USCS_Node::StaticClass()),
	                                       RF_Transient);

	Node->SetVariableName(InName, false);

	Node->VariableGuid = FGuid::NewGuid();

	NewComponentTemplate(Node, InOuter, InClass, InName);

	InSimpleConstructionScript->AddNode(Node);

	return Node;
}
