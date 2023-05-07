#include "Mixin/FMixinGenerator.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "Domain/FMonoDomain.h"
#include "Mixin/CSharpGeneratedClass.h"
#include "Template/TGetArrayLength.h"
#include "Bridge/FTypeBridge.h"

void FMixinGenerator::Generator()
{
	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() +
		DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX
		}
	});

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_CLASS_ATTRIBUTE);

	const auto AttributeMonoType = FMonoDomain::Class_Get_Type(AttributeMonoClass);

	const auto AttributeMonoReflectionType = FMonoDomain::Type_Get_Object(AttributeMonoType);

	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	// @TODO
	void* InParams[2] = {AttributeMonoReflectionType, mono_gchandle_get_target_v2(FMonoDomain::AssemblyGCHandles[0])};

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

	FMonoDomain::Deinitialize();
}

void FMixinGenerator::Generator(MonoClass* InMonoClass)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FMonoDomain::Class_Get_Name(InMonoClass);

	const auto Outer = UObject::StaticClass()->GetPackage();

	if (LoadClass<UObject>(Outer, *FString(ClassName)))
	{
		return;
	}

	const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass);

	const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass);

	const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType);

	const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

	const auto ParentClass = LoadClass<UObject>(nullptr, *ParentPathName);

	auto Class = NewObject<UCSharpGeneratedClass>(Outer, ClassName, RF_Public);

	// @TODO
	const auto Blueprint = NewObject<UBlueprint>(Outer);

	Blueprint->AddToRoot();

	Blueprint->GeneratedClass = Class;
#if WITH_EDITOR
	Class->ClassGeneratedBy = Blueprint;
#endif

	Class->PropertyLink = ParentClass->PropertyLink;

	Class->ClassWithin = ParentClass->ClassWithin;

	Class->ClassConfigName = ParentClass->ClassConfigName;

	Class->SetSuperStruct(ParentClass);

	Class->ClassFlags |= ParentClass->ClassFlags & (CLASS_Inherit | CLASS_ScriptInherit | CLASS_CompiledFromBlueprint);

	Class->ClassAddReferencedObjects = ParentClass->ClassAddReferencedObjects;

	// @TODO
	GeneratorProperty(InMonoClass, Class);

	Class->Bind();

	Class->StaticLink(true);

	Class->AssembleReferenceTokenStream();

	(void)Class->GetDefaultObject();
}

void FMixinGenerator::GeneratorProperty(MonoClass* InMonoClass, UCSharpGeneratedClass* InClass)
{
	if (InMonoClass == nullptr || InClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_PROPERTY_ATTRIBUTE);

	void* Iterator = nullptr;

	while (const auto Field = FMonoDomain::Class_Get_Fields(InMonoClass, &Iterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Field(InMonoClass, Field))
		{
			if (FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto FieldName = FMonoDomain::Field_Get_Name(Field);

				const auto FieldType = FMonoDomain::Field_Get_Type(Field);

				const auto ReflectionType = FMonoDomain::Type_Get_Object(FieldType);

#if WITH_EDITOR
				FBPVariableDescription BPVariableDescription;

				BPVariableDescription.VarName = FieldName;

				BPVariableDescription.VarGuid = FGuid::NewGuid();

				Cast<UBlueprint>(InClass->ClassGeneratedBy)->NewVariables.Add(BPVariableDescription);
#endif

				const auto Property = FTypeBridge::Factory(ReflectionType, InClass, FieldName, EObjectFlags::RF_Public);

				Property->SetPropertyFlags(CPF_BlueprintVisible);

				InClass->AddCppProperty(Property);
			}
		}
	}
}
