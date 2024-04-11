#include "FStructGenerator.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Engine/UserDefinedStruct.h"
#include "Kismet2/StructureEditorUtils.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Dynamic/FDynamicStructGenerator.h"

void FStructGenerator::Generator()
{
	for (TObjectIterator<UScriptStruct> ScriptStructIterator; ScriptStructIterator; ++ScriptStructIterator)
	{
		Generator(*ScriptStructIterator);
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
		"\t\t\treturn UStructImplementation.UStruct_StaticStructImplementation(\"%s\");\n"
		"\t\t}\n"
	),
	                                           SuperStruct != nullptr ? TEXT(" new") : TEXT(""),
	                                           *PathNameAttributeContent
	);

	IdenticalContent = FString::Printf(TEXT(
		"\t\tpublic static bool operator ==(%s A, %s B) => UStructImplementation.UStruct_IdenticalImplementation(StaticStruct().%s, A?.%s??nint.Zero, B?.%s??nint.Zero);\n\n"
		"\t\tpublic static bool operator !=(%s A, %s B) => !UStructImplementation.UStruct_IdenticalImplementation(StaticStruct().%s, A?.%s??nint.Zero, B?.%s??nint.Zero);\n\n"
		"\t\tpublic override bool Equals(object Other) => this == Other as %s;\n\n"
		"\t\tpublic override int GetHashCode() => (int)%s;\n"
	),
	                                   *ClassContent,
	                                   *ClassContent,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                   *ClassContent,
	                                   *ClassContent,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                   *ClassContent,
	                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UScriptStruct::StaticClass()));

	auto bHasProperty = false;

	TArray<TPair<FString, FString>> PropertyNames;

	for (TFieldIterator<FProperty> PropertyIterator(InScriptStruct, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated); PropertyIterator; ++
	     PropertyIterator)
	{
		if (!FGeneratorCore::IsSupported(*PropertyIterator))
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

		auto PropertyName = PropertyIterator->GetName();

		PropertyNames.Add(TPair<FString, FString>{
			FString::Printf(TEXT(
				"__%s"
			),
			                *FUnrealCSharpFunctionLibrary::Encode(PropertyName)
			),
			PropertyName
		});

		auto VariableFriendlyPropertyName = PropertyName;

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		if (UserDefinedStruct != nullptr)
		{
			VariableFriendlyPropertyName = FStructureEditorUtils::GetVariableFriendlyNameForProperty(
				UserDefinedStruct, *PropertyIterator);
		}

		if (FGeneratorCore::IsPrimitiveProperty(*PropertyIterator))
		{
			PropertyContent += FString::Printf(TEXT(
				"\t\t%s %s %s\n"
				"\t\t{\n"
				"\t\t\tget => %sFPropertyImplementation.FProperty_GetStruct%sPropertyImplementation(%s, %s);\n"
				"\n"
				"\t\t\tset => FPropertyImplementation.FProperty_SetStruct%sPropertyImplementation(%s, %s, %s);\n"
				"\t\t}\n"
			),
			                                   *PropertyAccessSpecifiers,
			                                   *PropertyType,
			                                   *FUnrealCSharpFunctionLibrary::Encode(VariableFriendlyPropertyName),
			                                   *FGeneratorCore::GetGetAccessorReturnParamName(*PropertyIterator),
			                                   *FGeneratorCore::GetGetPrimitiveAccessorType(*PropertyIterator),
			                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetGetPrimitiveAccessorType(*PropertyIterator),
			                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator)
			);
		}
		else
		{
			PropertyContent += FString::Printf(TEXT(
				"\t\t%s %s %s\n"
				"\t\t{\n"
				"\t\t\tget => FPropertyImplementation.FProperty_GetStructCompoundPropertyImplementation(%s, %s) as %s;\n"
				"\n"
				"\t\t\tset => FPropertyImplementation.FProperty_SetStructCompoundPropertyImplementation(%s, %s, %s);\n"
				"\t\t}\n"
			),
			                                   *PropertyAccessSpecifiers,
			                                   *PropertyType,
			                                   *FUnrealCSharpFunctionLibrary::Encode(VariableFriendlyPropertyName),
			                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetPropertyType(*PropertyIterator),
			                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator)
			);
		}
	}

	if (bHasProperty == true)
	{
		UsingNameSpaces.Add(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LIBRARY));
	}

	for (auto Index = 0; Index < PropertyNames.Num(); ++Index)
	{
		PropertyNameContent += FString::Printf(TEXT(
			"%s\t\tprivate static uint %s = 0;\n"
		),
		                                       Index == 0 ? TEXT("") : TEXT("\n"),
		                                       *PropertyNames[Index].Key
		);
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

	FGeneratorCore::SaveStringToFile(FGeneratorCore::GetFileName(InScriptStruct), Content);
}
