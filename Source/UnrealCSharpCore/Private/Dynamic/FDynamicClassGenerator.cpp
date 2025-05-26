#include "Dynamic/FDynamicClassGenerator.h"
#include "Engine/SCS_Node.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/InheritableComponentHandler.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Dynamic/FDynamicGenerator.h"
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

void FDynamicClassGenerator::Generator()
{
	FDynamicGeneratorCore::Generator(CLASS_U_CLASS_ATTRIBUTE,
	                                 [](MonoClass* InMonoClass)
	                                 {
		                                 if (InMonoClass == nullptr)
		                                 {
			                                 return;
		                                 }

		                                 if (!FMonoDomain::Type_Is_Class(FMonoDomain::Class_Get_Type(InMonoClass)))
		                                 {
			                                 return;
		                                 }

		                                 const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

		                                 auto Node = FDynamicDependencyGraph::FNode(ClassName, [InMonoClass]()
		                                 {
			                                 Generator(InMonoClass, EDynamicClassGeneratorType::DependencyGraph);
		                                 });

		                                 if (const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass))
		                                 {
			                                 if (FDynamicGeneratorCore::ClassHasAttr(
				                                 ParentMonoClass, CLASS_U_CLASS_ATTRIBUTE))
			                                 {
				                                 const auto ParentClassName = FString(
					                                 FMonoDomain::Class_Get_Name(ParentMonoClass));

				                                 Node.Dependency(FDynamicDependencyGraph::FDependency{
					                                 ParentClassName, false
				                                 });
			                                 }
		                                 }

		                                 FDynamicGeneratorCore::GeneratorProperty(InMonoClass, Node);

		                                 FDynamicGeneratorCore::GeneratorFunction(InMonoClass, Node);

		                                 FDynamicGeneratorCore::GeneratorInterface(InMonoClass, Node);

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

bool FDynamicClassGenerator::IsDynamicClass(MonoClass* InMonoClass)
{
	return FDynamicGeneratorCore::IsDynamic(InMonoClass, CLASS_U_CLASS_ATTRIBUTE);
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

void FDynamicClassGenerator::Generator(MonoClass* InMonoClass,
                                       const EDynamicClassGeneratorType InDynamicClassGeneratorType)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	if (!FMonoDomain::Type_Is_Class(FMonoDomain::Class_Get_Type(InMonoClass)))
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto ClassNamespace = FString(FMonoDomain::Class_Get_Namespace(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

	const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass);

	const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass);

	const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType);

	const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

	const auto ParentClass = LoadClass<UObject>(nullptr, *ParentPathName);

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
		                                         [InMonoClass](UClass* InClass)
		                                         {
			                                         ProcessGenerator(InMonoClass, InClass);
		                                         });
	}
	else
	{
		Class = GeneratorClass(Outer, ClassNamespace, ClassName, ParentClass,
		                       [InMonoClass](UClass* InClass)
		                       {
			                       ProcessGenerator(InMonoClass, InClass);
		                       });
	}

#if WITH_EDITOR
	if (OldClass != nullptr)
	{
		ReInstance(OldClass, Class);
	}

	if (InDynamicClassGeneratorType == EDynamicClassGeneratorType::FileChange)
	{
		if (const auto AssetRegistryModule = FModuleManager::GetModulePtr<FAssetRegistryModule>(TEXT("AssetRegistry")))
		{
			AssetRegistryModule->Get().OnFilesLoaded().Broadcast();
		}
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

UClass* FDynamicClassGenerator::GetDynamicClass(MonoClass* InMonoClass)
{
	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto FoundDynamicClass = DynamicClassMap.Find(ClassName);

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

#if UE_CLASS_ADD_REFERENCED_OBJECTS
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

void FDynamicClassGenerator::ProcessGenerator(MonoClass* InMonoClass, UClass* InClass)
{
	FDynamicGeneratorCore::SetFlags(InClass, FMonoDomain::Custom_Attrs_From_Class(InMonoClass));

	GeneratorProperty(InMonoClass, InClass);

	GeneratorFunction(InMonoClass, InClass);

	GeneratorInterface(InMonoClass, InClass);
}

void FDynamicClassGenerator::EndGenerator(UClass* InClass)
{
	InClass->ClearInternalFlags(EInternalObjectFlags::Native);

	InClass->Bind();

	InClass->StaticLink(true);

	InClass->AssembleReferenceTokenStream();

	InClass->ClassDefaultObject = StaticAllocateObject(InClass, InClass->GetOuter(),
	                                                   *InClass->GetDefaultObjectName().ToString(),
	                                                   RF_Public | RF_ClassDefaultObject | RF_ArchetypeObject,
	                                                   EInternalObjectFlags::None,
	                                                   false);

	(*InClass->ClassConstructor)(FObjectInitializer(InClass->ClassDefaultObject,
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
	NotifyRegistrationEvent(*InClass->ClassDefaultObject->GetPackage()->GetName(),
	                        *InClass->ClassDefaultObject->GetName(),
	                        ENotifyRegistrationType::NRT_ClassCDO,
	                        ENotifyRegistrationPhase::NRP_Finished,
	                        nullptr,
	                        false,
	                        InClass->ClassDefaultObject);


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

#if UE_REPLACE_INSTANCES_OF_CLASS_F_REPLACE_INSTANCES_OF_CLASS_PARAMETERS
	FReplaceInstancesOfClassParameters ReplaceInstancesOfClassParameters;

	ReplaceInstancesOfClassParameters.OriginalCDO = InOldClass->ClassDefaultObject;

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

	InOldClass->ClassDefaultObject = nullptr;

	(void)InOldClass->GetDefaultObject(true);

	for (const auto BlueprintGeneratedClass : BlueprintGeneratedClasses)
	{
		if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
		{
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

void FDynamicClassGenerator::GeneratorProperty(MonoClass* InMonoClass, UClass* InClass)
{
	FDynamicGeneratorCore::GeneratorProperty(InMonoClass, InClass,
	                                         [InClass](const MonoProperty* InMonoProperty,
	                                                   MonoCustomAttrInfo* InMonoCustomAttrInfo,
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
			                                         if (FDynamicGeneratorCore::AttrsHasAttr(
				                                         InMonoCustomAttrInfo, CLASS_DEFAULT_SUB_OBJECT_ATTRIBUTE))
			                                         {
				                                         FDefaultSubObjectInfo DefaultSubObject;

				                                         DefaultSubObject.Property = CastField<FObjectProperty>(
					                                         InProperty);

				                                         DefaultSubObject.bIsRootComponent =
					                                         FDynamicGeneratorCore::AttrsHasAttr(
						                                         InMonoCustomAttrInfo, CLASS_ROOT_COMPONENT_ATTRIBUTE);

				                                         DefaultSubObject.Parent = FDynamicGeneratorCore::AttrsHasAttr(
						                                         InMonoCustomAttrInfo,
						                                         CLASS_ATTACHMENT_PARENT_ATTRIBUTE)
						                                         ? FDynamicGeneratorCore::AttrGetValue(
							                                         InMonoCustomAttrInfo,
							                                         CLASS_ATTACHMENT_PARENT_ATTRIBUTE)
						                                         : FString{};

				                                         DefaultSubObject.Socket = FDynamicGeneratorCore::AttrsHasAttr(
						                                         InMonoCustomAttrInfo,
						                                         CLASS_ATTACHMENT_SOCKET_NAME_ATTRIBUTE)
						                                         ? FDynamicGeneratorCore::AttrGetValue(
							                                         InMonoCustomAttrInfo,
							                                         CLASS_ATTACHMENT_SOCKET_NAME_ATTRIBUTE)
						                                         : FString{};

				                                         DefaultSubObjectInfoMap.FindOrAdd(InClass).Add(
					                                         DefaultSubObject);
			                                         }
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

void FDynamicClassGenerator::GeneratorFunction(MonoClass* InMonoClass, UClass* InClass)
{
	FDynamicGeneratorCore::GeneratorFunction(InMonoClass, InClass,
	                                         [](const UFunction* InFunction)
	                                         {
	                                         });
}

void FDynamicClassGenerator::GeneratorInterface(MonoClass* InMonoClass, UClass* InClass)
{
	if (InMonoClass == nullptr || InClass == nullptr)
	{
		return;
	}

	void* Iterator = nullptr;

	while (const auto Interface = FMonoDomain::Class_Get_Interfaces(InMonoClass, &Iterator))
	{
		const auto InterfaceMonoType = FMonoDomain::Class_Get_Type(Interface);

		const auto InterfaceMonoReflectionType = FMonoDomain::Type_Get_Object(InterfaceMonoType);

		if (const auto InterfacePathName = FTypeBridge::GetPathName(InterfaceMonoReflectionType);
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
