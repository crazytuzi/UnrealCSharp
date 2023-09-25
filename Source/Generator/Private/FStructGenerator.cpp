#include "FStructGenerator.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Engine/UserDefinedStruct.h"
#include "Kismet2/StructureEditorUtils.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Mixin/CSharpScriptStruct.h"

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

	if (Cast<UCSharpScriptStruct>(InScriptStruct))
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

	if (!FGeneratorCore::IsSupportedModule(NameSpaceContent))
	{
		return;
	}

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InScriptStruct);

	auto FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InScriptStruct);

	FString SuperStructContent;

	FString ConstructorContent;

	FString DestructorContent;

	FString PropertyContent;

	FString PropertyNameContent;

	FString GCHandleContent;

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common")};

	auto SuperStruct = InScriptStruct->GetSuperStruct();

	if (SuperStruct != nullptr)
	{
		auto SuperStructNameSpace = FUnrealCSharpFunctionLibrary::GetClassNameSpace(SuperStruct);

		if (!FGeneratorCore::IsSupportedModule(SuperStructNameSpace))
		{
			return;
		}

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
			"\n\t\t~%s() => StructUtils.Struct_UnRegister(GetHandle());\n"
		),
		                                    *FullClassContent
		);

		GCHandleContent = TEXT(
			"\t\tpublic unsafe void SetHandle(void* InHandle)\n"
			"\t\t{\n"
			"\t\t\tGCHandle = new IntPtr(InHandle);\n"
			"\t\t}\n"
			"\n"
			"\t\tpublic IntPtr GetHandle()\n"
			"\t\t{\n"
			"\t\t\treturn GCHandle;\n"
			"\t\t}\n"
			"\n"
			"\t\tprivate IntPtr GCHandle;\n");

		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));
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

	TArray<TPair<FString, FString>> PropertyNames;

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

		if (!FGeneratorCore::IsSafeProperty(*PropertyIterator))
		{
			PropertyContent += FString::Printf(TEXT(
				"\t\t%s %s %s\n"
				"\t\t{\n"
				"\t\t\tget\n"
				"\t\t\t{\n"
				"\t\t\t\tPropertyUtils.GetStructProperty(GetHandle(), %s, out %s value);\n"
				"\n"
				"\t\t\t\treturn %s;\n"
				"\t\t\t}\n"
				"\n"
				"\t\t\tset => PropertyUtils.SetStructProperty(GetHandle(), %s, %s);\n"
				"\t\t}\n"
			),
			                                   *PropertyAccessSpecifiers,
			                                   *PropertyType,
			                                   *FGeneratorCore::GetName(VariableFriendlyPropertyName),
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetGetAccessorType(*PropertyIterator),
			                                   *FGeneratorCore::GetGetAccessorReturnParamName(*PropertyIterator),
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator)
			);
		}
		else
		{
			PropertyContent += FString::Printf(TEXT(
				"\t\t%s %s %s\n"
				"\t\t{\n"
				"\t\t\tget\n"
				"\t\t\t{\n"
				"\t\t\t\tPropertyUtils.GetStructProperty(GetHandle(), %s, out Object value);\n"
				"\n"
				"\t\t\t\treturn %s as %s;\n"
				"\t\t\t}\n"
				"\n"
				"\t\t\tset => PropertyUtils.SetStructProperty(GetHandle(), %s, %s);\n"
				"\t\t}\n"
			),
			                                   *PropertyAccessSpecifiers,
			                                   *PropertyType,
			                                   *FGeneratorCore::GetName(VariableFriendlyPropertyName),
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetGetAccessorReturnParamName(*PropertyIterator),
			                                   *FGeneratorCore::GetGetAccessorType(*PropertyIterator),
			                                   *PropertyNames[PropertyNames.Num() - 1].Key,
			                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator)
			);
		}
	}

	if (bHasProperty == true)
	{
		UsingNameSpaces.Add(TEXT("Script.Reflection.Property"));
	}

	for (auto Index = 0; Index < PropertyNames.Num(); ++Index)
	{
		PropertyNameContent += FString::Printf(TEXT(
			"%s\t\tprivate static string %s = new string(\"%s\");\n"
		),
		                                       Index == 0 ? TEXT("") : TEXT("\n"),
		                                       *PropertyNames[Index].Key,
		                                       *PropertyNames[Index].Value
		);
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
	                               *FullClassContent,
	                               SuperStruct != nullptr ? *SuperStructContent : TEXT(" : IGCHandle"),
	                               *StaticStructContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyNameContent,
	                               *GCHandleContent
	);

	auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InScriptStruct);

	auto DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGenerationPath(InScriptStruct), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
