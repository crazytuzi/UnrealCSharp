#include "Mixin/FMixinStructGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Mixin/FMixinGeneratorCore.h"
#include "Template/TGetArrayLength.inl"
#if WITH_EDITOR
#include "Kismet2/BlueprintEditorUtils.h"
#endif

void FMixinStructGenerator::Generator()
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_STRUCT_ATTRIBUTE);

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
void FMixinStructGenerator::CodeAnalysisGenerator()
{
	auto CSharpScriptStruct = FMixinGeneratorCore::GetMixin(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *UCSharpScriptStruct::StaticClass()->GetName()),
		UCSharpScriptStruct::StaticClass()->GetName()
	);

	for (const auto& StructName : CSharpScriptStruct)
	{
		const auto Outer = FMixinGeneratorCore::GetOuter();

		const auto ScriptStruct = LoadObject<UCSharpScriptStruct>(Outer, *StructName);

		if (ScriptStruct == nullptr)
		{
			GeneratorCSharpScriptStruct(Outer, StructName);
		}
	}
}
#endif

void FMixinStructGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FMonoDomain::Class_Get_Name(InMonoClass);

	const auto Outer = FMixinGeneratorCore::GetOuter();

#if WITH_EDITOR
	auto bExisted = false;

	TArray<UBlueprint*> Blueprints;
#endif

	auto ScriptStruct = LoadObject<UCSharpScriptStruct>(Outer, *FString(ClassName));

	if (ScriptStruct != nullptr)
	{
#if WITH_EDITOR
		if (bReInstance)
		{
			bExisted = true;

			for (TObjectIterator<UBlueprintGeneratedClass> ClassIterator; ClassIterator; ++ClassIterator)
			{
				for (TFieldIterator<FProperty> It(*ClassIterator, EFieldIteratorFlags::ExcludeSuper,
				                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
				{
					if (const auto StructProperty = CastField<FStructProperty>(*It))
					{
						if (StructProperty->Struct == ScriptStruct)
						{
							if (const auto ClassGeneratedBy = Cast<UBlueprint>(ClassIterator->ClassGeneratedBy))
							{
								Blueprints.Add(ClassGeneratedBy);
							}

							break;
						}
					}
				}
			}
		}
#endif

		ScriptStruct->DestroyChildPropertiesAndResetPropertyLinks();
	}
	else
	{
		ScriptStruct = GeneratorCSharpScriptStruct(Outer, ClassName);
	}

	if (const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass))
	{
		if (ParentMonoClass != FMonoDomain::Get_Object_Class())
		{
			if (const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass))
			{
				if (const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType))
				{
					const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

					if (const auto ParentClass = LoadObject<UScriptStruct>(nullptr, *ParentPathName))
					{
						ScriptStruct->SetSuperStruct(ParentClass);
					}
				}
			}
		}
	}

	// @TODO
#if WITH_EDITOR
	ScriptStruct->SetMetaData(FBlueprintMetadata::MD_AllowableBlueprintVariableType, TEXT("true"));
#endif

	BeginGenerator(ScriptStruct);

	GeneratorProperty(InMonoClass, ScriptStruct);

	EndGenerator(ScriptStruct);

#if WITH_EDITOR
	if (bReInstance == true && bExisted == true)
	{
		ReInstance(ScriptStruct, Blueprints);
	}
#endif
}

bool FMixinStructGenerator::IsMixinStruct(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_STRUCT_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

void FMixinStructGenerator::BeginGenerator(UScriptStruct* InScriptStruct)
{
}

void FMixinStructGenerator::EndGenerator(UScriptStruct* InScriptStruct)
{
	InScriptStruct->Bind();

	InScriptStruct->StaticLink(true);

	if (InScriptStruct->GetPropertiesSize() == 0)
	{
		InScriptStruct->SetPropertiesSize(1);
	}

	InScriptStruct->StructFlags = STRUCT_Native;
}

UCSharpScriptStruct* FMixinStructGenerator::GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName)
{
	const auto ScriptStruct = NewObject<UCSharpScriptStruct>(InOuter, *InName, RF_Public);

	ScriptStruct->AddToRoot();

	BeginGenerator(ScriptStruct);

	EndGenerator(ScriptStruct);

	return ScriptStruct;
}

#if WITH_EDITOR
void FMixinStructGenerator::ReInstance(UScriptStruct* InScriptStruct, const TArray<UBlueprint*>& InBlueprints)
{
	for (const auto Blueprint : InBlueprints)
	{
		if (const auto SkeletonGeneratedClass = Cast<UBlueprintGeneratedClass>(
			Blueprint->SkeletonGeneratedClass))
		{
			SkeletonGeneratedClass->Bind();

			SkeletonGeneratedClass->StaticLink(true);
		}

		FBlueprintEditorUtils::RefreshExternalBlueprintDependencyNodes(Blueprint, InScriptStruct);
	}
}
#endif

void FMixinStructGenerator::GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct)
{
	if (InMonoClass == nullptr || InScriptStruct == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_PROPERTY_ATTRIBUTE);

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

				FMixinGeneratorCore::SetPropertyFlags(CppProperty, Attrs);

				InScriptStruct->AddCppProperty(CppProperty);
			}
		}
	}
}
