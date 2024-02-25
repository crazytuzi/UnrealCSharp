#include "Dynamic/FDynamicStructGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Template/TGetArrayLength.inl"
#if WITH_EDITOR
#include "K2Node_StructOperation.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "BlueprintActionDatabase.h"
#endif
#include "UEVersion.h"

TMap<FString, UScriptStruct*> FDynamicStructGenerator::DynamicStructMap;

TSet<UScriptStruct*> FDynamicStructGenerator::DynamicStructSet;

void FDynamicStructGenerator::Generator()
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_STRUCT_ATTRIBUTE);

	const auto AttributeMonoType = FMonoDomain::Class_Get_Type(AttributeMonoClass);

	const auto AttributeMonoReflectionType = FMonoDomain::Type_Get_Object(AttributeMonoType);

	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	void* InParams[2] = {
		AttributeMonoReflectionType,
		FMonoDomain::GCHandle_Get_Target_V2(FMonoDomain::AssemblyGCHandles[1])
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

		Generator(Class);
	}
}

#if WITH_EDITOR
void FDynamicStructGenerator::CodeAnalysisGenerator()
{
	static FString CSharpScriptStruct = TEXT("CSharpScriptStruct");

	auto StructNames = FDynamicGeneratorCore::GetDynamic(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *CSharpScriptStruct),
		CSharpScriptStruct
	);

	for (const auto& StructName : StructNames)
	{
		if (!DynamicStructMap.Contains(StructName))
		{
			GeneratorCSharpScriptStruct(FDynamicGeneratorCore::GetOuter(), StructName, nullptr);
		}
	}
}
#endif

void FDynamicStructGenerator::Generator(MonoClass* InMonoClass)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

#if WITH_EDITOR
	UScriptStruct* OldScriptStruct{};

	if (DynamicStructMap.Contains(ClassName))
	{
		OldScriptStruct = DynamicStructMap[ClassName];

		DynamicStructSet.Remove(OldScriptStruct);

		OldScriptStruct->Rename(
			*MakeUniqueObjectName(
				OldScriptStruct->GetOuter(),
				OldScriptStruct->GetClass())
			.ToString(),
			nullptr,
			REN_DontCreateRedirectors);
	}
#endif

	UScriptStruct* ParentClass{};

	if (const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass))
	{
		if (ParentMonoClass != FMonoDomain::Get_Object_Class())
		{
			if (const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass))
			{
				if (const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType))
				{
					const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

					ParentClass = LoadObject<UScriptStruct>(nullptr, *ParentPathName);
				}
			}
		}
	}

	const auto ScriptStruct = GeneratorCSharpScriptStruct(Outer, ClassName, ParentClass,
	                                                      [InMonoClass](UScriptStruct* InScriptStruct)
	                                                      {
		                                                      ProcessGenerator(InMonoClass, InScriptStruct);
	                                                      });

#if WITH_EDITOR
	if (OldScriptStruct != nullptr)
	{
		ReInstance(OldScriptStruct, ScriptStruct);
	}
#endif
}

bool FDynamicStructGenerator::IsDynamicStruct(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_STRUCT_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

bool FDynamicStructGenerator::IsDynamicStruct(const UScriptStruct* InScriptStruct)
{
	return DynamicStructSet.Contains(InScriptStruct);
}

void FDynamicStructGenerator::BeginGenerator(UScriptStruct* InScriptStruct, UScriptStruct* InParentScriptStruct)
{
	if (InParentScriptStruct != nullptr)
	{
		InScriptStruct->SetSuperStruct(InParentScriptStruct);
	}
}

void FDynamicStructGenerator::ProcessGenerator(MonoClass* InMonoClass, UScriptStruct* InScriptStruct)
{
#if WITH_EDITOR
	GeneratorMetaData(InMonoClass, InScriptStruct);
#endif

	GeneratorProperty(InMonoClass, InScriptStruct);
}

void FDynamicStructGenerator::EndGenerator(UScriptStruct* InScriptStruct)
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

void FDynamicStructGenerator::GeneratorScriptStruct(const FString& InName, UScriptStruct* InScriptStruct,
                                                    UScriptStruct* InParentScriptStruct,
                                                    const TFunction<void(UScriptStruct*)>& InProcessGenerator)
{
	DynamicStructMap.Add(InName, InScriptStruct);

	DynamicStructSet.Add(InScriptStruct);

	BeginGenerator(InScriptStruct, InParentScriptStruct);

	InProcessGenerator(InScriptStruct);

	EndGenerator(InScriptStruct);
}

UScriptStruct* FDynamicStructGenerator::GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName,
                                                                    UScriptStruct* InParentScriptStruct)
{
	return GeneratorCSharpScriptStruct(InOuter, InName, InParentScriptStruct,
	                                   [](UScriptStruct*)
	                                   {
	                                   });
}

UScriptStruct* FDynamicStructGenerator::GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName,
                                                                    UScriptStruct* InParentScriptStruct,
                                                                    const TFunction<void(UScriptStruct*)>&
                                                                    InProcessGenerator)
{
	const auto ScriptStruct = NewObject<UScriptStruct>(InOuter, *InName.RightChop(1), RF_Public);

	ScriptStruct->AddToRoot();

	GeneratorScriptStruct(InName, ScriptStruct, InParentScriptStruct, InProcessGenerator);

	return ScriptStruct;
}

#if WITH_EDITOR
void FDynamicStructGenerator::ReInstance(UScriptStruct* InOldScriptStruct, UScriptStruct* InNewScriptStruct)
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
		const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy);

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

		for (const auto& Variable : Blueprint->NewVariables)
		{
			if (Variable.VarType.PinSubCategoryObject == InOldScriptStruct)
			{
				auto NewVarType = Variable.VarType;

				NewVarType.PinSubCategoryObject = InNewScriptStruct;

				FBlueprintEditorUtils::ChangeMemberVariableType(Blueprint, Variable.VarName, NewVarType);

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

	for (const auto DynamicClass : DynamicClasses)
	{
		if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(DynamicClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(DynamicClass)))
		{
			FDynamicClassGenerator::Generator(FoundMonoClass);
		}
	}

	InOldScriptStruct->RemoveFromRoot();

	InOldScriptStruct->MarkAsGarbage();
}

void FDynamicStructGenerator::GeneratorMetaData(MonoClass* InMonoClass, UScriptStruct* InScriptStruct)
{
	if (InMonoClass == nullptr || InScriptStruct == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_STRUCT_ATTRIBUTE);

	if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass))
	{
		if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
		{
			FDynamicGeneratorCore::SetMetaData(InScriptStruct, Attrs);
		}
	}
}
#endif

void FDynamicStructGenerator::GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct)
{
	if (InMonoClass == nullptr || InScriptStruct == nullptr)
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

				const auto CppProperty = FTypeBridge::Factory(ReflectionType, InScriptStruct, PropertyName,
				                                              EObjectFlags::RF_Public);

				FDynamicGeneratorCore::SetPropertyFlags(CppProperty, Attrs);

				InScriptStruct->AddCppProperty(CppProperty);
			}
		}
	}
}
