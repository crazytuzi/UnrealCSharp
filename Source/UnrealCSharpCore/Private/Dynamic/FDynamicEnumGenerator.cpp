#include "Dynamic/FDynamicEnumGenerator.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Domain/FMonoDomain.h"
#include "Template/TGetArrayLength.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#endif

TMap<FString, UEnum*> FDynamicEnumGenerator::DynamicEnumMap;

TSet<UEnum*> FDynamicEnumGenerator::DynamicEnumSet;

void FDynamicEnumGenerator::Generator()
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_ENUM_ATTRIBUTE);

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
void FDynamicEnumGenerator::CodeAnalysisGenerator()
{
	static FString CSharpEnum = TEXT("CSharpEnum");

	auto EnumNames = FDynamicGeneratorCore::GetDynamic(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *CSharpEnum),
		CSharpEnum
	);

	for (const auto& EnumName : EnumNames)
	{
		if (!DynamicEnumMap.Contains(EnumName))
		{
			DynamicEnumMap.Add(
				EnumName,
				GeneratorCSharpEnum(FDynamicGeneratorCore::GetOuter(), EnumName));
		}
	}
}
#endif

void FDynamicEnumGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

	UEnum* Enum{};

	if (DynamicEnumMap.Contains(ClassName))
	{
		Enum = DynamicEnumMap[ClassName];
	}
	else
	{
		Enum = GeneratorCSharpEnum(Outer, ClassName);

		DynamicEnumMap.Add(ClassName, Enum);
	}

	// @TODO
#if WITH_EDITOR
	Enum->SetMetaData(*FBlueprintMetadata::MD_AllowableBlueprintVariableType.ToString(), TEXT("true"));
#endif

#if WITH_EDITOR
	GeneratorMetaData(InMonoClass, Enum);
#endif

	GeneratorEnumerator(InMonoClass, Enum);

#if WITH_EDITOR
	if (bReInstance == true)
	{
		ReInstance(Enum);
	}
#endif
}

bool FDynamicEnumGenerator::IsDynamicEnum(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_ENUM_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

bool FDynamicEnumGenerator::IsDynamicEnum(const UEnum* InEnum)
{
	return DynamicEnumSet.Contains(InEnum);
}

UEnum* FDynamicEnumGenerator::GeneratorCSharpEnum(UPackage* InOuter, const FString& InName)
{
	const auto Enum = NewObject<UEnum>(InOuter, *InName, RF_Public);

	Enum->SetInternalFlags(EInternalObjectFlags::Native);

	Enum->AddToRoot();

	DynamicEnumSet.Add(Enum);

	return Enum;
}

#if WITH_EDITOR
void FDynamicEnumGenerator::ReInstance(UEnum* InEnum)
{
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InEnum);

		ActionDatabase.RefreshAssetActions(InEnum);
	}

	FDynamicGeneratorCore::ReloadPackages(
		[InEnum](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
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
		});
}

void FDynamicEnumGenerator::GeneratorMetaData(MonoClass* InMonoClass, UEnum* InEnum)
{
	if (InMonoClass == nullptr || InEnum == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_ENUM_ATTRIBUTE);

	if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass))
	{
		if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
		{
			FDynamicGeneratorCore::SetMetaData(InEnum, Attrs);
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
