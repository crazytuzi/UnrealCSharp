#include "Mixin/FMixinClassGenerator.h"
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
#include "mono/metadata/object.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#endif
#include "UEVersion.h"

void FMixinClassGenerator::Generator()
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_CLASS_ATTRIBUTE);

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
void FMixinClassGenerator::CodeAnalysisGenerator()
{
	auto CSharpGeneratedClass = FMixinGeneratorCore::GetMixin(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *UCSharpGeneratedClass::StaticClass()->GetName()),
		UCSharpGeneratedClass::StaticClass()->GetName()
	);

	for (const auto& ClassName : CSharpGeneratedClass)
	{
		const auto Outer = FMixinGeneratorCore::GetOuter();

		const auto Class = LoadObject<UClass>(Outer, *FString(ClassName));

		if (Class == nullptr)
		{
			GeneratorCSharpGeneratedClass(Outer, ClassName);
		}
	}

	auto CSharpBlueprintGeneratedClass = FMixinGeneratorCore::GetMixin(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *UCSharpBlueprintGeneratedClass::StaticClass()->GetName()),
		UCSharpBlueprintGeneratedClass::StaticClass()->GetName()
	);

	for (const auto& ClassName : CSharpBlueprintGeneratedClass)
	{
		const auto Outer = FMixinGeneratorCore::GetOuter();

		const auto Class = LoadObject<UClass>(Outer, *FString(ClassName));

		if (Class == nullptr)
		{
			GeneratorCSharpBlueprintGeneratedClass(Outer, ClassName);
		}
	}
}
#endif

void FMixinClassGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FMonoDomain::Class_Get_Name(InMonoClass);

	const auto Outer = FMixinGeneratorCore::GetOuter();

	const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass);

	const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass);

	const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType);

	const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

	const auto ParentClass = LoadClass<UObject>(nullptr, *ParentPathName);

	auto Class = LoadObject<UClass>(Outer, *FString(ClassName));

	if (Class != nullptr)
	{
		Class->PurgeClass(false);

		if (!Cast<UBlueprintGeneratedClass>(ParentClass))
		{
			Class->ClassFlags |= ParentClass->ClassFlags & CLASS_Native;
		}
		else
		{
			Class->ClassFlags |= ParentClass->ClassFlags;
		}
	}
	else
	{
		if (Cast<UBlueprintGeneratedClass>(ParentClass))
		{
			Class = GeneratorCSharpBlueprintGeneratedClass(Outer, ClassName);

			Class->ClassFlags |= ParentClass->ClassFlags;
		}
		else
		{
			Class = GeneratorCSharpGeneratedClass(Outer, ClassName);

			Class->ClassFlags |= ParentClass->ClassFlags & CLASS_Native;
		}
	}

	BeginGenerator(Class, ParentClass);

	GeneratorProperty(InMonoClass, Class);

	GeneratorFunction(InMonoClass, Class);

	EndGenerator(Class);

	(void)Class->GetDefaultObject();

#if WITH_EDITOR
	if (bReInstance == true)
	{
		ReInstance(Class);
	}
#endif
}

bool FMixinClassGenerator::IsMixinClass(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), CLASS_U_CLASS_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

void FMixinClassGenerator::BeginGenerator(UClass* InClass, UClass* InParentClass)
{
	InClass->PropertyLink = InParentClass->PropertyLink;

	InClass->ClassWithin = InParentClass->ClassWithin;

	InClass->ClassConfigName = InParentClass->ClassConfigName;

	InClass->SetSuperStruct(InParentClass);

#if UE_CLASS_ADD_REFERENCED_OBJECTS
	InClass->ClassAddReferencedObjects = InParentClass->ClassAddReferencedObjects;
#endif
}

void FMixinClassGenerator::EndGenerator(UClass* InClass)
{
	InClass->Bind();

	InClass->StaticLink(true);

	InClass->AssembleReferenceTokenStream();
}

UCSharpGeneratedClass* FMixinClassGenerator::GeneratorCSharpGeneratedClass(UPackage* InOuter, const FString& InName)
{
	const auto Class = NewObject<UCSharpGeneratedClass>(InOuter, *InName, RF_Public);

	Class->AddToRoot();

	BeginGenerator(Class, AActor::StaticClass());

	EndGenerator(Class);

	return Class;
}

UCSharpBlueprintGeneratedClass* FMixinClassGenerator::GeneratorCSharpBlueprintGeneratedClass(
	UPackage* InOuter, const FString& InName)
{
	auto Class = NewObject<UCSharpBlueprintGeneratedClass>(InOuter, *InName, RF_Public);

	Class->UpdateCustomPropertyListForPostConstruction();

	const auto Blueprint = NewObject<UBlueprint>(Class);

	Blueprint->AddToRoot();

	Blueprint->SkeletonGeneratedClass = Class;

	Blueprint->GeneratedClass = Class;

#if WITH_EDITOR
	Class->ClassGeneratedBy = Blueprint;
#endif

	BeginGenerator(Class, AActor::StaticClass());

	EndGenerator(Class);

	return Class;
}

#if WITH_EDITOR
void FMixinClassGenerator::ReInstance(UClass* InClass)
{
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InClass);

		ActionDatabase.RefreshClassActions(InClass);
	}

	for (TObjectIterator<UBlueprintGeneratedClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		if (ClassIterator->IsChildOf(InClass))
		{
			ClassIterator->Bind();

			ClassIterator->StaticLink(true);
		}
	}
}
#endif

void FMixinClassGenerator::GeneratorProperty(MonoClass* InMonoClass, UClass* InClass)
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
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto PropertyName = FMonoDomain::Property_Get_Name(Property);

				const auto PropertyType = FMonoDomain::Property_Get_Type(Property);

				const auto ReflectionType = FMonoDomain::Type_Get_Object(PropertyType);

				const auto CppProperty = FTypeBridge::Factory(ReflectionType, InClass, PropertyName,
				                                              EObjectFlags::RF_Public);

				FMixinGeneratorCore::SetPropertyFlags(CppProperty, Attrs);

				InClass->AddCppProperty(CppProperty);

#if WITH_EDITOR
				if (const auto ClassGeneratedBy = Cast<UBlueprint>(InClass->ClassGeneratedBy))
				{
					auto bExisted = false;

					for (const auto& Variable : ClassGeneratedBy->NewVariables)
					{
						if (Variable.VarName == PropertyName)
						{
							bExisted = true;

							break;
						}
					}

					if (!bExisted)
					{
						FBPVariableDescription BPVariableDescription;

						BPVariableDescription.VarName = PropertyName;

						BPVariableDescription.VarGuid = FGuid::NewGuid();

						ClassGeneratedBy->NewVariables.Add(BPVariableDescription);
					}
				}
#endif
			}
		}
	}
}

void FMixinClassGenerator::GeneratorFunction(MonoClass* InMonoClass, UClass* InClass)
{
	struct FParamDescriptor
	{
		MonoReflectionType* ReflectionType;

		FName Name;

		bool bIsRef;
	};

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
			if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
			{
				const auto MethodName = FMonoDomain::Method_Get_Name(Method);

				const auto Signature = FMonoDomain::Method_Signature(Method);

				void* ParamIterator = nullptr;

				const auto ParamCount = FMonoDomain::Signature_Get_Param_Count(Signature);

				const auto ParamNames = static_cast<const char**>(FMemory_Alloca(ParamCount * sizeof(const char*)));

				FMonoDomain::Method_Get_Param_Names(Method, ParamNames);

				auto ParamIndex = 0;

				TArray<FParamDescriptor> ParamDescriptors;

				while (const auto Param = FMonoDomain::Signature_Get_Params(Signature, &ParamIterator))
				{
					ParamDescriptors.Add({
						FMonoDomain::Type_Get_Object(Param),
						ParamNames[ParamIndex++],
						!!FMonoDomain::Type_Is_ByRef(Param)
					});
				}

				auto Function = NewObject<UFunction>(InClass, MethodName, RF_Public | RF_Transient);

				Function->MinAlignment = 1;

				if (const auto ReturnParamType = FMonoDomain::Signature_Get_Return_Type(Signature))
				{
					const auto ReturnParamReflectionType = FMonoDomain::Type_Get_Object(ReturnParamType);

					const auto Property = FTypeBridge::Factory(ReturnParamReflectionType, Function, "",
					                                           RF_Public | RF_Transient);

					Property->SetPropertyFlags(CPF_Parm | CPF_ReturnParm);

					Function->AddCppProperty(Property);
				}

				for (auto Index = ParamDescriptors.Num() - 1; Index >= 0; --Index)
				{
					const auto Property = FTypeBridge::Factory(ParamDescriptors[Index].ReflectionType,
					                                           Function,
					                                           ParamDescriptors[Index].Name,
					                                           RF_Public | RF_Transient);

					Property->SetPropertyFlags(CPF_Parm);

					if (ParamDescriptors[Index].bIsRef)
					{
						Property->SetPropertyFlags(CPF_OutParm);
					}

					Function->AddCppProperty(Property);
				}

				Function->Bind();

				Function->StaticLink(true);

				Function->Next = InClass->Children;

				InClass->Children = Function;

				FMixinGeneratorCore::SetFunctionFlags(Function, Attrs);

				InClass->AddFunctionToFunctionMap(Function, MethodName);

				Function->AddToRoot();
			}
		}
	}
}
