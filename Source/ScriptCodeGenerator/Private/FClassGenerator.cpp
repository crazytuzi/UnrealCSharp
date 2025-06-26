#include "FClassGenerator.h"
#include "FDoxygenConverter.h"
#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Engine/UserDefinedEnum.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Binding/Class/FBindingClass.h"
#include "Containers/ArrayBuilder.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "ScriptCodeGeneratorMacro.h"
#include "Dynamic/FDynamicGenerator.h"

void FClassGenerator::Generator()
{
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		if (!Cast<UBlueprintGeneratedClass>(*ClassIterator))
		{
			Generator(*ClassIterator);
		}
	}
}

void FClassGenerator::Generator(const UClass* InClass)
{
	if (InClass == nullptr)
	{
		return;
	}

	if (FDynamicGenerator::IsDynamicClass(InClass))
	{
		return;
	}

	if (Cast<UAnimBlueprintGeneratedClass>(InClass))
	{
		return;
	}

	if (FGeneratorCore::IsSkip(InClass))
	{
		return;
	}

	if (!FGeneratorCore::IsSupported(InClass))
	{
		return;
	}

	if (FUnrealCSharpFunctionLibrary::IsSpecialClass(InClass))
	{
		return;
	}

	if (FUnrealCSharpFunctionLibrary::IsDynamicReInstanceField(InClass))
	{
		return;
	}

	FString UsingNameSpaceContent;

	auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass);

	auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InClass);

	auto ClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InClass);

	const auto& OverrideFunctions = FGeneratorCore::GetOverrideFunctions(NameSpaceContent, ClassContent);

	const auto& BindingFunctions = FBindingClass::GetFunctionNames(ClassContent);

	const auto& BindingProperties = FBindingClass::GetPropertyNames(ClassContent);

	FString SuperClassContent;

	FString InterfaceContent;

	FString PropertyContent;

	FString FunctionContent;

	FString InterfaceFunction;

	FString IInterfaceContent;

	FString PropertyNameContent;

	FString FunctionNameContent;

	auto bIsInterface = InClass->IsChildOf(UInterface::StaticClass());

	TSet<FString> UsingNameSpaces{COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)};

	auto SuperClass = InClass->GetSuperClass();

	if (SuperClass != nullptr)
	{
		if (auto SuperClassNameSpace = FUnrealCSharpFunctionLibrary::GetClassNameSpace(SuperClass);
			NameSpaceContent != SuperClassNameSpace)
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

		InterfaceContent += FString::Printf(TEXT(
			", %s"
		),
		                                    *FUnrealCSharpFunctionLibrary::GetFullInterface(Interface.Class));
	}

	auto bHasProperty = false;

	TSet<FString> PropertyNameSet;

	for (TFieldIterator<FProperty> PropertyIterator(InClass, EFieldIteratorFlags::ExcludeSuper,
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

		auto EncodePropertyName = FUnrealCSharpFunctionLibrary::Encode(*PropertyIterator);

		auto DummyPropertyName = FString::Printf(TEXT(
			"__%s"
		),
		                                         *EncodePropertyName
		);

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*PropertyIterator));

		PropertyContent += FString::Printf(TEXT(
			"\t\t%s %s %s\n"
			"\t\t{\n"
			"\t\t\tget\n"
			"\t\t\t{\n"
			"\t\t\t\tunsafe\n"
			"\t\t\t\t{\n"
			"\t\t\t\t\tvar %s = stackalloc byte[%d];\n"
			"\n"
			"\t\t\t\t\tFPropertyImplementation.FProperty_GetObjectPropertyImplementation(%s, %s, %s);\n"
			"\n"
			"\t\t\t\t\treturn *(%s*)%s;\n"
			"\t\t\t\t}\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tset\n"
			"\t\t\t{\n"
			"\t\t\t\tunsafe\n"
			"\t\t\t\t{\n"
			"\t\t\t\t\tvar %s = stackalloc byte[%d];\n"
			"\n"
			"\t\t\t\t\t*(%s*)%s = %s;\n"
			"\n"
			"\t\t\t\t\tFPropertyImplementation.FProperty_SetObjectPropertyImplementation(%s, %s, %s);\n"
			"\t\t\t\t}\n"
			"\t\t\t}\n"
			"\t\t}\n"
		),
		                                   *PropertyAccessSpecifiers,
		                                   *PropertyType,
		                                   *EncodePropertyName,
		                                   RETURN_BUFFER_TEXT,
		                                   FGeneratorCore::GetBufferSize(*PropertyIterator),
		                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                   *DummyPropertyName,
		                                   RETURN_BUFFER_TEXT,
		                                   *PropertyType,
		                                   RETURN_BUFFER_TEXT,
		                                   IN_BUFFER_TEXT,
		                                   FGeneratorCore::GetBufferSize(*PropertyIterator),
		                                   *FGeneratorCore::GetBufferCast(*PropertyIterator),
		                                   IN_BUFFER_TEXT,
		                                   *FGeneratorCore::GetSetAccessorParamName(*PropertyIterator),
		                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                   *DummyPropertyName,
		                                   IN_BUFFER_TEXT
		);

		PropertyNameContent += FString::Printf(TEXT(
			"%s\t\tprivate static uint %s = 0;\n"
		),
		                                       PropertyNameSet.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                       *DummyPropertyName
		);

		PropertyNameSet.Add(PropertyName);
	}

	auto bHasFunction = false;

	TSet<FString> FunctionNameSet;

	FunctionContent = FString::Printf(TEXT(
		"\t\tpublic%s static UClass StaticClass()\n"
		"\t\t{\n"
		"\t\t\treturn StaticClassSingleton \?\?= UObjectImplementation.UObject_StaticClassImplementation(\"%s\");\n"
		"\t\t}\n\n"
		"\t\tprivate static UClass StaticClassSingleton { get; set; }\n"
	),
	                                  SuperClass != nullptr ? TEXT(" new") : TEXT(""),
	                                  *PathNameAttributeContent
	);

	UsingNameSpaces.Add(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LIBRARY));

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()));

	TArray<TTuple<bool, FString, FString, UFunction*>> Functions;

	for (const auto& InInterface : InClass->Interfaces)
	{
		if (SuperClass != nullptr && SuperClass->ImplementsInterface(InInterface.Class))
		{
			continue;
		}

		for (TFieldIterator<UFunction> FunctionIterator(InInterface.Class, EFieldIteratorFlags::IncludeSuper,
		                                                EFieldIteratorFlags::ExcludeDeprecated); FunctionIterator; ++
		     FunctionIterator)
		{
			const auto& FunctionName = FunctionIterator->GetName();

			const auto& EncodeFunctionName = FUnrealCSharpFunctionLibrary::Encode(*FunctionIterator);

			if (FunctionNameSet.Contains(FunctionName))
			{
				continue;
			}

			if (!FGeneratorCore::IsSupported(*FunctionIterator))
			{
				continue;
			}

			FunctionNameSet.Add(FunctionName);

			if (OverrideFunctions.Contains(EncodeFunctionName))
			{
				if (FUnrealCSharpFunctionLibrary::EnableCallOverrideFunction())
				{
					Functions.Emplace(true,
					                  FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(FunctionName),
					                  FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(EncodeFunctionName),
					                  *FunctionIterator);
				}
			}
			else
			{
				Functions.Emplace(false, FunctionName, EncodeFunctionName, *FunctionIterator);
			}
		}
	}

	for (TFieldIterator<UFunction> FunctionIterator(InClass, EFieldIteratorFlags::ExcludeSuper,
	                                                EFieldIteratorFlags::ExcludeDeprecated); FunctionIterator; ++
	     FunctionIterator)
	{
		if (!FunctionIterator->HasAnyFunctionFlags(FUNC_AccessSpecifiers | FUNC_BlueprintEvent))
		{
			continue;
		}

		const auto& FunctionName = FunctionIterator->GetName();

		const auto& EncodeFunctionName = FUnrealCSharpFunctionLibrary::Encode(*FunctionIterator);

		if (FunctionNameSet.Contains(FunctionName))
		{
			continue;
		}

		if (FunctionIterator->HasAnyFunctionFlags(FUNC_Delegate))
		{
			continue;
		}

		if (BindingFunctions.Contains(FunctionName))
		{
			continue;
		}

		if (!FGeneratorCore::IsSupported(*FunctionIterator))
		{
			continue;
		}

		FunctionNameSet.Add(FunctionName);

		if (OverrideFunctions.Contains(EncodeFunctionName))
		{
			if (FUnrealCSharpFunctionLibrary::EnableCallOverrideFunction())
			{
				Functions.Emplace(true,
				                  FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(FunctionName),
				                  FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(EncodeFunctionName),
				                  *FunctionIterator);
			}
		}
		else
		{
			Functions.Emplace(false, FunctionName, EncodeFunctionName, *FunctionIterator);
		}
	}

	FunctionNameSet.Empty();

	for (const auto& [bIsOverrideFunction, FunctionName, EncodeFunctionName, Function] : Functions)
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

		if (bIsInterface == true)
		{
			FunctionPolymorphism = TEXT("");
		}
		else
		{
			FunctionAccessSpecifiers = TEXT("public");

			if (bIsOverrideFunction == true)
			{
				FunctionPolymorphism = TEXT("new");
			}
			else if (SuperClass != nullptr)
			{
				if (SuperClass->FindFunctionByName(*FunctionName))
				{
					FunctionPolymorphism = TEXT("override");
				}

				static TSet<FString> DefaultImplementations =
				{
					TEXT("GetClass"),
					TEXT("GetName"),
					TEXT("GetWorld"),
					TEXT("ToString"),
					TEXT("IsValid"),
					TEXT("GetType")
				};

				if (DefaultImplementations.Contains(FunctionName))
				{
					FunctionPolymorphism = TEXT("new");
				}
			}
		}

		auto bIsStatic = Function->HasAnyFunctionFlags(FUNC_Static);

		if (bIsStatic == true)
		{
			FunctionStatic = TEXT("static");

			FunctionPolymorphism = TEXT("");
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

		FString FunctionComment;

		if (FUnrealCSharpFunctionLibrary::IsGenerateFunctionComment())
		{
			auto Comment = Function->GetMetaData(TEXT("Comment"));

			if (!Comment.IsEmpty())
			{
				FunctionComment = FDoxygenConverter(TEXT("\t\t"))(Comment);
			}
		}

		FString FunctionDeclarationBody;

		TArray<int32> FunctionOutParamIndexMapping;

		FunctionOutParamIndexMapping.AddDefaulted(FunctionParams.Num());

		auto bGeneratorFunctionDefaultParam = false;

		for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
		{
			if (FunctionParams[Index]->HasAnyPropertyFlags(CPF_OutParm) && !FunctionParams[Index]->HasAnyPropertyFlags(
				CPF_ConstParm))
			{
				if (FUnrealCSharpFunctionLibrary::IsNativeFunction(InClass, Function->GetFName()) ||
					FunctionParams[Index]->HasAnyPropertyFlags(CPF_ReferenceParm))
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

			if (bGeneratorFunctionDefaultParam == false)
			{
				bGeneratorFunctionDefaultParam = HasFunctionDefaultParam(Function, FunctionParams[Index]);
			}
		}

		if (bGeneratorFunctionDefaultParam)
		{
			bGeneratorFunctionDefaultParam = GeneratorFunctionDefaultParam(
				FunctionOutParamIndex, FunctionRefParamIndex);
		}

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
			                                           *FUnrealCSharpFunctionLibrary::Encode(FunctionParams[Index]),
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
		                                           *EncodeFunctionName,
		                                           *FunctionDeclarationBody
		);

		auto DummyFunctionName = FString::Printf(TEXT(
			"__%s"
		),
		                                         *EncodeFunctionName
		);

		if (bIsInterface == true)
		{
			InterfaceFunction += FString::Printf(TEXT(
				"\t\t%s;\n"
			),
			                                     *FunctionDeclaration);

			continue;
		}

		FString InBufferBody;

		auto bHasInBuffer = false;

		if (!FunctionParams.IsEmpty())
		{
			auto BufferSize = 0;

			for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
			{
				if (FunctionOutParamIndex.Contains(Index) == false)
				{
					InBufferBody += FString::Printf(TEXT(
						"\t\t\t\t*(%s*)(%s%s) = %s;\n\n"
					),
					                                *FGeneratorCore::GetBufferCast(FunctionParams[Index]),
					                                IN_BUFFER_TEXT,
					                                BufferSize == 0
						                                ? TEXT("")
						                                : *FString::Printf(TEXT(
							                                " + %d"),
						                                                   BufferSize),
					                                *FGeneratorCore::GetParamName(FunctionParams[Index])
					);

					BufferSize += FGeneratorCore::GetBufferSize(FunctionParams[Index]);
				}
			}

			InBufferBody = FString::Printf(TEXT(
				"\t\t\t\tvar %s = stackalloc byte[%d];\n\n"
				"%s"
			),
			                               IN_BUFFER_TEXT,
			                               BufferSize,
			                               *InBufferBody
			);

			bHasInBuffer = BufferSize != 0;
		}

		FString OutBufferBody;

		auto bHasOutBuffer = false;

		if (!FunctionOutParamIndex.IsEmpty() || !FunctionRefParamIndex.IsEmpty())
		{
			auto BufferSize = 0;

			for (auto Index = 0; Index < FunctionOutParamIndex.Num(); ++Index)
			{
				BufferSize += FGeneratorCore::GetBufferSize(FunctionParams[FunctionOutParamIndex[Index]]);
			}

			for (auto Index = 0; Index < FunctionRefParamIndex.Num(); ++Index)
			{
				BufferSize += FGeneratorCore::GetBufferSize(FunctionParams[FunctionRefParamIndex[Index]]);
			}

			OutBufferBody = FString::Printf(TEXT(
				"\t\t\t\tvar %s = stackalloc byte[%d];\n\n"
			),
			                                OUT_BUFFER_TEXT,
			                                BufferSize
			);

			bHasOutBuffer = BufferSize != 0;
		}

		FString ReturnBufferBody;

		auto bHasReturnBuffer = false;

		if (FunctionReturnParam != nullptr)
		{
			bHasReturnBuffer = true;

			ReturnBufferBody = FString::Printf(TEXT(
				"\t\t\t\tvar %s = stackalloc byte[%d];\n\n"
			),
			                                   RETURN_BUFFER_TEXT,
			                                   FGeneratorCore::GetBufferSize(FunctionReturnParam)
			);
		}

		auto FunctionCallBody = FString::Printf(TEXT(
			"FFunctionImplementation.FFunction_%sCall%dImplementation(%s, %s%s%s%s);\n"
		),
		                                        *FGeneratorCore::GetFunctionPrefix(FunctionReturnParam),
		                                        FGeneratorCore::GetFunctionIndex(FunctionReturnParam != nullptr,
			                                        FunctionParams.Num() - FunctionOutParamIndex.Num() != 0,
			                                        !FunctionRefParamIndex.IsEmpty() || !FunctionOutParamIndex.
			                                        IsEmpty(),
			                                        Function->HasAnyFunctionFlags(FUNC_Native),
			                                        Function->HasAnyFunctionFlags(FUNC_Net)),
		                                        bIsStatic == true
			                                        ? *FString::Printf(
				                                        TEXT("StaticClass().%s"),
				                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE)
			                                        : *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                        *DummyFunctionName,
		                                        bHasInBuffer
			                                        ? *FString::Printf(TEXT(
				                                        ", %s"
			                                        ),
			                                                           IN_BUFFER_TEXT)
			                                        : TEXT(""),
		                                        bHasOutBuffer
			                                        ? *FString::Printf(TEXT(
				                                        ", %s"
			                                        ),
			                                                           OUT_BUFFER_TEXT)
			                                        : TEXT(""),
		                                        bHasReturnBuffer
			                                        ? *FString::Printf(TEXT(
				                                        ", %s"
			                                        ),
			                                                           RETURN_BUFFER_TEXT)
			                                        : TEXT("")
		);

		FString FunctionReturnParamBody;

		if (FunctionReturnParam != nullptr)
		{
			FunctionReturnParamBody = FString::Printf(TEXT(
				"return *(%s*)%s;"
			),
			                                          *FunctionReturnType,
			                                          RETURN_BUFFER_TEXT
			);
		}

		FString FunctionDefaultParamBody;

		if (bGeneratorFunctionDefaultParam)
		{
			for (auto Index = 0; Index < FunctionParams.Num(); ++Index)
			{
				FunctionDefaultParamBody += GeneratorFunctionDefaultParam(Function, FunctionParams[Index]);
			}
		}

		FString FunctionOutParamBody;

		if (bHasOutBuffer)
		{
			auto FunctionOutBufferIndex = TArrayBuilder<int32>().Append(FunctionOutParamIndex).Append(
				FunctionRefParamIndex).Build();

			FunctionOutBufferIndex.Sort();

			auto BufferSize = 0;

			for (auto Index = 0; Index < FunctionOutBufferIndex.Num(); ++Index)
			{
				FunctionOutParamBody += FString::Printf(TEXT(
					"\n\t\t\t\t%s = *(%s*)(%s%s);\n"
				),
				                                        *FUnrealCSharpFunctionLibrary::Encode(
					                                        FunctionParams[FunctionOutBufferIndex[Index]]),
				                                        *FGeneratorCore::GetPropertyType(
					                                        FunctionParams[FunctionOutBufferIndex[Index]]),
				                                        OUT_BUFFER_TEXT,
				                                        BufferSize == 0
					                                        ? TEXT("")
					                                        : *FString::Printf(TEXT(
						                                        " + %d"),
					                                                           BufferSize)
				);

				BufferSize += FGeneratorCore::GetBufferSize(FunctionParams[FunctionOutBufferIndex[Index]]);
			}
		}

		auto FunctionImplementationBody = FString::Printf(TEXT(
			"%s"
			"%s"
			"%s"
			"%s"
			"\t\t\t\t%s"
			"%s"
			"%s"
			"%s"
		),
		                                                  *FunctionDefaultParamBody,
		                                                  *InBufferBody,
		                                                  *OutBufferBody,
		                                                  *ReturnBufferBody,
		                                                  *FunctionCallBody,
		                                                  *FunctionOutParamBody,
		                                                  !FunctionReturnParamBody.IsEmpty()
			                                                  ? TEXT("\n")
			                                                  : TEXT(""),
		                                                  FunctionReturnParamBody.IsEmpty()
			                                                  ? TEXT("")
			                                                  : *FString::Printf(TEXT(
				                                                  "\t\t\t\t%s\n"
			                                                  ),
				                                                  *FunctionReturnParamBody));

		FunctionContent += FString::Printf(TEXT(
			"%s"
			"\t\t%s\n"
			"\t\t{\n"
			"\t\t\tunsafe\n"
			"\t\t\t{\n"
			"%s"
			"\t\t\t}\n"
			"\t\t}\n"
		),
		                                   *FunctionComment,
		                                   *FunctionDeclaration,
		                                   *FunctionImplementationBody
		);

		if (bIsInterface == false)
		{
			FunctionNameContent += FString::Printf(TEXT(
				"%s\t\tprivate static uint %s = 0;\n"
			),
			                                       FunctionNameSet.IsEmpty() ? TEXT("") : TEXT("\n"),
			                                       *DummyFunctionName
			);
		}

		FunctionNameSet.Add(FunctionName);
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
		"\tpublic partial class %s%s%s\n"
		"\t{\n"
		"%s"
		"%s"
		"%s"
		"%s"
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
	                               *ClassContent,
	                               *SuperClassContent,
	                               *InterfaceContent,
	                               *PropertyContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *FunctionContent,
	                               bHasProperty == true ? TEXT("\n") : TEXT(""),
	                               *PropertyNameContent,
	                               bIsInterface == false && bHasFunction == true ? TEXT("\n") : TEXT(""),
	                               *FunctionNameContent,
	                               bIsInterface == true ? TEXT("\n") : TEXT(""),
	                               *IInterfaceContent
	);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FGeneratorCore::GetFileName(InClass), Content);
}

bool FClassGenerator::GeneratorFunctionDefaultParam(const TArray<int32>& InFunctionOutParamIndex,
                                                    const TArray<int32>& InFunctionRefParamIndex)
{
	return InFunctionOutParamIndex.Num() == 0 && InFunctionRefParamIndex.Num() == 0 ||
	(InFunctionOutParamIndex.Num() >= InFunctionRefParamIndex.Num()
		 ? InFunctionOutParamIndex[InFunctionOutParamIndex.Num() - 1] == InFunctionOutParamIndex.Num() - 1
		 : InFunctionRefParamIndex[InFunctionRefParamIndex.Num() - 1] == InFunctionRefParamIndex.Num() - 1);
}

bool FClassGenerator::HasFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	if (InFunction == nullptr || InProperty == nullptr)
	{
		return false;
	}

	if (!InFunction->HasAnyFunctionFlags(FUNC_BlueprintCallable))
	{
		return false;
	}

	if (Cast<UBlueprintGeneratedClass>(InFunction->GetOuter()))
	{
		return HasBlueprintFunctionDefaultParam(InFunction, InProperty);
	}

	return HasCppFunctionDefaultParam(InFunction, InProperty);
}

bool FClassGenerator::HasCppFunctionDefaultParam(const UFunction* InFunction, const FProperty* InProperty)
{
	const auto Key = FString::Printf(TEXT("CPP_Default_%s"), *InProperty->GetName());

	return InFunction->HasMetaData(*Key);
}

bool FClassGenerator::HasBlueprintFunctionDefaultParam(const UFunction* InFunction, const FProperty* InProperty)
{
	if (InProperty->HasAnyPropertyFlags(CPF_OutParm) && !InProperty->HasAnyPropertyFlags(CPF_ConstParm))
	{
		return false;
	}

	const auto Key = InProperty->GetName();

	return InFunction->HasMetaData(*Key);
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
			const auto EnumName = ByteProperty->Enum->GetName();

			if (MetaData.StartsWith("Type::"))
			{
				return FString::Printf(TEXT(" = %s.%s"), *EnumName,
				                       *MetaData.Right(MetaData.Len() - 6));
			}
			else
			{
				static auto CollisionChannel = FString(TEXT("ECollisionChannel"));

				if (EnumName == CollisionChannel)
				{
					return FString::Printf(TEXT(" = %s.%s"), *EnumName,
					                       *UCollisionProfile::Get()->ReturnChannelNameFromContainerIndex(
						                       ByteProperty->Enum->GetIndexByName(*MetaData)).ToString());
				}
				else
				{
					return FString::Printf(TEXT(" = %s.%s"), *EnumName, *MetaData);
				}
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
				*FUnrealCSharpFunctionLibrary::Encode(MetaData.IsEmpty()
														  ? *UserDefinedEnum->
														  GetDisplayNameTextByIndex(
															  ENUM_DEFAULT_MAX_INDEX).ToString()
														  : *UserDefinedEnum->
														  GetDisplayNameTextByIndex(
															  UserDefinedEnum->
															  GetIndexByNameString(MetaData)).
														  ToString(), false));
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

	if (CastField<FDelegateProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = null"));
	}

	if (CastField<FInterfaceProperty>(InProperty))
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

	if (const auto EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		return FString::Printf(TEXT(" = %s.%s"), *EnumProperty->GetEnum()->GetName(),
		                       MetaData.IsEmpty()
			                       ? *EnumProperty->GetEnum()->GetDisplayNameTextByIndex(ENUM_DEFAULT_MAX_INDEX).
			                                        ToString()
			                       : *MetaData);
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

FString FClassGenerator::GeneratorFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	if (InFunction == nullptr || InProperty == nullptr)
	{
		return TEXT("");
	}

	if (FGeneratorCore::IsPrimitiveProperty(InProperty))
	{
		return TEXT("");
	}

	if (Cast<UBlueprintGeneratedClass>(InFunction->GetOuter()))
	{
		return GeneratorBlueprintFunctionDefaultParam(InFunction, InProperty);
	}

	return GeneratorCppFunctionDefaultParam(InFunction, InProperty);
}

FString FClassGenerator::GeneratorCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	const auto Key = FString::Printf(TEXT("CPP_Default_%s"), *InProperty->GetName());

	if (!InFunction->HasMetaData(*Key))
	{
		return TEXT("");
	}

	const auto MetaData = InFunction->GetMetaData(*Key);

	return GeneratorFunctionDefaultParam(InProperty, MetaData);
}

FString FClassGenerator::GeneratorBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty)
{
	if (InProperty->HasAnyPropertyFlags(CPF_OutParm) && !InProperty->HasAnyPropertyFlags(CPF_ConstParm))
	{
		return TEXT("");
	}

	const auto Key = InProperty->GetName();

	if (!InFunction->HasMetaData(*Key))
	{
		return TEXT("");
	}

	const auto MetaData = InFunction->GetMetaData(*Key);

	return GeneratorFunctionDefaultParam(InProperty, MetaData);
}

FString FClassGenerator::GeneratorFunctionDefaultParam(FProperty* InProperty, const FString& InMetaData)
{
	if (CastField<FNameProperty>(InProperty))
	{
		return FString::Printf(TEXT(
			"\t\t\t\t%s \?\?= new FName(\"%s\");\n\n"
		),
		                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
		                       *InMetaData
		);
	}

	if (const auto StructProperty = CastField<FStructProperty>(InProperty))
	{
		if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
		{
			TArray<FString> Value;

			InMetaData.ParseIntoArray(Value, TEXT(","));

			if (Value.Num() == 3)
			{
				return FString::Printf(TEXT(
					"\t\t\t\t%s \?\?= new FRotator(%lf, %lf, %lf);\n\n"
				),
				                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
				                       TCString<TCHAR>::Atod(*Value[0]),
				                       TCString<TCHAR>::Atod(*Value[1]),
				                       TCString<TCHAR>::Atod(*Value[2])
				);
			}
		}

		if (StructProperty->Struct == TBaseStructure<FLinearColor>::Get())
		{
			FLinearColor Value;

			if (Value.InitFromString(InMetaData))
			{
				return FString::Printf(TEXT(
					"\t\t\t\t%s \?\?= new FLinearColor(%ff, %ff, %ff, %ff);\n\n"
				),
				                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
				                       Value.R,
				                       Value.G,
				                       Value.B,
				                       Value.A
				);
			}
		}

		if (StructProperty->Struct == TBaseStructure<FVector>::Get())
		{
			TArray<FString> Value;

			InMetaData.ParseIntoArray(Value, TEXT(","));

			if (Value.Num() == 3)
			{
				return FString::Printf(TEXT(
					"\t\t\t\t%s \?\?= new FVector(%lf, %lf, %lf);\n\n"
				),
				                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
				                       TCString<TCHAR>::Atod(*Value[0]),
				                       TCString<TCHAR>::Atod(*Value[1]),
				                       TCString<TCHAR>::Atod(*Value[2])
				);
			}
		}

		if (StructProperty->Struct == TBaseStructure<FVector2D>::Get())
		{
			FVector2D Value;

			if (Value.InitFromString(InMetaData))
			{
				return FString::Printf(TEXT(
					"\t\t\t\t%s \?\?= new FVector2D(%lf, %lf);\n\n"
				),
				                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
				                       Value.X,
				                       Value.Y
				);
			}
		}

		return FString::Printf(TEXT(
			"\t\t\t\t%s \?\?= new %s%s();\n\n"
		),
		                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
		                       StructProperty->Struct->IsNative() ? TEXT("F") : TEXT(""),
		                       *StructProperty->Struct->GetName()
		);
	}

	if (CastField<FStrProperty>(InProperty))
	{
		return FString::Printf(TEXT(
			"\t\t\t\t%s \?\?= new FString(\"%s\");\n\n"
		),
		                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
		                       *InMetaData
		);
	}

	if (CastField<FTextProperty>(InProperty))
	{
		return FString::Printf(TEXT(
			"\t\t\t\t%s \?\?= new FText(\"%s\");\n\n"
		),
		                       *FUnrealCSharpFunctionLibrary::Encode(InProperty),
		                       *InMetaData.Replace(TEXT("\""), TEXT("\\\""))
		);
	}

	return TEXT("");
}
