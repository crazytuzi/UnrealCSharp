#include "Dynamic/FDynamicStructGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Template/TGetArrayLength.inl"

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
			DynamicStructMap.Add(
				StructName,
				GeneratorCSharpScriptStruct(FDynamicGeneratorCore::GetOuter(), StructName.RightChop(1)));
		}
	}
}
#endif

void FDynamicStructGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

	UScriptStruct* ScriptStruct{};

	if (DynamicStructMap.Contains(ClassName))
	{
		ScriptStruct = DynamicStructMap[ClassName];

		ScriptStruct->DestroyChildPropertiesAndResetPropertyLinks();
	}
	else
	{
		ScriptStruct = GeneratorCSharpScriptStruct(Outer, ClassName.RightChop(1));

		DynamicStructMap.Add(ClassName, ScriptStruct);
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

#if WITH_EDITOR
	GeneratorMetaData(InMonoClass, ScriptStruct);
#endif

	GeneratorProperty(InMonoClass, ScriptStruct);

	EndGenerator(ScriptStruct);

#if WITH_EDITOR
	if (bReInstance == true)
	{
		ReInstance(ScriptStruct);
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

void FDynamicStructGenerator::BeginGenerator(UScriptStruct* InScriptStruct)
{
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
}

UScriptStruct* FDynamicStructGenerator::GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName)
{
	const auto ScriptStruct = NewObject<UScriptStruct>(InOuter, *InName, RF_Public);

	ScriptStruct->AddToRoot();

	BeginGenerator(ScriptStruct);

	EndGenerator(ScriptStruct);

	DynamicStructSet.Add(ScriptStruct);

	return ScriptStruct;
}

#if WITH_EDITOR
void FDynamicStructGenerator::ReInstance(UScriptStruct* InScriptStruct)
{
	FDynamicGeneratorCore::ReloadPackages(
		[InScriptStruct](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			for (TFieldIterator<FProperty> It(*InBlueprintGeneratedClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
			{
				if (const auto StructProperty = CastField<FStructProperty>(*It))
				{
					if (StructProperty->Struct == InScriptStruct)
					{
						return true;
					}
				}
			}

			return false;
		});
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
