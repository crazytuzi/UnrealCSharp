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
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Dynamic/FDynamicGenerator.h"
#endif
#include "UEVersion.h"

TSet<UClass::ClassConstructorType> FDynamicClassGenerator::ClassConstructorSet
{
	&FDynamicClassGenerator::ClassConstructor
};

TMap<FString, UClass*> FDynamicClassGenerator::DynamicClassMap;

TSet<UClass*> FDynamicClassGenerator::DynamicClassSet;

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
	static FString CSharpClass = TEXT("CSharpClass");

	auto ClassNames = FDynamicGeneratorCore::GetDynamic(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *CSharpClass),
		CSharpClass
	);

	for (const auto& ClassName : ClassNames)
	{
		if (!DynamicClassMap.Contains(ClassName))
		{
			GeneratorCSharpClass(FDynamicGeneratorCore::GetOuter(), ClassName, AActor::StaticClass());
		}
	}

	static FString CSharpBlueprintGeneratedClass = TEXT("CSharpBlueprintGeneratedClass");

	auto BlueprintGeneratedClassNames = FDynamicGeneratorCore::GetDynamic(
		FString::Printf(TEXT(
			"%s/%s.json"),
		                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		                *CSharpBlueprintGeneratedClass),
		CSharpBlueprintGeneratedClass
	);

	for (const auto& ClassName : BlueprintGeneratedClassNames)
	{
		if (!DynamicClassMap.Contains(ClassName))
		{
			GeneratorCSharpBlueprintGeneratedClass(FDynamicGeneratorCore::GetOuter(), ClassName, AActor::StaticClass());
		}
	}
}

void FDynamicClassGenerator::OnPrePIEEnded()
{
	FDynamicGeneratorCore::IteratorBlueprintGeneratedClass(
		[](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			for (const auto& DynamicClass : DynamicClassMap)
			{
				if (InBlueprintGeneratedClass->IsChildOf(DynamicClass.Value))
				{
					return true;
				}
			}

			return false;
		},
		[](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			InBlueprintGeneratedClass->ClassConstructor = &FDynamicClassGenerator::ClassConstructor;
		});
}
#endif

void FDynamicClassGenerator::Generator(MonoClass* InMonoClass)
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

	UClass* Class{};

#if WITH_EDITOR
	UClass* OldClass{};

	if (DynamicClassMap.Contains(ClassName))
	{
		OldClass = DynamicClassMap[ClassName];

		DynamicClassSet.Remove(OldClass);

		if (const auto BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(OldClass))
		{
			if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
			{
				Blueprint->Rename(
					*MakeUniqueObjectName(
						BlueprintGeneratedClass->GetOuter(),
						BlueprintGeneratedClass->GetClass())
					.ToString(),
					nullptr,
					REN_DontCreateRedirectors);
			}
		}
		else
		{
			OldClass->Rename(
				*MakeUniqueObjectName(
					OldClass->GetOuter(),
					OldClass->GetClass())
				.ToString(),
				nullptr,
				REN_DontCreateRedirectors);
		}
	}
#endif

	if (Cast<UBlueprintGeneratedClass>(ParentClass))
	{
		Class = GeneratorCSharpBlueprintGeneratedClass(Outer, ClassName, ParentClass,
		                                               [InMonoClass](UClass* InClass)
		                                               {
			                                               ProcessGenerator(InMonoClass, InClass);
		                                               });
	}
	else
	{
		Class = GeneratorCSharpClass(Outer, ClassName, ParentClass,
		                             [InMonoClass](UClass* InClass)
		                             {
			                             ProcessGenerator(InMonoClass, InClass);
		                             });
	}

#if WITH_EDITOR
	if (OldClass != nullptr)
	{
		ReInstance(OldClass, Class);
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

bool FDynamicClassGenerator::IsDynamicClass(const UClass* InClass)
{
	return DynamicClassSet.Contains(InClass);
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(const UField* InField)
{
	return IsDynamicBlueprintGeneratedClass(Cast<UClass>(InField));
}

bool FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(const UClass* InClass)
{
	return IsDynamicClass(InClass) && !!Cast<UBlueprintGeneratedClass>(InClass);
}

UClass* FDynamicClassGenerator::GetDynamicClass(MonoClass* InMonoClass)
{
	const auto ClassName = FString(FMonoDomain::Class_Get_Name(InMonoClass));

	const auto FoundDynamicClass = DynamicClassMap.Find(ClassName);

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

	InClass->ClassFlags |= CLASS_Native;

	InClass->ClassCastFlags |= InParentClass->ClassCastFlags;

	InClass->ClassConstructor = &FDynamicClassGenerator::ClassConstructor;
}

void FDynamicClassGenerator::BeginGenerator(UBlueprintGeneratedClass* InClass, UClass* InParentClass)
{
	BeginGenerator(static_cast<UClass*>(InClass), InParentClass);

#if WITH_EDITOR
	Cast<UBlueprint>(InClass->ClassGeneratedBy)->ParentClass = InParentClass;
#endif
}

void FDynamicClassGenerator::ProcessGenerator(MonoClass* InMonoClass, UClass* InClass)
{
#if WITH_EDITOR
	GeneratorMetaData(InMonoClass, InClass);
#endif

	GeneratorProperty(InMonoClass, InClass);

	GeneratorFunction(InMonoClass, InClass);
}

void FDynamicClassGenerator::EndGenerator(UClass* InClass)
{
	InClass->ClearInternalFlags(EInternalObjectFlags::Native);

	InClass->Bind();

	InClass->StaticLink(true);

	InClass->AssembleReferenceTokenStream();

	InClass->ClassDefaultObject = StaticAllocateObject(InClass, InClass->GetOuter(),
	                                                   *InClass->GetDefaultObjectName().ToString(),
	                                                   RF_Public | RF_ClassDefaultObject | RF_ArchetypeObject,
	                                                   EInternalObjectFlags::None,
	                                                   false);

	(*InClass->ClassConstructor)(FObjectInitializer(InClass->ClassDefaultObject,
	                                                InClass->GetSuperClass()->GetDefaultObject(),
	                                                EObjectInitializerOptions::None));

	InClass->SetInternalFlags(EInternalObjectFlags::Native);
}

UClass* FDynamicClassGenerator::GeneratorCSharpClass(
	UPackage* InOuter, const FString& InName, UClass* InParentClass)
{
	return GeneratorCSharpClass(InOuter, InName, InParentClass,
	                            [](UClass*)
	                            {
	                            });
}

UClass* FDynamicClassGenerator::GeneratorCSharpClass(UPackage* InOuter, const FString& InName, UClass* InParentClass,
                                                     const TFunction<void(UClass*)>& InProcessGenerator)
{
	const auto Class = NewObject<UClass>(InOuter, *InName.RightChop(1), RF_Public);

	Class->AddToRoot();

	GeneratorClass(InName, Class, InParentClass, InProcessGenerator);

	return Class;
}

UBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorCSharpBlueprintGeneratedClass(
	UPackage* InOuter, const FString& InName, UClass* InParentClass)
{
	return GeneratorCSharpBlueprintGeneratedClass(InOuter, InName, InParentClass,
	                                              [](UClass*)
	                                              {
	                                              });
}

UBlueprintGeneratedClass* FDynamicClassGenerator::GeneratorCSharpBlueprintGeneratedClass(UPackage* InOuter,
	const FString& InName, UClass* InParentClass, const TFunction<void(UClass*)>& InProcessGenerator)
{
	auto Class = NewObject<UBlueprintGeneratedClass>(InOuter, *InName, RF_Public);

	Class->UpdateCustomPropertyListForPostConstruction();

	const auto Blueprint = NewObject<UBlueprint>(Class, *InName.LeftChop(2));

	Blueprint->AddToRoot();

	Blueprint->SkeletonGeneratedClass = Class;

	Blueprint->GeneratedClass = Class;

#if WITH_EDITOR
	Class->ClassGeneratedBy = Blueprint;
#endif

	GeneratorClass(InName, Class, InParentClass, InProcessGenerator);

	return Class;
}

#if WITH_EDITOR
void FDynamicClassGenerator::ReInstance(UClass* InOldClass, UClass* InNewClass)
{
	if (GEditor)
	{
		FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();

		ActionDatabase.ClearAssetActions(InNewClass);

		ActionDatabase.RefreshClassActions(InNewClass);
	}

	FBlueprintCompileReinstancer::ReplaceInstancesOfClass(InOldClass, InNewClass, InOldClass->ClassDefaultObject);

	TArray<UBlueprintGeneratedClass*> BlueprintGeneratedClasses;

	FDynamicGeneratorCore::IteratorBlueprintGeneratedClass(
		[InOldClass](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			return InBlueprintGeneratedClass->IsChildOf(InOldClass) && *InBlueprintGeneratedClass != InOldClass;
		},
		[&BlueprintGeneratedClasses](const TObjectIterator<UBlueprintGeneratedClass>& InBlueprintGeneratedClass)
		{
			if (const auto ClassName = InBlueprintGeneratedClass->GetName();
				ClassName.StartsWith(TEXT("SKEL_")) || ClassName.StartsWith(TEXT("PLACEHOLDER-CLASS")) ||
				ClassName.StartsWith(TEXT("REINST_")) || ClassName.StartsWith(TEXT("TRASHCLASS_")) ||
				ClassName.StartsWith(TEXT("HOTRELOADED_")))
			{
				return;
			}

			BlueprintGeneratedClasses.AddUnique(*InBlueprintGeneratedClass);
		});

	InOldClass->ClassDefaultObject = nullptr;

	(void)InOldClass->GetDefaultObject(true);

	for (const auto BlueprintGeneratedClass : BlueprintGeneratedClasses)
	{
		const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy);

		Blueprint->Modify();

		if (const auto SimpleConstructionScript = Blueprint->SimpleConstructionScript)
		{
			SimpleConstructionScript->Modify();

			const auto& AllNodes = SimpleConstructionScript->GetAllNodes();

			for (const auto& Node : AllNodes)
			{
				Node->Modify();
			}
		}

		Blueprint->ParentClass = InNewClass;

		if (FDynamicGenerator::IsFullGenerator())
		{
			const auto OriginalBlueprintType = Blueprint->BlueprintType;

			Blueprint->BlueprintType = BPTYPE_MacroLibrary;

			FBlueprintEditorUtils::RefreshAllNodes(Blueprint);

			Blueprint->BlueprintType = OriginalBlueprintType;

			TArray<UK2Node*> AllNodes;

			FBlueprintEditorUtils::GetAllNodesOfClass(Blueprint, AllNodes);

			for (const auto Node : AllNodes)
			{
				for (const auto Pin : Node->Pins)
				{
					if (Pin->PinType.PinSubCategoryObject == InOldClass)
					{
						Pin->PinType.PinSubCategoryObject = InNewClass;
					}
				}
			}
		}
		else
		{
			FBlueprintEditorUtils::RefreshAllNodes(Blueprint);
		}

		FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);

		constexpr auto BlueprintCompileOptions = EBlueprintCompileOptions::SkipGarbageCollection |
			EBlueprintCompileOptions::SkipSave;

		FKismetEditorUtilities::CompileBlueprint(Blueprint, BlueprintCompileOptions);
	}

	if (const auto BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InOldClass))
	{
		if (const auto Blueprint = Cast<UBlueprint>(BlueprintGeneratedClass->ClassGeneratedBy))
		{
			Blueprint->RemoveFromRoot();

			Blueprint->MarkAsGarbage();
		}
	}
	else
	{
		InOldClass->RemoveFromRoot();

		InOldClass->MarkAsGarbage();
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
				if (const auto Blueprint = Cast<UBlueprint>(InClass->ClassGeneratedBy))
				{
					auto bExisted = false;

					for (const auto& Variable : Blueprint->NewVariables)
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

						Blueprint->NewVariables.Add(BPVariableDescription);
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
						Property->SetPropertyFlags(CPF_Parm | CPF_OutParm | CPF_ReturnParm);

						Function->AddCppProperty(Property);

						Function->FunctionFlags |= FUNC_HasOutParms;
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
						Property->SetPropertyFlags(CPF_OutParm | CPF_ReferenceParm);
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
		if (IsDynamicClass(SuperClass))
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
