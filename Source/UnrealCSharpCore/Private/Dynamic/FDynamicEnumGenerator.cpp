#include "Dynamic/FDynamicEnumGenerator.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "Domain/FMonoDomain.h"
#include "Template/TGetArrayLength.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Dynamic/FDynamicBlueprintExtensionScope.h"
#endif
#include "UEVersion.h"

TMap<UEnum*, FString> FDynamicEnumGenerator::NamespaceMap;

TMap<FString, UEnum*> FDynamicEnumGenerator::DynamicEnumMap;

TSet<UEnum*> FDynamicEnumGenerator::DynamicEnumSet;

void FDynamicEnumGenerator::Generator()
{
	FDynamicGeneratorCore::Generator(CLASS_U_ENUM_ATTRIBUTE,
	                                 [](MonoClass* InMonoClass)
	                                 {
		                                 if (InMonoClass == nullptr)
		                                 {
			                                 return;
		                                 }

		                                 if (!FMonoDomain::Type_Is_Enum(FMonoDomain::Class_Get_Type(InMonoClass)))
		                                 {
			                                 return;
		                                 }

		                                 const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

		                                 const auto Node = FDynamicDependencyGraph::FNode(
			                                 ClassName, [InMonoClass]()
			                                 {
				                                 Generator(InMonoClass);
			                                 });

		                                 FDynamicGeneratorCore::AddNode(Node);
	                                 });
}

#if WITH_EDITOR
void FDynamicEnumGenerator::CodeAnalysisGenerator()
{
	FDynamicGeneratorCore::CodeAnalysisGenerator(DYNAMIC_ENUM,
	                                             [](const FString& InNameSpace, const FString& InName)
	                                             {
		                                             if (!DynamicEnumMap.Contains(InName))
		                                             {
			                                             GeneratorEnum(
				                                             FDynamicGeneratorCore::GetOuter(),
				                                             InNameSpace,
				                                             InName);
		                                             }
	                                             });
}

bool FDynamicEnumGenerator::IsDynamicEnum(MonoClass* InMonoClass)
{
	return FDynamicGeneratorCore::IsDynamic(InMonoClass, CLASS_U_ENUM_ATTRIBUTE);
}
#endif

void FDynamicEnumGenerator::Generator(MonoClass* InMonoClass)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	if (!FMonoDomain::Type_Is_Enum(FMonoDomain::Class_Get_Type(InMonoClass)))
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto ClassNamespace = FString(FMonoDomain::Class_Get_Namespace(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

#if WITH_EDITOR
	const UEnum* OldEnum{};
#endif

	UEnum* Enum{};

	if (DynamicEnumMap.Contains(ClassName))
	{
		Enum = DynamicEnumMap[ClassName];

		GeneratorEnum(ClassNamespace, ClassName, Enum, [InMonoClass](UEnum* InEnum)
		{
			ProcessGenerator(InMonoClass, InEnum);
		});

#if WITH_EDITOR
		OldEnum = Enum;
#endif
	}
	else
	{
		Enum = GeneratorEnum(Outer, ClassNamespace, ClassName,
		                     [InMonoClass](UEnum* InEnum)
		                     {
			                     ProcessGenerator(InMonoClass, InEnum);
		                     });
	}

#if WITH_EDITOR
	if (OldEnum != nullptr)
	{
		ReInstance(Enum);
	}
#endif

	FDynamicGeneratorCore::Completed(ClassName);
}

bool FDynamicEnumGenerator::IsDynamicEnum(const UEnum* InEnum)
{
	return DynamicEnumSet.Contains(InEnum);
}

FString FDynamicEnumGenerator::GetNameSpace(const UEnum* InEnum)
{
	const auto FoundNameSpace = NamespaceMap.Find(InEnum);

	return FoundNameSpace != nullptr ? *FoundNameSpace : FString{};
}

void FDynamicEnumGenerator::BeginGenerator(const UEnum* InEnum)
{
	InEnum->SetInternalFlags(EInternalObjectFlags::Native);
}

void FDynamicEnumGenerator::ProcessGenerator(MonoClass* InMonoClass, UEnum* InEnum)
{
	FDynamicGeneratorCore::SetFlags(InEnum, FMonoDomain::Custom_Attrs_From_Class(InMonoClass));

	GeneratorEnumerator(InMonoClass, InEnum);
}

void FDynamicEnumGenerator::EndGenerator(UEnum* InEnum)
{
#if WITH_EDITOR
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InEnum);

		ActionDatabase.RefreshAssetActions(InEnum);
	}
#endif

#if UE_NOTIFY_REGISTRATION_EVENT
#if !WITH_EDITOR
	NotifyRegistrationEvent(*InEnum->GetPackage()->GetName(),
	                        *InEnum->GetName(),
	                        ENotifyRegistrationType::NRT_Enum,
	                        ENotifyRegistrationPhase::NRP_Finished,
	                        nullptr,
	                        false,
	                        InEnum);
#endif
#endif
}

void FDynamicEnumGenerator::GeneratorEnum(const FString& InNameSpace, const FString& InName,
                                          UEnum* InEnum, const TFunction<void(UEnum*)>& InProcessGenerator)
{
	NamespaceMap.Add(InEnum, InNameSpace);

	DynamicEnumMap.Add(InName, InEnum);

	DynamicEnumSet.Add(InEnum);

	BeginGenerator(InEnum);

	InProcessGenerator(InEnum);

	EndGenerator(InEnum);
}

UEnum* FDynamicEnumGenerator::GeneratorEnum(UPackage* InOuter, const FString& InNameSpace, const FString& InName)
{
	return GeneratorEnum(InOuter, InNameSpace, InName,
	                     [](UEnum* InEnum)
	                     {
	                     });
}

UEnum* FDynamicEnumGenerator::GeneratorEnum(UPackage* InOuter, const FString& InNameSpace,
                                            const FString& InName, const TFunction<void(UEnum*)>& InProcessGenerator)
{
	const auto Enum = NewObject<UEnum>(InOuter, *InName, RF_Public);

	Enum->AddToRoot();

	GeneratorEnum(InNameSpace, InName, Enum, InProcessGenerator);

	return Enum;
}

#if WITH_EDITOR
void FDynamicEnumGenerator::ReInstance(UEnum* InEnum)
{
	TArray<UBlueprintGeneratedClass*> BlueprintGeneratedClasses;

	FDynamicGeneratorCore::IteratorObject<UBlueprintGeneratedClass>(
		[InEnum](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			if (InBlueprintGeneratedClass->IsNative())
			{
				return false;
			}

			for (TFieldIterator<FProperty> It(*InBlueprintGeneratedClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
			{
				if (const auto EnumProperty = CastField<FEnumProperty>(*It))
				{
					if (EnumProperty->GetEnum() == InEnum)
					{
						return true;
					}
				}
				else if (const auto ByteProperty = CastField<FByteProperty>(*It))
				{
					if (ByteProperty->Enum == InEnum)
					{
						return true;
					}
				}
			}

			return false;
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

			Blueprint->Modify();

			FBlueprintEditorUtils::RefreshAllNodes(Blueprint);

			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);

			constexpr auto BlueprintCompileOptions = EBlueprintCompileOptions::SkipGarbageCollection |
				EBlueprintCompileOptions::SkipSave;

			FKismetEditorUtilities::CompileBlueprint(Blueprint, BlueprintCompileOptions);
		}
	}
}
#endif

void FDynamicEnumGenerator::GeneratorEnumerator(MonoClass* InMonoClass, UEnum* InEnum)
{
	if (InMonoClass == nullptr || InEnum == nullptr)
	{
		return;
	}

	TArray<TPair<FName, int64>> InNames;

	void* Iterator = nullptr;

	while (const auto Field = FMonoDomain::Class_Get_Fields(InMonoClass, &Iterator))
	{
		static auto value__ = FName(TEXT("value__"));

		const auto FieldName = FMonoDomain::Field_Get_Name(Field);

		if (FieldName != value__)
		{
			auto FieldValue = *(int64*)FMonoDomain::Object_Unbox(
				FMonoDomain::Field_Get_Value_Object(FMonoDomain::Domain, Field, (MonoObject*)InMonoClass));

			InNames.Add({FieldName, FieldValue});
		}
	}

	InEnum->SetEnums(InNames, UEnum::ECppForm::Regular);
}
