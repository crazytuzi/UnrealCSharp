#include "FClassGenerator.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Engine/UserDefinedEnum.h"
#include "Misc/FileHelper.h"
#include "Mixin/CSharpGeneratedClass.h"
#include "Mixin/CSharpBlueprintGeneratedClass.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Animation/AnimBlueprintGeneratedClass.h"

void FClassGenerator::Generator()
{
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		Generator(*ClassIterator);
	}
}

void FClassGenerator::Generator(const UClass* InClass)
{
	if (InClass == nullptr)
	{
		return;
	}

	if (Cast<UCSharpGeneratedClass>(InClass) || Cast<UCSharpBlueprintGeneratedClass>(InClass))
	{
		return;
	}

	if (Cast<UAnimBlueprintGeneratedClass>(InClass))
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

	auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass);

	if (!FGeneratorCore::IsSupportedModule(NameSpaceContent))
	{
		return;
	}

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InClass);

	auto FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InClass);

	const auto& OverrideFunctions = GetOverrideFunctions(NameSpaceContent, FullClassContent);

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
		auto SuperClassNameSpace = FUnrealCSharpFunctionLibrary::GetClassNameSpace(SuperClass);

		if (!FGeneratorCore::IsSupportedModule(SuperClassNameSpace))
		{
			return;
		}

		if (NameSpaceContent != SuperClassNameSpace)
		{
			UsingNameSpaces.Add(SuperClassNameSpace);
		}

		SuperClassContent = FString::Printf(TEXT(
			" : %s, IStaticClass"
		),
		                                    *FUnrealCSharpFunctionLibrary::GetFullClass(SuperClass));
	}
	else
	{
		SuperClassContent = ": IStaticClass";
	}

	for (auto Interface : InClass->Interfaces)
	{
		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(Interface.Class));

		InterfaceContent = FString::Printf(TEXT(
			", %s"
		),
		                                   *FUnrealCSharpFunctionLibrary::GetFullInterface(Interface.Class));
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

		FString PropertyAccessSpecifiers = TEXT("public");

		auto PropertyType = FGeneratorCore::GetPropertyType(*PropertyIterator);

		auto PropertyName = PropertyIterator->GetName();

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		PropertyContent += FString::Printf(TEXT(
			"\t\t%s %s %s\n"
			"\t\t{\n"
			"\t\t\tget\n"
			"\t\t\t{\n"
			"\t\t\t\tPropertyUtils.GetObjectProperty(this, \"%s\", out %s value);\n"
			"\n"
			"\t\t\t\treturn %s;\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tset => PropertyUtils.SetObjectProperty(this, \"%s\", %s);\n"
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

	FunctionContent = FString::Printf(TEXT(
		"\t\tpublic%s static UClass StaticClass()\n"
		"\t\t{\n"
		"\t\t\tObjectImplementation.Object_StaticClassImplementation(\"%s\", out var __OutValue);\n"
		"\n"
		"\t\t\treturn __OutValue;\n"
		"\t\t}\n"
	),
	                                  SuperClass != nullptr ? TEXT(" new") : TEXT(""),
	                                  *PathNameAttributeContent
	);

	UsingNameSpaces.Add(TEXT("Script.Library"));

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()));

	TArray<UFunction*> Functions;

	for (TFieldIterator<UFunction> FunctionIterator(InClass, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated); FunctionIterator; ++
	     FunctionIterator)
	{
		if (FunctionIterator->HasAnyFunctionFlags(FUNC_Delegate))
		{
			continue;
		}

		if (SuperClass != nullptr && SuperClass->FindFunctionByName(FunctionIterator->GetFName()))
		{
			continue;
		}

		if (OverrideFunctions.Contains(FunctionIterator->GetName()))
		{
			continue;
		}

		Functions.Add(*FunctionIterator);
	}

	for (const auto InInterface : InClass->Interfaces)
	{
		if (SuperClass != nullptr && SuperClass->ImplementsInterface(InInterface.Class))
		{
			continue;
		}

		for (TFieldIterator<UFunction> FunctionIterator(InInterface.Class, EFieldIteratorFlags::IncludeSuper,
		                                                EFieldIteratorFlags::ExcludeDeprecated); FunctionIterator; ++
		     FunctionIterator)
		{
			Functions.Add(*FunctionIterator);
		}
	}

	for (const auto Function : Functions)
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

			if (bIsInterface == false)
			{
				FunctionContent += "\n";
			}
		}

		FString FunctionStatic;

		FString FunctionAccessSpecifiers;

		FString FunctionPolymorphism = TEXT("virtual");

		auto FunctionName = Function->GetName();

		if (bIsInterface == true)
		{
			FunctionPolymorphism = TEXT("");
		}
		else
		{
			FunctionAccessSpecifiers = TEXT("public");

			if (SuperClass != nullptr)
			{
				if (SuperClass->FindFunctionByName(*FunctionName))
				{
					FunctionPolymorphism = TEXT("override");
				}
			}
		}

		auto bIsStatic = Function->HasAnyFunctionFlags(FUNC_Static);

		if (bIsStatic == true)
		{
			FunctionStatic = TEXT("static");

			FunctionPolymorphism = TEXT("");

			UsingNameSpaces.Add(TEXT("System.Reflection"));

			UsingNameSpaces.Add(TEXT("Script.Reflection.Struct"));
		}

		TArray<FProperty*> FunctionParams;

		TArray<int32> FunctionOutParamIndex;

		TArray<int32> FunctionRefParamIndex;

		FProperty* FunctionReturnParam = nullptr;

		for (TFieldIterator<FProperty> ParamIterator(Function); ParamIterator && (ParamIterator->PropertyFlags
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

		auto FunctionComment = Function->GetMetaData(TEXT("Comment"));

		if (!FunctionComment.IsEmpty())
		{
			FunctionComment = FString::Printf(TEXT(
				"\t\t%s"
			),
			                                  *FunctionComment
			);

			FunctionComment = FunctionComment.Replace(TEXT("\n"), TEXT("\n\t\t"));

			FunctionComment = FunctionComment.Replace(TEXT("\n\t\t\t"), TEXT("\n\t\t"));

			if (FunctionComment.EndsWith(TEXT("\t")))
			{
				FunctionComment.RemoveAt(FunctionComment.Len() - 2, 2);
			}
			else if (FunctionComment.EndsWith(TEXT("\t\t")))
			{
				FunctionComment.RemoveAt(FunctionComment.Len() - 4, 4);
			}

			if (!FunctionComment.EndsWith(TEXT("\n")))
			{
				FunctionComment = FString::Printf(TEXT(
					"%s\n"
				), *FunctionComment);
			}
		}

		FString FunctionDeclarationBody;

		TArray<int32> FunctionOutParamIndexMapping;

		FunctionOutParamIndexMapping.AddDefaulted(FunctionParams.Num());

		for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
		{
			if (FunctionParams[Index]->HasAnyPropertyFlags(CPF_OutParm) && !FunctionParams[Index]->HasAnyPropertyFlags(
				CPF_ConstParm))
			{
				if (FunctionParams[Index]->HasAnyPropertyFlags(CPF_ReferenceParm))
				{
					FunctionOutParamIndexMapping[FunctionParams.Num() - 1 - FunctionRefParamIndex.Num()] =
						FunctionRefParamIndex.Num() + FunctionOutParamIndex.Num();

					FunctionRefParamIndex.Emplace(Index);
				}
				else
				{
					FunctionOutParamIndexMapping[FunctionOutParamIndex.Num()] =
						FunctionRefParamIndex.Num() + FunctionOutParamIndex.Num();

					FunctionOutParamIndex.Emplace(Index);
				}
			}
		}

		auto bGeneratorFunctionDefaultParam = GeneratorFunctionDefaultParam(
			FunctionOutParamIndex, FunctionRefParamIndex);

		for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
		{
			if (FunctionOutParamIndex.Contains(Index))
			{
				FunctionDeclarationBody += TEXT("out ");
			}
			else if (FunctionRefParamIndex.Contains(Index))
			{
				FunctionDeclarationBody += TEXT("ref ");
			}

			FunctionDeclarationBody += FString::Printf(TEXT(
				"%s %s%s%s"),
			                                           *FGeneratorCore::GetPropertyType(FunctionParams[Index]),
			                                           *FGeneratorCore::GetName(FunctionParams[Index]->GetName()),
			                                           bGeneratorFunctionDefaultParam
				                                           ? *GetFunctionDefaultParam(
					                                           Function, FunctionParams[Index])
				                                           : TEXT(""),
			                                           Index == FunctionParams.Num() - 1 ? TEXT("") : TEXT(", ")
			);
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"%s%s%s%s%s %s(%s)"
		),
		                                           *FunctionAccessSpecifiers,
		                                           FunctionPolymorphism.IsEmpty()
			                                           ? TEXT(" ")
			                                           : *FString::Printf(TEXT(
				                                           " %s "
			                                           ),
			                                                              *FunctionPolymorphism),
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
				"FunctionUtils.Function_Reflection<%s>(%s, \"%s\", out var __ReturnValue, out var __OutValue"
			),
			FunctionReturnParam != nullptr ? *FGeneratorCore::GetReturnParamType(FunctionReturnParam) : TEXT("Object"),
			bIsStatic == true ? TEXT("StaticClass().GetDefaultObject()") : TEXT("this"),
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
				                                          FunctionParams[FunctionOutParamIndex[Index]],
				                                          FunctionOutParamIndexMapping[Index])));
		}

		for (auto Index = 0; Index < FunctionRefParamIndex.Num(); ++Index)
		{
			if (bIsSafeFunction == true)
			{
				bIsSafeFunction = FGeneratorCore::IsSafeProperty(FunctionParams[FunctionRefParamIndex[Index]]);
			}

			FunctionOutParams.Emplace(FString::Printf(TEXT(
				"%s = %s;"
			),
			                                          *FGeneratorCore::GetName(
				                                          FunctionParams[FunctionRefParamIndex[Index]]->GetName()),
			                                          *FGeneratorCore::GetOutParamString(
				                                          FunctionParams[FunctionRefParamIndex[Index]],
				                                          FunctionOutParamIndexMapping[FunctionParams.Num() - 1 -
					                                          Index])));
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
				"{0}"
				"\t\t{1}\n"
				"\t\t{\n"
				"{2}"
				"\t\t}\n"
			);
		}
		else
		{
			FunctionTab = TEXT("\t\t\t\t");

			UsingNameSpaces.Add(TEXT("IntPtr = Script.Common.IntPtr"));

			FunctionStringFormat = TEXT(
				"{0}"
				"\t\t{1}\n"
				"\t\t{\n"
				"\t\t\tunsafe\n"
				"\t\t\t{\n"
				"{2}"
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

		FStringFormatOrderedArguments StringFormatArgs{
			FunctionComment, FunctionDeclaration, FunctionImplementationBody
		};

		FunctionContent += FString::Format(*FunctionStringFormat, StringFormatArgs);
	}

	if (bIsInterface == true)
	{
		IInterfaceContent = FString::Printf(TEXT(
			"\t[PathName(\"%s\")]\n"
			"\tpublic interface %s%s\n"
			"\t{\n"
			"%s"
			"\t}\n"
		),
		                                    *PathNameAttributeContent,
		                                    *FUnrealCSharpFunctionLibrary::GetFullInterface(InClass),
		                                    SuperClass != nullptr && SuperClass != UObject::StaticClass()
			                                    ? *FString::Printf(TEXT(
				                                    " : %s"
			                                    ),
			                                                       *FUnrealCSharpFunctionLibrary::GetFullInterface(
				                                                       SuperClass))
			                                    : TEXT(""),
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
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *FunctionContent,
	                               bIsInterface ? TEXT("\n") : TEXT(""),
	                               *IInterfaceContent
	);

	auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InClass);

	auto DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGenerationPath(InClass), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

bool FClassGenerator::GeneratorFunctionDefaultParam(const TArray<int32>& InFunctionOutParamIndex,
                                                    const TArray<int32>& InFunctionRefParamIndex)
{
	return InFunctionOutParamIndex.Num() == 0 && InFunctionRefParamIndex.Num() == 0 ||
	(InFunctionOutParamIndex.Num() > InFunctionRefParamIndex.Num()
		 ? InFunctionOutParamIndex[InFunctionOutParamIndex.Num() - 1] == InFunctionOutParamIndex.Num() - 1
		 : InFunctionRefParamIndex[InFunctionRefParamIndex.Num() - 1] == InFunctionRefParamIndex.Num() - 1);
}

FString FClassGenerator::GetFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	if (InFunction == nullptr || InProperty == nullptr)
	{
		return TEXT("");
	}

	if (!InFunction->HasAnyFunctionFlags(FUNC_BlueprintCallable))
	{
		return TEXT("");
	}

	if (Cast<UBlueprintGeneratedClass>(InFunction->GetOuter()))
	{
		return GetBlueprintFunctionDefaultParam(InFunction, InProperty);
	}

	return GetCppFunctionDefaultParam(InFunction, InProperty);
}

FString FClassGenerator::GetCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	const auto Key = FString::Printf(TEXT("CPP_Default_%s"), *InProperty->GetName());

	if (!InFunction->HasMetaData(*Key))
	{
		return TEXT("");
	}

	const auto MetaData = InFunction->GetMetaData(*Key);

	if (const auto ByteProperty = CastField<FByteProperty>(InProperty))
	{
		if (ByteProperty->Enum != nullptr)
		{
			if (MetaData.StartsWith("Type::"))
			{
				return FString::Printf(TEXT(" = %s.%s"), *ByteProperty->Enum->GetName(),
				                       *MetaData.Right(MetaData.Len() - 6));
			}
			else
			{
				const auto EnumName = ByteProperty->Enum->GetName();

				// @TODO
				if (EnumName == TEXT("ECollisionChannel"))
				{
					return FString::Printf(TEXT(" = %s.%s"), *EnumName,
					                       *UCollisionProfile::Get()->ReturnChannelNameFromContainerIndex(
						                       ByteProperty->Enum->GetIndexByName(*MetaData)).ToString());
				}

				return FString::Printf(TEXT(" = %s.%s"), *EnumName, *MetaData);
			}
		}
		else
		{
			return FString::Printf(TEXT(" = %s"), *MetaData);
		}
	}

	if (CastField<FIntProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), *MetaData);
	}

	if (CastField<FInt64Property>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), *MetaData);
	}

	if (CastField<FBoolProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), *MetaData);
	}

	if (CastField<FFloatProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %sf"), *MetaData);
	}

	if (CastField<FClassProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FObjectProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FNameProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FStructProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s.%s"), *EnumProperty->GetEnum()->GetName(), *MetaData);
	}

	if (CastField<FStrProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FTextProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FSoftClassProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FSoftObjectProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FDoubleProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), *MetaData);
	}

	return TEXT("");
}

FString FClassGenerator::GetBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	if (InProperty->HasAnyPropertyFlags(CPF_OutParm) && !InProperty->HasAnyPropertyFlags(CPF_ConstParm))
	{
		return TEXT("");
	}

	const auto Key = InProperty->GetName();

	const auto MetaData = InFunction->GetMetaData(*Key);

	if (const auto ByteProperty = CastField<FByteProperty>(InProperty))
	{
		if (ByteProperty->Enum != nullptr)
		{
			if (const auto UserDefinedEnum = Cast<UUserDefinedEnum>(ByteProperty->Enum))
			{
				return FString::Printf(TEXT(" = %s.%s"), *ByteProperty->Enum->GetName(),
				                       *UserDefinedEnum->GetDisplayNameTextByIndex(
					                       UserDefinedEnum->GetIndexByNameString(MetaData)).ToString());
			}
			else
			{
				return FString::Printf(TEXT(" = %s.%s"), *ByteProperty->Enum->GetName(), *MetaData);
			}
		}
		else
		{
			return FString::Printf(TEXT(" = %s"), MetaData.IsEmpty() ? TEXT("0") : *MetaData);
		}
	}

	if (CastField<FIntProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), MetaData.IsEmpty() ? TEXT("0") : *MetaData);
	}

	if (CastField<FInt64Property>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), MetaData.IsEmpty() ? TEXT("0") : *MetaData);
	}

	if (CastField<FBoolProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), MetaData.IsEmpty() ? TEXT("false") : *MetaData);
	}

	if (CastField<FFloatProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %sf"), MetaData.IsEmpty() ? TEXT("0") : *MetaData);
	}

	if (CastField<FClassProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FObjectProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FNameProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FStructProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FArrayProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FStrProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FTextProperty>(InProperty))
	{
		// @TODO

		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FSoftClassProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FSoftObjectProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FDoubleProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s"), MetaData.IsEmpty() ? TEXT("0") : *MetaData);
	}

	if (CastField<FMapProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FSetProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	return TEXT("");
}

TArray<FString> FClassGenerator::GetOverrideFunctions(const FString& InNameSpace, const FString& InClass)
{
	const auto FileName = FString::Printf(TEXT(
		"%s/%s.%s.json"
	),
	                                      *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
	                                      *InNameSpace,
	                                      *InClass
	);

	auto& FileManager = IFileManager::Get();

	if (!FileManager.FileExists(*FileName))
	{
		return {};
	}

	FString JsonStr;

	if (FFileHelper::LoadFileToString(JsonStr, *FileName))
	{
		TSharedPtr<FJsonObject> JsonObj;

		TArray<FString> OverrideFunctions;

		const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

		FJsonSerializer::Deserialize(JsonReader, JsonObj);

		JsonObj->TryGetStringArrayField(TEXT("Override"), OverrideFunctions);

		return OverrideFunctions;
	}

	return {};
}
