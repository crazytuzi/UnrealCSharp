#include "Dynamic/FDynamicClassGenerator.h"
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
#include "mono/metadata/object.h"
#if WITH_EDITOR
#include "BlueprintActionDatabase.h"
#include "Kismet2/KismetEditorUtilities.h"
#endif
#include "UEVersion.h"
#include "Dynamic/CSharpBlueprint.h"

TSet<void*> FDynamicClassGenerator::ClassConstructorSet = {&FDynamicClassGenerator::ClassConstructor};

TMap<FString, UClass*> FDynamicClassGenerator::DynamicClass;

void FDynamicClassGenerator::Generator()
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_CLASS_ATTRIBUTE);

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
void FDynamicClassGenerator::CodeAnalysisGenerator()
{
	auto CSharpGeneratedClass = FDynamicGeneratorCore::GetDynamic(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *UCSharpClass::StaticClass()->GetName()),
		UCSharpClass::StaticClass()->GetName()
	);

	for (const auto& ClassName : CSharpGeneratedClass)
	{
		if (!DynamicClass.Contains(ClassName))
		{
			DynamicClass.Add(
				ClassName,
				GeneratorCSharpClass(FDynamicGeneratorCore::GetOuter(), ClassName.RightChop(1), AActor::StaticClass()));
		}
	}

	auto CSharpBlueprintGeneratedClass = FDynamicGeneratorCore::GetDynamic(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *UCSharpBlueprintGeneratedClass::StaticClass()->GetName()),
		UCSharpBlueprintGeneratedClass::StaticClass()->GetName()
	);

	for (const auto& ClassName : CSharpBlueprintGeneratedClass)
	{
		if (!DynamicClass.Contains(ClassName))
		{
			DynamicClass.Add(
				ClassName,
				GeneratorCSharpBlueprintGeneratedClass(FDynamicGeneratorCore::GetOuter(), ClassName,
				                                       AActor::StaticClass()));
		}
	}
}
#endif

void FDynamicClassGenerator::Generator(MonoClass* InMonoClass, const bool bReInstance)
{
	if (InMonoClass == nullptr)
	{
		return;
	}

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto Outer = FDynamicGeneratorCore::GetOuter();

	const auto ParentMonoClass = FMonoDomain::Class_Get_Parent(InMonoClass);

	const auto ParentMonoType = FMonoDomain::Class_Get_Type(ParentMonoClass);

	const auto ParentMonoReflectionType = FMonoDomain::Type_Get_Object(ParentMonoType);

	const auto ParentPathName = FTypeBridge::GetPathName(ParentMonoReflectionType);

	const auto ParentClass = LoadClass<UObject>(nullptr, *ParentPathName);

#if WITH_EDITOR
	auto PrevStructSize = 0;
#endif

	UClass* Class{};

	if (DynamicClass.Contains(ClassName))
	{
		Class = DynamicClass[ClassName];

#if WITH_EDITOR
		PrevStructSize = Class->GetStructureSize();
#endif

		Class->PurgeClass(false);

		if (Cast<UBlueprintGeneratedClass>(ParentClass))
		{
			Class->ClassFlags |= ParentClass->ClassFlags;

			BeginGenerator(Class, ParentClass);
		}
		else
		{
			Class->ClassFlags |= ParentClass->ClassFlags & CLASS_Native;

			BeginGenerator(Class, ParentClass);
		}
	}
	else
	{
		if (Cast<UBlueprintGeneratedClass>(ParentClass))
		{
			Class = GeneratorCSharpBlueprintGeneratedClass(Outer, ClassName, ParentClass);

			Class->ClassFlags |= ParentClass->ClassFlags;
		}
		else
		{
			Class = GeneratorCSharpClass(Outer, ClassName.RightChop(1), ParentClass);

			Class->ClassFlags |= ParentClass->ClassFlags & CLASS_Native;
		}

		DynamicClass.Add(ClassName, Class);
	}

#if WITH_EDITOR
	GeneratorMetaData(InMonoClass, Class);
#endif

	GeneratorProperty(InMonoClass, Class);

	GeneratorFunction(InMonoClass, Class);

	EndGenerator(Class);

#if WITH_EDITOR
	const auto NewStructSize = Class->GetStructureSize();

	if (bReInstance == true)
	{
		ReInstance(Class, NewStructSize - PrevStructSize);
	}
#endif
}

bool FDynamicClassGenerator::IsDynamicClass(MonoClass* InMonoClass)
{
	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_CLASS_ATTRIBUTE);

	const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass);

	return !!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass);
}

UClass* FDynamicClassGenerator::GetDynamicClass(MonoClass* InMonoClass)
{
	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto FoundDynamicClass = DynamicClass.Find(ClassName);

	return FoundDynamicClass != nullptr ? *FoundDynamicClass : nullptr;
}

void FDynamicClassGenerator::BeginGenerator(UClass* InClass, UClass* InParentClass)
{
	InClass->PropertyLink = InParentClass->PropertyLink;

	InClass->ClassWithin = InParentClass->ClassWithin;

	InClass->ClassConfigName = InParentClass->ClassConfigName;

	InClass->SetSuperStruct(InParentClass);

#if UE_CLASS_ADD_REFERENCED_OBJECTS
	InClass->ClassAddReferencedObjects = InParentClass->ClassAddReferencedObjects;
#endif

	InClass->ClassCastFlags |= InParentClass->ClassCastFlags;

	InClass->ClassConstructor = &FDynamicClassGenerator::ClassConstructor;
}

void FDynamicClassGenerator::BeginGenerator(UCSharpBlueprintGeneratedClass* InClass, UClass* InParentClass)
{
	BeginGenerator(static_cast<UClass*>(InClass), InParentClass);

#if WITH_EDITOR
	Cast<UCSharpBlueprint>(InClass->ClassGeneratedBy)->ParentClass = InParentClass;
#endif
}

void FDynamicClassGenerator::EndGenerator(UClass* InClass)
{
	InClass->ClearInternalFlags(EInternalObjectFlags::Native);

	InClass->Bind();

	InClass->StaticLink(true);

	InClass->AssembleReferenceTokenStream();

	if (InClass->ClassDefaultObject != nullptr)
	{
		InClass->ClassDefaultObject->SetFlags(RF_NewerVersionExists);

		InClass->ClassDefaultObject->MarkAsGarbage();

		InClass->ClassDefaultObject = nullptr;
	}

	(void)InClass->GetDefaultObject(true);

	InClass->SetInternalFlags(EInternalObjectFlags::Native);
}

UCSharpClass* FDynamicClassGenerator::GeneratorCSharpClass(
	UPackage* InOuter, const FString& InName, UClass* InParentClass)
{
	const auto Class = NewObject<UCSharpClass>(InOuter, *InName, RF_Public);

	Class->AddToRoot();

	BeginGenerator(Class, InParentClass);

	EndGenerator(Class);

	return Class;
}

UCSharpBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorCSharpBlueprintGeneratedClass(
	UPackage* InOuter, const FString& InName, UClass* InParentClass)
{
	auto Class = NewObject<UCSharpBlueprintGeneratedClass>(InOuter, *InName, RF_Public);

	Class->UpdateCustomPropertyListForPostConstruction();

	const auto Blueprint = NewObject<UCSharpBlueprint>(Class);

	Blueprint->AddToRoot();

	Blueprint->SkeletonGeneratedClass = Class;

	Blueprint->GeneratedClass = Class;

#if WITH_EDITOR
	Class->ClassGeneratedBy = Blueprint;
#endif

	BeginGenerator(Class, InParentClass);

	EndGenerator(Class);

	return Class;
}

#if WITH_EDITOR
void FDynamicClassGenerator::ReInstance(UClass* InClass, const int32 InChangedStructSize)
{
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InClass);

		ActionDatabase.RefreshClassActions(InClass);
	}

	if (Cast<UCSharpBlueprintGeneratedClass>(InClass))
	{
		if (InChangedStructSize != 0)
		{
			FDynamicGeneratorCore::IteratorBlueprintGeneratedClass(
				[InClass](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
				{
					return InBlueprintGeneratedClass->IsChildOf(InClass) &&
						InBlueprintGeneratedClass->GetPackage() != InClass->GetPackage() &&
						FKismetEditorUtilities::IsClassABlueprintSkeleton(*InBlueprintGeneratedClass);
				},
				[InChangedStructSize](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
				{
					InBlueprintGeneratedClass->SetPropertiesSize(
						InBlueprintGeneratedClass->GetPropertiesSize() + InChangedStructSize);
				});
		}
	}
	else
	{
		FDynamicGeneratorCore::ReloadPackages(
			[InClass](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
			{
				return InBlueprintGeneratedClass->IsChildOf(InClass);
			});
	}
}

void FDynamicClassGenerator::GeneratorMetaData(MonoClass* InMonoClass, UClass* InClass)
{
	if (InMonoClass == nullptr || InClass == nullptr)
	{
		return;
	}

	const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_CLASS_ATTRIBUTE);

	if (const auto Attrs = FMonoDomain::Custom_Attrs_From_Class(InMonoClass))
	{
		if (!!FMonoDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
		{
			FDynamicGeneratorCore::SetMetaData(InClass, Attrs);
		}
	}
}
#endif

void FDynamicClassGenerator::GeneratorProperty(MonoClass* InMonoClass, UClass* InClass)
{
	if (InMonoClass == nullptr || InClass == nullptr)
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

				const auto CppProperty = FTypeBridge::Factory(ReflectionType, InClass, PropertyName,
				                                              EObjectFlags::RF_Public);

				FDynamicGeneratorCore::SetPropertyFlags(CppProperty, Attrs);

				InClass->AddCppProperty(CppProperty);

#if WITH_EDITOR
				if (const auto ClassGeneratedBy = Cast<UCSharpBlueprint>(InClass->ClassGeneratedBy))
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

void FDynamicClassGenerator::GeneratorFunction(MonoClass* InMonoClass, UClass* InClass)
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
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_FUNCTION_ATTRIBUTE);

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

					if (const auto Property = FTypeBridge::Factory(ReturnParamReflectionType, Function, "",
					                                               RF_Public | RF_Transient))
					{
						Property->SetPropertyFlags(CPF_Parm | CPF_ReturnParm);

						Function->AddCppProperty(Property);
					}
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

				FDynamicGeneratorCore::SetFunctionFlags(Function, Attrs);

				InClass->AddFunctionToFunctionMap(Function, MethodName);
			}
		}
	}
}

void FDynamicClassGenerator::ClassConstructor(const FObjectInitializer& InObjectInitializer)
{
	const auto Object = InObjectInitializer.GetObj();

	auto SuperClass = InObjectInitializer.GetClass();

	while (SuperClass != nullptr)
	{
		if (Cast<UCSharpClass>(SuperClass) || Cast<UCSharpBlueprintGeneratedClass>(SuperClass))
		{
			for (TFieldIterator<FProperty> It(SuperClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
			{
				It->InitializeValue(It->ContainerPtrToValuePtr<void>(Object));
			}
		}

		SuperClass = SuperClass->GetSuperClass();
	}

	SuperClass = InObjectInitializer.GetClass();

	while (SuperClass != nullptr)
	{
		if (SuperClass->ClassConstructor != nullptr && !ClassConstructorSet.Contains(SuperClass->ClassConstructor))
		{
			SuperClass->ClassConstructor(InObjectInitializer);

			break;
		}

		SuperClass = SuperClass->GetSuperClass();
	}
}
