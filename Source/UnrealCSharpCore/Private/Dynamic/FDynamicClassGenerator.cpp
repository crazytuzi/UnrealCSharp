#include "Dynamic/FDynamicClassGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Dynamic/FDynamicGenerator.h"
#endif
#include "UEVersion.h"

TSet<UClass::ClassConstructorType> FDynamicClassGenerator::ClassConstructorSet
{
	&FDynamicClassGenerator::ClassConstructor
};

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
			                                 Generator(InMonoClass);
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

		                                 FDynamicGeneratorCore::AddNode(Node);
	                                 });
}

#if WITH_EDITOR
void FDynamicClassGenerator::CodeAnalysisGenerator()
{
	FDynamicGeneratorCore::CodeAnalysisGenerator(TEXT("DynamicClass"),
	                                             [](const FString& InName)
	                                             {
		                                             if (!DynamicClassMap.Contains(InName))
		                                             {
			                                             if (IsDynamicBlueprintGeneratedClass(InName))
			                                             {
				                                             GeneratorBlueprintGeneratedClass(
					                                             FDynamicGeneratorCore::GetOuter(),
					                                             InName,
					                                             AActor::StaticClass());
			                                             }
			                                             else
			                                             {
				                                             GeneratorClass(
					                                             FDynamicGeneratorCore::GetOuter(),
					                                             InName,
					                                             AActor::StaticClass());
			                                             }
		                                             }
	                                             });
}

bool FDynamicClassGenerator::IsDynamicClass(MonoClass* InMonoClass)
{
	return FDynamicGeneratorCore::IsDynamic(InMonoClass, CLASS_U_CLASS_ATTRIBUTE);
}

MonoClass* FDynamicClassGenerator::GetMonoClass(const FString& InName)
{
	static auto A = ACTOR_PREFIX;

	static auto U = OBJECT_PREFIX;

	if (IsDynamicBlueprintGeneratedClass(InName))
	{
		return FMonoDomain::Class_From_Name(FDynamicGeneratorCore::GetClassNameSpace(), InName);
	}

	if (const auto Class = FMonoDomain::Class_From_Name(FDynamicGeneratorCore::GetClassNameSpace(), A + InName))
	{
		return Class;
	}

	if (const auto Class = FMonoDomain::Class_From_Name(FDynamicGeneratorCore::GetClassNameSpace(), U + InName))
	{
		return Class;
	}

	return nullptr;
}

void FDynamicClassGenerator::OnPrePIEEnded()
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
#endif

void FDynamicClassGenerator::Generator(MonoClass* InMonoClass)
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
		Class = GeneratorBlueprintGeneratedClass(Outer, ClassName, ParentClass,
		                                         [InMonoClass](UClass* InClass)
		                                         {
			                                         ProcessGenerator(InMonoClass, InClass);
		                                         });
	}
	else
	{
		Class = GeneratorClass(Outer, ClassName, ParentClass,
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
#endif

	FDynamicGeneratorCore::Completed(ClassName);
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
#if WITH_EDITOR
	GeneratorMetaData(InMonoClass, InClass);
#endif

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

UClass* FDynamicClassGenerator::GeneratorClass(UPackage* InOuter, const FString& InName, UClass* InParentClass)
{
	return GeneratorClass(InOuter, InName, InParentClass,
	                      [](UClass* InClass)
	                      {
	                      });
}

UClass* FDynamicClassGenerator::GeneratorClass(UPackage* InOuter, const FString& InName, UClass* InParentClass,
                                               const TFunction<void(UClass*)>& InProcessGenerator)
{
	const auto Class = NewObject<UClass>(InOuter, *InName.RightChop(1), RF_Public);

	Class->AddToRoot();

	GeneratorClass(InName, Class, InParentClass, InProcessGenerator);

	return Class;
}

UBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorBlueprintGeneratedClass(UPackage* InOuter,
	const FString& InName, UClass* InParentClass)
{
	return GeneratorBlueprintGeneratedClass(InOuter, InName, InParentClass,
	                                        [](UClass* InClass)
	                                        {
	                                        });
}

UBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorBlueprintGeneratedClass(UPackage* InOuter,
	const FString& InName, UClass* InParentClass, const TFunction<void(UClass*)>& InProcessGenerator)
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

	GeneratorClass(InName, Class, InParentClass, InProcessGenerator);

	return Class;
}

#if WITH_EDITOR
void FDynamicClassGenerator::ReInstance(UClass* InOldClass, UClass* InNewClass)
{
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

void FDynamicClassGenerator::GeneratorMetaData(MonoClass* InMonoClass, UClass* InClass)
{
	FDynamicGeneratorCore::SetMetaData(InMonoClass, InClass, CLASS_U_CLASS_ATTRIBUTE);
}
#endif

void FDynamicClassGenerator::GeneratorProperty(MonoClass* InMonoClass, UClass* InClass)
{
	FDynamicGeneratorCore::GeneratorProperty(InMonoClass, InClass,
	                                         [InClass](const FProperty* InProperty)
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
	                                         });
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

	auto SuperClass = InObjectInitializer.GetClass();

	while (SuperClass != nullptr)
	{
		if (IsDynamicClass(SuperClass))
		{
			for (TFieldIterator<FProperty> It(SuperClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
			{
				It->InitializeValue(It->ContainerPtrToValuePtr<void>(Object));
			}
		}

		SuperClass = SuperClass->GetSuperClass();
	}

	SuperClass = InObjectInitializer.GetClass();

	while (SuperClass != nullptr)
	{
		if (SuperClass->ClassConstructor != nullptr && !ClassConstructorSet.Contains(SuperClass->ClassConstructor))
		{
			SuperClass->ClassConstructor(InObjectInitializer);

			break;
		}

		SuperClass = SuperClass->GetSuperClass();
	}
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(const FString& InName)
{
	return InName.EndsWith(TEXT("_C"));
}
