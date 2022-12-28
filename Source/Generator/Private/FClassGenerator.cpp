#include "FClassGenerator.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"

void FClassGenerator::Generator()
{
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		Generator(*ClassIterator);
	}
}

void FClassGenerator::Generator(UClass* InClass)
{
	if (InClass == nullptr)
	{
		return;
	}

	auto ClassName = InClass->GetName();

	if (ClassName.StartsWith(TEXT("SKEL_")) || ClassName.StartsWith(TEXT("PLACEHOLDER-CLASS")) ||
		ClassName.StartsWith(TEXT("REINST_")) || ClassName.StartsWith(TEXT("TRASHCLASS_")) ||
		ClassName.StartsWith(TEXT("HOTRELOADED_")))
	{
		return;
	}

	FString UsingNameSpaceContent;

	auto NameSpaceContent = FGeneratorCore::GetClassNameSpace(InClass);

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InClass);

	auto FullClassContent = FGeneratorCore::GetFullClass(InClass);

	FString SuperClassContent;

	FString InterfaceContent;

	FString PropertyContent;

	FString FunctionContent;

	FString InterfaceFunction;

	FString IInterfaceContent;

	auto bIsInterface = InClass->IsChildOf(UInterface::StaticClass());

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common")};

	auto SuperClass = InClass->GetSuperClass();

	if (SuperClass != nullptr)
	{
		auto SuperClassNameSpace = FGeneratorCore::GetClassNameSpace(SuperClass);

		if (NameSpaceContent != SuperClassNameSpace)
		{
			UsingNameSpaces.Add(SuperClassNameSpace);
		}

		SuperClassContent = FString::Printf(TEXT(
			" : %s"
		),
		                                    *FGeneratorCore::GetFullClass(SuperClass));
	}

	for (auto Interface : InClass->Interfaces)
	{
		UsingNameSpaces.Add(FGeneratorCore::GetClassNameSpace(Interface.Class));

		InterfaceContent = FString::Printf(TEXT(
			", %s"
		),
		                                   *GetFullInterface(Interface.Class));
	}

	auto bHasProperty = false;

	for (TFieldIterator<FProperty> PropertyIterator(InClass, EFieldIteratorFlags::ExcludeSuper,
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

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		FString PropertyAccessSpecifiers = TEXT("public");

		auto PropertyType = FGeneratorCore::GetPropertyType(*PropertyIterator);

		auto PropertyName = PropertyIterator->GetName();

		PropertyContent += FString::Printf(TEXT(
			"\t\t%s %s %s\n"
			"\t\t{\n"
			"\t\t\tget\n"
			"\t\t\t{\n"
			"\t\t\t\tPropertyUtils.GetProperty(this, \"%s\", out %s value);\n"
			"\n"
			"\t\t\t\treturn %s;\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tset => PropertyUtils.SetProperty(this, \"%s\", %s);\n"
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

	auto bHasFunction = false;

	TArray<FString> FunctionDeclarations;

	for (TFieldIterator<UFunction> FunctionIterator(InClass, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated,
	                                                EFieldIteratorFlags::IncludeInterfaces); FunctionIterator; ++
	     FunctionIterator)
	{
		if (bHasFunction == true)
		{
			if (bIsInterface == true)
			{
				InterfaceFunction += "\n";
			}
			else
			{
				FunctionContent += "\n";
			}
		}
		else
		{
			bHasFunction = true;
		}

		FString FunctionNew;

		FString FunctionStatic;

		FString FunctionAccessSpecifiers;

		if (bIsInterface == false)
		{
			FunctionAccessSpecifiers = TEXT("public");

			if (SuperClass != nullptr)
			{
				if (SuperClass->FindFunctionByName(*FunctionIterator->GetName()))
				{
					FunctionNew = TEXT("new");
				}
			}
		}

		auto bIsStatic = FunctionIterator->HasAnyFunctionFlags(FUNC_Static);

		if (bIsStatic == true)
		{
			FunctionStatic = TEXT("static");

			UsingNameSpaces.Add(TEXT("System.Reflection"));

			UsingNameSpaces.Add(TEXT("Script.Reflection.Struct"));
		}

		TArray<FProperty*> FunctionParams;

		TArray<int32> FunctionOutParamIndex;

		FProperty* FunctionReturnParam = nullptr;

		for (TFieldIterator<FProperty> ParamIterator(*FunctionIterator); ParamIterator && (ParamIterator->PropertyFlags
			     & CPF_Parm); ++ParamIterator)
		{
			FDelegateGenerator::Generator(*ParamIterator);

			if (ParamIterator->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				FunctionReturnParam = *ParamIterator;
			}
			else
			{
				FunctionParams.Emplace(*ParamIterator);
			}

			UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*ParamIterator));
		}

		FString FunctionReturnType = TEXT("void");

		if (FunctionReturnParam != nullptr)
		{
			FunctionReturnType = FGeneratorCore::GetPropertyType(FunctionReturnParam);
		}

		auto FunctionName = FunctionIterator->GetName();

		FString FunctionDeclarationBody;

		for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
		{
			if (FunctionParams[Index]->HasAnyPropertyFlags(CPF_OutParm) && !FunctionParams[Index]->HasAnyPropertyFlags(
				CPF_ConstParm))
			{
				FunctionOutParamIndex.Emplace(Index);

				FunctionDeclarationBody += TEXT("out ");
			}

			FunctionDeclarationBody += FString::Printf(TEXT(
				"%s %s%s"),
			                                           *FGeneratorCore::GetPropertyType(FunctionParams[Index]),
			                                           *FGeneratorCore::GetName(FunctionParams[Index]->GetName()),
			                                           Index == FunctionParams.Num() - 1 ? TEXT("") : TEXT(", ")
			);
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"%s%s%s%s%s%s%s %s(%s)"
		),
		                                           *FunctionAccessSpecifiers,
		                                           bIsInterface == true ? TEXT("") : TEXT(" "),
		                                           *FunctionNew,
		                                           FunctionNew.IsEmpty() == true ? TEXT("") : TEXT(" "),
		                                           *FunctionStatic,
		                                           FunctionStatic.IsEmpty() == true ? TEXT("") : TEXT(" "),
		                                           *FunctionReturnType,
		                                           *FGeneratorCore::GetName(FunctionName),
		                                           *FunctionDeclarationBody
		);

		if (FunctionDeclarations.Contains(FunctionDeclaration))
		{
			continue;
		}

		FunctionDeclarations.Emplace(FunctionDeclaration);

		if (bIsInterface == true)
		{
			InterfaceFunction += FString::Printf(TEXT(
				"\t\t%s;\n"
			),
			                                     *FunctionDeclaration);

			continue;
		}

		auto FunctionCallBody = FString::Printf(
			TEXT(
				"FunctionUtils.%s<%s>(%s, \"%s\", out var __ReturnValue, out var __OutValue"
			),
			bIsStatic == true ? TEXT("Function_ReflectionStatic") : TEXT("Function_ReflectionMember"),
			FunctionReturnParam != nullptr ? *FGeneratorCore::GetReturnParamType(FunctionReturnParam) : TEXT("Object"),
			bIsStatic == true
				? *FString::Printf(
					TEXT(
						"typeof(%s).GetCustomAttribute<PathNameAttribute>(true).PathName"
					),
					*FGeneratorCore::GetFullClass(InClass))
				: TEXT("this"),
			*FunctionName);

		for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
		{
			if (FunctionOutParamIndex.Contains(Index) == false)
			{
				FunctionCallBody += ", " + FGeneratorCore::GetParamName(FunctionParams[Index]);
			}
		}

		FunctionCallBody += TEXT(");");

		auto bIsSafeFunction = true;

		TArray<FString> FunctionOutParams;

		for (auto Index = 0; Index < FunctionOutParamIndex.Num(); ++Index)
		{
			if (bIsSafeFunction == true)
			{
				bIsSafeFunction = FGeneratorCore::IsSafeProperty(FunctionParams[FunctionOutParamIndex[Index]]);
			}

			FunctionOutParams.Emplace(FString::Printf(TEXT(
				"%s = %s;"
			),
			                                          *FGeneratorCore::GetName(
				                                          FunctionParams[FunctionOutParamIndex[Index]]->GetName()),
			                                          *FGeneratorCore::GetOutParamString(
				                                          FunctionParams[FunctionOutParamIndex[Index]], Index)));
		}

		FString FunctionReturnParamBody;

		if (FunctionReturnParam != nullptr)
		{
			FunctionReturnParamBody = FString::Printf(TEXT(
				"return %s;"
			),
			                                          *FGeneratorCore::GetReturnParamName(FunctionReturnParam));
		}

		FString FunctionTab;

		FString FunctionStringFormat;

		if (bIsSafeFunction == true)
		{
			FunctionTab = TEXT("\t\t\t");

			FunctionStringFormat = TEXT(
				"\t\t{0}\n"
				"\t\t{\n"
				"{1}"
				"\t\t}\n"
			);
		}
		else
		{
			FunctionTab = TEXT("\t\t\t\t");

			UsingNameSpaces.Add(TEXT("IntPtr = Script.Common.IntPtr"));

			FunctionStringFormat = TEXT(
				"\t\t{0}\n"
				"\t\t{\n"
				"\t\t\tunsafe\n"
				"\t\t\t{\n"
				"{1}"
				"\t\t\t}\n"
				"\t\t}\n"
			);
		}

		FString FunctionOutParamBody;

		for (auto FunctionOutParam : FunctionOutParams)
		{
			FunctionOutParamBody += FString::Printf(TEXT(
				"\n%s%s\n"
			),
			                                        *FunctionTab,
			                                        *FunctionOutParam);
		}

		auto FunctionImplementationBody = FString::Printf(TEXT(
			"%s%s\n"
			"%s"
			"%s"
			"%s"
		),
		                                                  *FunctionTab,
		                                                  *FunctionCallBody,
		                                                  *FunctionOutParamBody,
		                                                  FunctionReturnParamBody.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                                  FunctionReturnParamBody.IsEmpty()
			                                                  ? TEXT("")
			                                                  : *FString::Printf(
				                                                  TEXT(
					                                                  "%s%s\n"
				                                                  ),
				                                                  *FunctionTab,
				                                                  *FunctionReturnParamBody));

		FStringFormatOrderedArguments StringFormatArgs{FunctionDeclaration, FunctionImplementationBody};

		FunctionContent += FString::Format(*FunctionStringFormat, StringFormatArgs);
	}

	if (bIsInterface == true)
	{
		IInterfaceContent = FString::Printf(TEXT(
			"\tpublic interface %s\n"
			"\t{\n"
			"%s"
			"\t}\n"
		),
		                                    *GetFullInterface(InClass),
		                                    *InterfaceFunction);
	}
	else
	{
		if (bHasFunction == true)
		{
			UsingNameSpaces.Add(TEXT("Script.Reflection.Function"));
		}
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
		"\tpublic partial class %s%s%s\n"
		"\t{\n"
		"%s"
		"%s"
		"%s"
		"\t}\n"
		"%s"
		"%s"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *PathNameAttributeContent,
	                               *FullClassContent,
	                               *SuperClassContent,
	                               *InterfaceContent,
	                               *PropertyContent,
	                               bHasProperty == true && bHasFunction == true ? TEXT("\n") : TEXT(""),
	                               *FunctionContent,
	                               bIsInterface ? TEXT("\n") : TEXT(""),
	                               *IInterfaceContent
	);

	auto ModuleName = FGeneratorCore::GetModuleName(InClass);

	auto DirectoryName = FPaths::Combine(FGeneratorCore::GetBasePath(), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

FString FClassGenerator::GetFullInterface(const UStruct* InStruct)
{
	return FString::Printf(TEXT(
		"I%s"
	),
	                       *FGeneratorCore::GetFullClass(InStruct).RightChop(1));
}
