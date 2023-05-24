#include "Mixin/FMixinEnumGenerator.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Domain/FMonoDomain.h"
#include "Mixin/CSharpEnum.h"
#include "Template/TGetArrayLength.h"

void FMixinEnumGenerator::Generator()
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_ENUM_ATTRIBUTE);

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

void FMixinEnumGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FMonoDomain::Class_Get_Name(InMonoClass);

	const auto Outer = UObject::StaticClass()->GetPackage();

	auto Enum = LoadObject<UCSharpEnum>(Outer, *FString(ClassName));

	if (Enum != nullptr)
	{
		if (bReInstance)
		{
			// @TODO
		}
	}
	else
	{
		Enum = NewObject<UCSharpEnum>(Outer, ClassName, RF_Public);

		Enum->AddToRoot();
	}

	// @TODO
#if WITH_EDITOR
	Enum->SetMetaData(*FBlueprintMetadata::MD_AllowableBlueprintVariableType.ToString(), TEXT("true"));
#endif

	GeneratorEnumerator(InMonoClass, Enum);

#if WITH_EDITOR
	if (bReInstance)
	{
		ReInstance(Enum);
	}
#endif
}

bool FMixinEnumGenerator::IsMixinEnum(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_ENUM_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

#if WITH_EDITOR
void FMixinEnumGenerator::ReInstance(UEnum* InEnum)
{
	// @TODO
}
#endif

void FMixinEnumGenerator::GeneratorEnumerator(MonoClass* InMonoClass, UEnum* InEnum)
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
