#include "FStructGenerator.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Engine/UserDefinedStruct.h"
#include "Kismet2/StructureEditorUtils.h"
#include "FUnrealCSharpFunctionLibrary.h"

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

	auto ClassName = InScriptStruct->GetName();

	if (ClassName.StartsWith(TEXT("STRUCT_REINST_")))
	{
		return;
	}

	auto UserDefinedStruct = Cast<UUserDefinedStruct>(InScriptStruct);

	FString UsingNameSpaceContent;

	auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InScriptStruct);

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InScriptStruct);

	auto FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InScriptStruct);

	FString SuperStructContent;

	FString ConstructorContent;

	FString DestructorContent;

	FString PropertyContent;

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common")};

	auto SuperStruct = InScriptStruct->GetSuperStruct();

	if (SuperStruct != nullptr)
	{
		auto SuperStructNameSpace = FUnrealCSharpFunctionLibrary::GetClassNameSpace(SuperStruct);

		if (NameSpaceContent != SuperStructNameSpace)
		{
			UsingNameSpaces.Add(SuperStructNameSpace);
		}

		SuperStructContent = FString::Printf(TEXT(
			" : %s"
		),
		                                     *FUnrealCSharpFunctionLibrary::GetFullClass(SuperStruct));

		ConstructorContent = FString::Printf(TEXT(
			"\t\tpublic %s() : base(typeof(%s)) => StructUtils.Struct_Register(this, \"%s\");\n"
			"\n"
			"\t\tprotected %s(Type InValue) : base(InValue)\n"
			"\t\t{\n"
			"\t\t}\n"
		),
		                                     *FullClassContent,
		                                     *FullClassContent,
		                                     *PathNameAttributeContent,
		                                     *FullClassContent
		);
	}
	else
	{
		ConstructorContent = FString::Printf(TEXT(
			"\t\tpublic %s() => StructUtils.Struct_Register(this, \"%s\");\n"
			"\n"
			"\t\tprotected %s(Type InValue)\n"
			"\t\t{\n"
			"\t\t}\n"
		),
		                                     *FullClassContent,
		                                     *PathNameAttributeContent,
		                                     *FullClassContent
		);

		DestructorContent = FString::Printf(TEXT(
			"\n\t\t~%s() => StructUtils.Struct_UnRegister(this);\n"
		),
		                                    *FullClassContent
		);
	}

	auto StaticStructContent = FString::Printf(TEXT(
		"\t\tpublic%s static UScriptStruct StaticStruct()\n"
		"\t\t{\n"
		"\t\t\tStructUtils.Struct_StaticStruct(\"%s\", out var __OutValue);\n"
		"\n"
		"\t\t\treturn __OutValue;\n"
		"\t\t}\n"
	),
	                                           SuperStruct != nullptr ? TEXT(" new") : TEXT(""),
	                                           *PathNameAttributeContent
	);

	UsingNameSpaces.Add(TEXT("Script.Reflection.Struct"));

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UScriptStruct::StaticClass()));

	auto bHasProperty = false;

	for (TFieldIterator<FProperty> PropertyIterator(InScriptStruct, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated); PropertyIterator; ++
	     PropertyIterator)
	{
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

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		if (UserDefinedStruct != nullptr)
		{
			PropertyName = FStructureEditorUtils::GetVariableFriendlyNameForProperty(
				UserDefinedStruct, *PropertyIterator);
		}

		PropertyContent += FString::Printf(TEXT(
			"\t\t%s %s %s\n"
			"\t\t{\n"
			"\t\t\tget\n"
			"\t\t\t{\n"
			"\t\t\t\tPropertyUtils.GetStructProperty(this, \"%s\", out %s value);\n"
			"\n"
			"\t\t\t\treturn %s;\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tset => PropertyUtils.SetStructProperty(this, \"%s\", %s);\n"
			"\t\t}\n"
		),
		                                   *PropertyAccessSpecifiers,
		                                   *PropertyType,
		                                   *FGeneratorCore::GetName(PropertyName),
		                                   *PropertyName,
		                                   *FGeneratorCore::GetGetAccessorType(*PropertyIterator),
		                                   *FGeneratorCore::GetGetAccessorReturnParamName(*PropertyIterator),
		                                   *PropertyName,
		                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator)
		);
	}

	if (bHasProperty == true)
	{
		UsingNameSpaces.Add(TEXT("Script.Reflection.Property"));
	}

	UsingNameSpaces.Remove(UsingNameSpaceContent);

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
		"%s"
		"%s"
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *PathNameAttributeContent,
	                               *FullClassContent,
	                               *SuperStructContent,
	                               *StaticStructContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyContent
	);

	auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InScriptStruct);

	auto DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGenerationPath(InScriptStruct), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
