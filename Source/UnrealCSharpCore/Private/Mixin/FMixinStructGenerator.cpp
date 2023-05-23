#include "Mixin/FMixinStructGenerator.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"
#include "Mixin/CSharpScriptStruct.h"
#include "Mixin/FMixinGeneratorCore.h"
#include "Template/TGetArrayLength.h"

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

void FMixinStructGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FMonoDomain::Class_Get_Name(InMonoClass);

	const auto Outer = UObject::StaticClass()->GetPackage();

	auto bExisted = false;

	TArray<FBPVariableDescriptionIndex> BPVariableDescriptionIndex;

	if (bReInstance)
	{
		if (const auto Class = LoadObject<UScriptStruct>(Outer, *FString(ClassName)))
		{
			bExisted = true;

			for (TObjectIterator<UBlueprintGeneratedClass> ClassIterator; ClassIterator; ++ClassIterator)
			{
				for (TFieldIterator<FProperty> It(*ClassIterator, EFieldIteratorFlags::ExcludeSuper,
				                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
				{
					if (const auto StructProperty = CastField<FStructProperty>(*It))
					{
						if (StructProperty->Struct == Class)
						{
							if (const auto ClassGeneratedBy = Cast<UBlueprint>(ClassIterator->ClassGeneratedBy))
							{
								for (auto Index = 0; Index < ClassGeneratedBy->NewVariables.Num(); ++Index)
								{
									if (ClassGeneratedBy->NewVariables[Index].VarType.PinSubCategoryObject == Class)
									{
										BPVariableDescriptionIndex.Add({ClassGeneratedBy, Index});
									}
								}
							}
						}
					}
				}
			}
		}
	}

	const auto Class = NewObject<UCSharpScriptStruct>(Outer, ClassName, RF_Public);

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
						Class->SetSuperStruct(ParentClass);
					}
				}
			}
		}
	}

	// @TODO
#if WITH_EDITOR
	Class->SetMetaData(FBlueprintMetadata::MD_AllowableBlueprintVariableType, TEXT("true"));
#endif

	GeneratorProperty(InMonoClass, Class);

	Class->Bind();

	Class->StaticLink(true);

	if (Class->GetPropertiesSize() == 0)
	{
		Class->SetPropertiesSize(1);
	}

	Class->StructFlags = STRUCT_Native;

	if (bReInstance == true && bExisted == true)
	{
		ReInstance(Class, BPVariableDescriptionIndex);
	}
}

bool FMixinStructGenerator::IsMixinStruct(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_STRUCT_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

void FMixinStructGenerator::ReInstance(UScriptStruct* InScriptStruct,
                                       const TArray<FBPVariableDescriptionIndex>& InBPVariableDescriptionIndex)
{
	for (const auto BPVariableDescriptionIndex : InBPVariableDescriptionIndex)
	{
		auto Blueprint = BPVariableDescriptionIndex.Blueprint;

		if (Blueprint.IsValid())
		{
			if (Blueprint->NewVariables.IsValidIndex(BPVariableDescriptionIndex.Index))
			{
				Blueprint->NewVariables[BPVariableDescriptionIndex.Index].VarType.PinSubCategoryObject = InScriptStruct;

				if (const auto SkeletonGeneratedClass = Cast<UBlueprintGeneratedClass>(
					Blueprint->SkeletonGeneratedClass))
				{
					SkeletonGeneratedClass->Bind();

					SkeletonGeneratedClass->StaticLink(true);
				}
			}
		}
	}
}

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
