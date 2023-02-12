﻿#include "FStructGenerator.h"
#include "FDelegateGenerator.h"
#include "FEnumGenerator.h"
#include "FGeneratorCore.h"
#include "FGeneratorPaths.h"
#include "Engine/UserDefinedStruct.h"
#include "Kismet2/StructureEditorUtils.h"

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

	auto NameSpaceContent = FGeneratorCore::GetClassNameSpace(InScriptStruct);

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InScriptStruct);

	auto FullClassContent = FGeneratorCore::GetFullClass(InScriptStruct);

	FString SuperStructContent;

	FString ConstructorContent;

	FString DestructorContent;

	FString PropertyContent;

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common")};

	auto SuperStruct = InScriptStruct->GetSuperStruct();

	if (SuperStruct != nullptr)
	{
		auto SuperStructNameSpace = FGeneratorCore::GetClassNameSpace(SuperStruct);

		if (NameSpaceContent != SuperStructNameSpace)
		{
			UsingNameSpaces.Add(SuperStructNameSpace);
		}

		SuperStructContent = FString::Printf(TEXT(
			" : %s"
		),
		                                     *FGeneratorCore::GetFullClass(SuperStruct));

		ConstructorContent = FString::Printf(TEXT(
			"\t\tpublic %s()\n"
			"\t\t{\n"
			"\t\t}\n"
			"\n"
			"\t\tprotected %s(Type InValue) : base(InValue)\n"
			"\t\t{\n"
			"\t\t}\n"
		),
		                                     *FGeneratorCore::GetFullClass(InScriptStruct),
		                                     *FGeneratorCore::GetFullClass(InScriptStruct)
		);
	}
	else
	{
		ConstructorContent = FString::Printf(TEXT(
			"\t\tpublic %s() => "
			"StructUtils.Struct_Register(this, GetType().GetCustomAttribute<PathNameAttribute>(true).PathName);\n"
			"\n"
			"\t\tprotected %s(Type InValue)\n"
			"\t\t{\n"
			"\t\t}\n"
		),
		                                     *FGeneratorCore::GetFullClass(InScriptStruct),
		                                     *FGeneratorCore::GetFullClass(InScriptStruct)
		);

		DestructorContent = FString::Printf(TEXT(
			"\t\t~%s() => StructUtils.Struct_UnRegister(this);\n"
		),
		                                    *FGeneratorCore::GetFullClass(InScriptStruct)
		);

		UsingNameSpaces.Add(TEXT("System.Reflection"));

		UsingNameSpaces.Add(TEXT("Script.Reflection.Struct"));
	}

	auto bHasProperty = false;

	for (TFieldIterator<FProperty> PropertyIterator(InScriptStruct, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated); PropertyIterator; ++
	     PropertyIterator)
	{
		FDelegateGenerator::Generator(*PropertyIterator);

		if(FEnumProperty* EnumProperty = Cast<FEnumProperty>(*PropertyIterator))
		{
			FEnumGenerator::EmplaceEnumUnderlyingCache(EnumProperty->GetEnum(), EnumProperty->GetUnderlyingProperty());
		}
		
		if (bHasProperty == true)
		{
			PropertyContent += "\n";
		}
		else
		{
			bHasProperty = true;
		}

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		FString PropertyAccessSpecifiers = TEXT("public");

		auto PropertyType = FGeneratorCore::GetPropertyType(*PropertyIterator);

		auto PropertyName = PropertyIterator->GetName();

		if(UserDefinedStruct != nullptr)
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
		"%s"
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
	                               *ConstructorContent,
	                               ConstructorContent.IsEmpty() == true ? TEXT("") : TEXT("\n"),
	                               *DestructorContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyContent
	);

	auto ModuleName = FGeneratorCore::GetModuleName(InScriptStruct);

	auto DirectoryName = FPaths::Combine(FGeneratorPaths::GetGenerationPath(InScriptStruct->GetPackage()->GetName()), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
