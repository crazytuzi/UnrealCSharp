#include "FStructGenerator.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Binding/Class/FBindingClass.h"
#include "Engine/UserDefinedStruct.h"
#include "Kismet2/StructureEditorUtils.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Dynamic/FDynamicStructGenerator.h"

void FStructGenerator::Generator()
{
	for (TObjectIterator<UScriptStruct> ScriptStructIterator; ScriptStructIterator; ++ScriptStructIterator)
	{
		if (!Cast<UUserDefinedStruct>(*ScriptStructIterator))
		{
			Generator(*ScriptStructIterator);
		}
	}
}

void FStructGenerator::Generator(const UScriptStruct* InScriptStruct)
{
	if (InScriptStruct == nullptr)
	{
		return;
	}

	if (FDynamicStructGenerator::IsDynamicStruct(InScriptStruct))
	{
		return;
	}

	if (Cast<UAnimBlueprintGeneratedClass>(InScriptStruct->GetOwnerClass()))
	{
		return;
	}

	if (FGeneratorCore::IsSkip(InScriptStruct))
	{
		return;
	}

	if (!FGeneratorCore::IsSupported(InScriptStruct))
	{
		return;
	}

	if (FUnrealCSharpFunctionLibrary::IsSpecialStruct(InScriptStruct))
	{
		return;
	}

	if (FUnrealCSharpFunctionLibrary::IsDynamicReInstanceField(InScriptStruct))
	{
		return;
	}

	auto UserDefinedStruct = Cast<UUserDefinedStruct>(InScriptStruct);

	FString UsingNameSpaceContent;

	auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InScriptStruct);

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InScriptStruct);

	auto ClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InScriptStruct);

	const auto& BindingProperties = FBindingClass::GetPropertyNames(ClassContent);

	FString SuperStructContent;

	FString ConstructorContent;

	FString DestructorContent;

	FString IdenticalContent;

	FString PropertyContent;

	FString PropertyNameContent;

	FString GCHandleContent;

	TSet<FString> UsingNameSpaces{
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LIBRARY)
	};

	auto SuperStruct = InScriptStruct->GetSuperStruct();

	if (SuperStruct != nullptr)
	{
		auto SuperStructNameSpace = FUnrealCSharpFunctionLibrary::GetClassNameSpace(SuperStruct);

		if (NameSpaceContent != SuperStructNameSpace)
		{
			UsingNameSpaces.Add(SuperStructNameSpace);
		}

		SuperStructContent = FString::Printf(TEXT(
			" : %s, IStaticStruct, IGarbageCollectionHandle"
		),
		                                     *FUnrealCSharpFunctionLibrary::GetFullClass(SuperStruct));

		ConstructorContent = FString::Printf(TEXT(
			"\t\tpublic %s()\n"
			"\t\t{\n"
			"\t\t}\n"
		),
		                                     *ClassContent
		);
	}
	else
	{
		SuperStructContent = TEXT(" : IStaticStruct, IGarbageCollectionHandle");

		ConstructorContent = FString::Printf(TEXT(
			"\t\tpublic %s() => UStructImplementation.UStruct_RegisterImplementation(this, Utils.GetPathName(GetType()));\n"
		),
		                                     *ClassContent
		);

		DestructorContent = FString::Printf(TEXT(
			"\n\t\t~%s() => UStructImplementation.UStruct_UnRegisterImplementation(%s);\n"
		),
		                                    *ClassContent,
		                                    *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		GCHandleContent = FString::Printf(TEXT(
			"\t\tpublic nint %s { get; set; }\n"
		),
		                                  *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));
	}

	auto StaticStructContent = FString::Printf(TEXT(
		"\t\tpublic%s static UScriptStruct StaticStruct()\n"
		"\t\t{\n"
		"\t\t\treturn StaticStructSingleton \?\?= UStructImplementation.UStruct_StaticStructImplementation(\"%s\");\n"
		"\t\t}\n\n"
		"\t\tprivate static UScriptStruct StaticStructSingleton { get; set; }\n"
	),
	                                           SuperStruct != nullptr ? TEXT(" new") : TEXT(""),
	                                           *PathNameAttributeContent
	);

	IdenticalContent = FString::Printf(TEXT(
		"\t\tpublic static bool operator ==(%s A, %s B) => Utils.EqualsTo(A, B, UStructImplementation.UStruct_IdenticalImplementation);\n\n"
		"\t\tpublic static bool operator !=(%s A, %s B) => !(A == B);\n\n"
		"\t\tpublic override bool Equals(object Other) => this == Other as %s;\n\n"
		"\t\tpublic override int GetHashCode() => (int)%s;\n"
	),
	                                   *ClassContent,
	                                   *ClassContent,
	                                   *ClassContent,
	                                   *ClassContent,
	                                   *ClassContent,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UScriptStruct::StaticClass()));

	auto bHasProperty = false;

	TSet<FString> PropertyNameSet;

	for (TFieldIterator<FProperty> PropertyIterator(InScriptStruct, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated); PropertyIterator; ++
	     PropertyIterator)
	{
		const auto& PropertyName = PropertyIterator->GetName();

		if (PropertyNameSet.Contains(PropertyName))
		{
			continue;
		}

		if (!FGeneratorCore::IsSupported(*PropertyIterator))
		{
			continue;
		}

		if (BindingProperties.Contains(PropertyName))
		{
			continue;
		}

		FDelegateGenerator::Generator(*PropertyIterator);

		if (bHasProperty == true)
		{
			PropertyContent += "\n";
		}
		else
		{
			bHasProperty = true;
		}

		FString PropertyAccessSpecifiers = TEXT("public");

		auto PropertyType = FGeneratorCore::GetPropertyType(*PropertyIterator);

		auto DummyPropertyName = FString::Printf(TEXT(
			"__%s"
		),
		                                         *FUnrealCSharpFunctionLibrary::Encode(*PropertyIterator)
		);

		auto VariableFriendlyPropertyName = PropertyName;

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		if (UserDefinedStruct != nullptr)
		{
			VariableFriendlyPropertyName = FStructureEditorUtils::GetVariableFriendlyNameForProperty(
				UserDefinedStruct, *PropertyIterator);
		}

		PropertyContent += FString::Printf(TEXT(
			"\t\t%s %s %s\n"
			"\t\t{\n"
			"\t\t\tget\n"
			"\t\t\t{\n"
			"\t\t\t\tunsafe\n"
			"\t\t\t\t{\n"
			"\t\t\t\t\tvar __ReturnBuffer = stackalloc byte[%d];\n"
			"\n"
			"\t\t\t\t\tFPropertyImplementation.FProperty_GetStructPropertyImplementation(%s, %s, __ReturnBuffer);\n"
			"\n"
			"\t\t\t\t\treturn *(%s*)__ReturnBuffer;\n"
			"\t\t\t\t}\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tset\n"
			"\t\t\t{\n"
			"\t\t\t\tunsafe\n"
			"\t\t\t\t{\n"
			"\t\t\t\t\tvar __InBuffer = stackalloc byte[%d];\n"
			"\n"
			"\t\t\t\t\t*(%s*)__InBuffer = %s;\n"
			"\n"
			"\t\t\t\t\tFPropertyImplementation.FProperty_SetStructPropertyImplementation(%s, %s, __InBuffer);\n"
			"\t\t\t\t}\n"
			"\t\t\t}\n"
			"\t\t}\n"
		),
		                                   *PropertyAccessSpecifiers,
		                                   *PropertyType,
		                                   *FUnrealCSharpFunctionLibrary::Encode(
			                                   VariableFriendlyPropertyName, PropertyIterator->IsNative()),
		                                   FGeneratorCore::GetBufferSize(*PropertyIterator),
		                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                   *DummyPropertyName,
		                                   *PropertyType,
		                                   FGeneratorCore::GetBufferSize(*PropertyIterator),
		                                   *FGeneratorCore::GetBufferCast(*PropertyIterator),
		                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator),
		                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                   *DummyPropertyName
		);

		PropertyNameContent += FString::Printf(TEXT(
			"%s\t\tprivate static uint %s = 0;\n"
		),
		                                       PropertyNameSet.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                       *DummyPropertyName
		);

		PropertyNameSet.Add(PropertyName);
	}

	if (bHasProperty == true)
	{
		UsingNameSpaces.Add(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LIBRARY));
	}

	UsingNameSpaces.Remove(NameSpaceContent);

	UsingNameSpaces.Remove(TEXT(""));

	for (auto UsingNameSpace : UsingNameSpaces)
	{
		UsingNameSpaceContent += FString::Printf(TEXT(
			"using %s;\n"
		),
		                                         *UsingNameSpace);
	}

	auto Content = FString::Printf(TEXT(
		"%s\n"
		"namespace %s\n"
		"{\n"
		"\t[PathName(\"%s\")]\n"
		"\tpublic partial class %s%s\n"
		"\t{\n"
		"%s\n"
		"%s"
		"%s"
		"\n"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"\n"
		"%s"
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *PathNameAttributeContent,
	                               *ClassContent,
	                               *SuperStructContent,
	                               *StaticStructContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               *IdenticalContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyNameContent,
	                               *GCHandleContent
	);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FGeneratorCore::GetFileName(InScriptStruct), Content);
}
