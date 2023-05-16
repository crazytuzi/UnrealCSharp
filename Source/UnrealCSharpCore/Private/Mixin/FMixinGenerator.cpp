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
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
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
	void* InParams[2] = {AttributeMonoReflectionType, mono_gchandle_get_target_v2(FMonoDomain::AssemblyGCHandles[1])};

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

void FMixinGenerator::Generator(const TArray<FFileChangeData>& FileChangeData)
{
	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() +
		DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	for (const auto& Data : FileChangeData)
	{
		if (FPaths::GetExtension(Data.Filename) == TEXT("cs"))
		{
			auto Filename = FPaths::GetBaseFilename(Data.Filename);

			if (auto Class = LoadClass<UObject>(UObject::StaticClass()->GetPackage(), *FString(Filename)))
			{
				Generator(FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(Class),
					FUnrealCSharpFunctionLibrary::GetFullClass(Class)));

				Class = LoadClass<UObject>(UObject::StaticClass()->GetPackage(), *FString(Filename));

				for (TObjectIterator<UBlueprintGeneratedClass> ClassIterator; ClassIterator; ++ClassIterator)
				{
					if (ClassIterator->IsChildOf(Class))
					{
						ClassIterator->UpdateCustomPropertyListForPostConstruction();

						ClassIterator->Bind();

						ClassIterator->StaticLink(true);
					}
				}
			}
		}
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

	const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass);

	const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass);

	const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType);

	const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

	const auto ParentClass = LoadClass<UObject>(nullptr, *ParentPathName);

	const auto Class = NewObject<UCSharpGeneratedClass>(Outer, ClassName, RF_Public);

	Class->PropertyLink = ParentClass->PropertyLink;

	Class->ClassWithin = ParentClass->ClassWithin;

	Class->ClassConfigName = ParentClass->ClassConfigName;

	Class->SetSuperStruct(ParentClass);

	Class->ClassFlags |= ParentClass->ClassFlags & CLASS_Native;

	Class->ClassAddReferencedObjects = ParentClass->ClassAddReferencedObjects;

	// @TODO
	GeneratorProperty(InMonoClass, Class);

	// @TODO
	GeneratorFunction(InMonoClass, Class);

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

	while (const auto Property = FMonoDomain::Class_Get_Properties(InMonoClass, &Iterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Property(InMonoClass, Property))
		{
			if (FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto PropertyName = FMonoDomain::Property_Get_Name(Property);

				const auto PropertyType = FMonoDomain::Property_Get_Type(Property);

				const auto ReflectionType = FMonoDomain::Type_Get_Object(PropertyType);

				const auto CppProperty = FTypeBridge::Factory(ReflectionType, InClass, PropertyName,
				                                              EObjectFlags::RF_Public);

				// @TODO
				CppProperty->SetPropertyFlags(CPF_BlueprintVisible | CPF_Edit);

				InClass->AddCppProperty(CppProperty);
			}
		}
	}
}

void FMixinGenerator::GeneratorFunction(MonoClass* InMonoClass, UCSharpGeneratedClass* InClass)
{
	if (InMonoClass == nullptr || InClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_FUNCTION_ATTRIBUTE);

	void* MethodIterator = nullptr;

	while (const auto Method = FMonoDomain::Class_Get_Methods(InMonoClass, &MethodIterator))
	{
		if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Method(Method))
		{
			if (FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto MethodName = FMonoDomain::Method_Get_Name(Method);

				const auto Signature = FMonoDomain::Method_Signature(Method);

				void* ParamIterator = nullptr;

				const auto ParamCount = FMonoDomain::Signature_Get_Param_Count(Signature);

				const auto ParamNames = static_cast<const char**>(FMemory_Alloca(ParamCount * sizeof(const char*)));

				FMonoDomain::Method_Get_Param_Names(Method, ParamNames);

				auto ParamIndex = 0;

				TArray<TPair<const char*, MonoReflectionType*>> Params;

				while (const auto Param = FMonoDomain::Signature_Get_Params(Signature, &ParamIterator))
				{
					Params.Add({ParamNames[ParamIndex++], FMonoDomain::Type_Get_Object(Param)});
				}

				auto Function = NewObject<UFunction>(InClass, MethodName, RF_Public | RF_Transient);

				// @TODO
				Function->FunctionFlags = FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent;

				Function->MinAlignment = 1;

				if (const auto ReturnParamType = FMonoDomain::Signature_Get_Return_Type(Signature))
				{
					const auto ReturnParamReflectionType = FMonoDomain::Type_Get_Object(ReturnParamType);

					const auto Property = FTypeBridge::Factory(ReturnParamReflectionType, Function, "",
					                                           RF_Public | RF_Transient);

					Property->SetPropertyFlags(CPF_Parm | CPF_ReturnParm);

					Function->AddCppProperty(Property);
				}

				for (auto Index = Params.Num() - 1; Index >= 0; --Index)
				{
					const auto Property = FTypeBridge::Factory(Params[Index].Value, Function, Params[Index].Key,
					                                           RF_Public | RF_Transient);

					Property->SetPropertyFlags(CPF_Parm);

					Function->AddCppProperty(Property);
				}

				Function->Bind();

				Function->StaticLink(true);

				Function->Next = InClass->Children;

				InClass->Children = Function;

				InClass->AddFunctionToFunctionMap(Function, MethodName);

				Function->AddToRoot();
			}
		}
	}
}
