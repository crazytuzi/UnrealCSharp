#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

void FDelegateGenerator::Generator(FProperty* InProperty)
{
	if (InProperty == nullptr)
	{
		return;
	}

	if (const auto DelegateProperty = CastField<FDelegateProperty>(InProperty))
	{
		Generator(DelegateProperty);
	}
	else if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(InProperty))
	{
		Generator(MulticastDelegateProperty);
	}
}

void FDelegateGenerator::Generator(FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return;
	}

	auto SignatureFunction = InDelegateProperty->SignatureFunction;

	FString UsingNameSpaceContent;

	auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InDelegateProperty);

	FString FullClassContent;

	FString SuperClassContent;

	FString BindFunctionContent;

	FString ExecuteFunctionContent;

	FString DelegateDeclarationContent;

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common"), TEXT("Script.Library")};

	FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InDelegateProperty);

	auto DelegateFullName = FullClassContent;

	auto DelegateName = DelegateFullName.RightChop(1);

	TArray<FProperty*> DelegateParams;

	TArray<int32> DelegateRefParamIndex;

	FProperty* DelegateReturnParam = nullptr;

	const auto ConstructorContent = FString::Printf(TEXT(
		"\t\tpublic %s() => DelegateImplementation.Delegate_RegisterImplementation(this);\n"
	),
	                                                *FullClassContent
	);

	const auto DestructorContent = FString::Printf(TEXT(
		"\n\t\t~%s() => DelegateImplementation.Delegate_UnRegisterImplementation(GetHandle());\n"
	),
	                                               *FullClassContent
	);

	for (TFieldIterator<FProperty> ParamIterator(SignatureFunction); ParamIterator && (ParamIterator->PropertyFlags &
		     CPF_Parm); ++ParamIterator)
	{
		if (ParamIterator->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			DelegateReturnParam = *ParamIterator;
		}
		else
		{
			DelegateParams.Emplace(*ParamIterator);
		}

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*ParamIterator));
	}

	FString DelegateReturnType = TEXT("void");

	if (DelegateReturnParam != nullptr)
	{
		DelegateReturnType = FGeneratorCore::GetPropertyType(DelegateReturnParam);
	}

	FString DelegateDeclarationBody;

	for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
	{
		if (DelegateParams[Index]->HasAnyPropertyFlags(CPF_OutParm) && !DelegateParams[Index]->HasAnyPropertyFlags(
			CPF_ConstParm))
		{
			DelegateRefParamIndex.Emplace(Index);

			DelegateDeclarationBody += TEXT("ref ");
		}

		DelegateDeclarationBody += FString::Printf(TEXT(
			"%s %s%s"
		),
		                                           *FGeneratorCore::GetPropertyType(DelegateParams[Index]),
		                                           *FUnrealCSharpFunctionLibrary::Encode(
			                                           DelegateParams[Index]->GetName()),
		                                           Index == DelegateParams.Num() - 1 ? TEXT("") : TEXT(", ")
		);
	}

	auto ExecuteFunctionDeclaration = FString::Printf(TEXT(
		"public %s Execute(%s)\n"
	),
	                                                  *DelegateReturnType,
	                                                  *DelegateDeclarationBody
	);

	auto ExecuteFunctionCallBody = FString::Printf(TEXT(
		"DelegateImplementation.Delegate_Execute%dImplementation(GetHandle()%s"
	),
	                                               FGeneratorCore::GetFunctionIndex(DelegateReturnParam != nullptr,
		                                               !DelegateParams.IsEmpty(),
		                                               !DelegateRefParamIndex.IsEmpty()),
	                                               DelegateRefParamIndex.IsEmpty()
		                                               ? TEXT("")
		                                               : TEXT(", out var __OutValue")
	);

	for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
	{
		if (DelegateRefParamIndex.Contains(Index) == false)
		{
			ExecuteFunctionCallBody += ", " + FGeneratorCore::GetParamName(DelegateParams[Index]);
		}
	}

	ExecuteFunctionCallBody += TEXT(")");

	TArray<FString> ExecuteFunctionOutParams;

	for (auto Index = 0; Index < DelegateRefParamIndex.Num(); ++Index)
	{
		ExecuteFunctionOutParams.Emplace(FString::Printf(TEXT(
			"%s = %s;"
		),
		                                                 *FUnrealCSharpFunctionLibrary::Encode(
			                                                 DelegateParams[DelegateRefParamIndex[Index]]->GetName()),
		                                                 *FGeneratorCore::GetOutParamString(
			                                                 DelegateParams[DelegateRefParamIndex[Index]], Index)));
	}

	FString ExecuteFunctionReturnParamBody;

	if (DelegateReturnParam != nullptr)
	{
		ExecuteFunctionReturnParamBody = FString::Printf(TEXT(
			"return %s;"
		),
		                                                 DelegateRefParamIndex.IsEmpty()
			                                                 ? FGeneratorCore::IsPrimitiveProperty(DelegateReturnParam)
				                                                   ? *FString::Printf(TEXT(
					                                                   "(%s)%s"
				                                                   ),
					                                                   *FGeneratorCore::GetPropertyType(
						                                                   DelegateReturnParam),
					                                                   *ExecuteFunctionCallBody)
				                                                   : *FString::Printf(TEXT(
					                                                   "%s as %s"
				                                                   ),
					                                                   *ExecuteFunctionCallBody,
					                                                   *FGeneratorCore::GetPropertyType(
						                                                   DelegateReturnParam))
			                                                 : FGeneratorCore::IsPrimitiveProperty(DelegateReturnParam)
			                                                 ? *FString::Printf(TEXT(
				                                                 "(%s)__ReturnValue"
			                                                 ),
				                                                 *FGeneratorCore::GetPropertyType(DelegateReturnParam))
			                                                 : *FString::Printf(TEXT(
				                                                 "__ReturnValue as %s"),
				                                                 *FGeneratorCore::GetPropertyType(DelegateReturnParam))
		);
	}

	FString ExecuteFunctionOutParamBody;

	for (auto ExecuteFunctionOutParam : ExecuteFunctionOutParams)
	{
		ExecuteFunctionOutParamBody += FString::Printf(TEXT(
			"\n\t\t\t%s\n"
		),
		                                               *ExecuteFunctionOutParam);
	}

	auto ExecuteFunctionImplementationBody = FString::Printf(TEXT(
		"\t\t\t%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
	),
	                                                         DelegateReturnParam != nullptr && !DelegateRefParamIndex.
	                                                         IsEmpty()
		                                                         ? TEXT("var __ReturnValue = ")
		                                                         : TEXT(""),
	                                                         DelegateReturnParam == nullptr || !DelegateRefParamIndex.
	                                                         IsEmpty()
		                                                         ? *ExecuteFunctionCallBody
		                                                         : TEXT(""),
	                                                         DelegateReturnParam == nullptr || !DelegateRefParamIndex.
	                                                         IsEmpty()
		                                                         ? TEXT(";\n")
		                                                         : TEXT(""),
	                                                         *ExecuteFunctionOutParamBody,
	                                                         !ExecuteFunctionOutParamBody.IsEmpty()
		                                                         ? TEXT("\n")
		                                                         : TEXT(""),
	                                                         ExecuteFunctionReturnParamBody.IsEmpty()
		                                                         ? TEXT("")
		                                                         : *FString::Printf(TEXT(
			                                                         "%s%s\n"
		                                                         ),
			                                                         !DelegateRefParamIndex.IsEmpty()
				                                                         ? TEXT("\t\t\t")
				                                                         : TEXT(""),
			                                                         *ExecuteFunctionReturnParamBody));

	ExecuteFunctionContent = FString::Printf(TEXT(
		"\t\t%s"
		"\t\t{\n"
		"%s"
		"\t\t}\n"
	),
	                                         *ExecuteFunctionDeclaration,
	                                         *ExecuteFunctionImplementationBody
	);

	if (!DelegateRefParamIndex.IsEmpty())
	{
		SuperClassContent = TEXT("FRefDelegate");

		BindFunctionContent = TEXT(
			"\t\tpublic void Bind(UObject InObject, Delegate InDelegate) => DelegateImplementation.Delegate_BindImplementation(GetHandle(), InDelegate);\n"
			"\n"
			"\t\tpublic void Bind(Delegate InDelegate) => DelegateImplementation.Delegate_BindImplementation(GetHandle(), InDelegate);\n"
		);

		DelegateDeclarationContent = FString::Printf(TEXT(
			"\t\tpublic delegate %s Delegate(%s);\n"
		),
		                                             *DelegateReturnType,
		                                             *DelegateDeclarationBody);

		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));
	}
	else
	{
		if (DelegateReturnParam != nullptr)
		{
			SuperClassContent = TEXT("FDelegate<Func<");
		}
		else
		{
			if (!DelegateParams.IsEmpty())
			{
				SuperClassContent = TEXT("FDelegate<Action<");
			}
			else
			{
				SuperClassContent = TEXT("FDelegate<Action");
			}
		}

		for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
		{
			SuperClassContent += FString::Printf(TEXT(
				"%s%s"
			),
			                                     Index != 0 ? TEXT(", ") : TEXT(""),
			                                     *FGeneratorCore::GetPropertyType(DelegateParams[Index]));
		}

		if (DelegateReturnParam != nullptr)
		{
			SuperClassContent += !DelegateParams.IsEmpty()
				                     ? FString::Printf(TEXT(
					                     ", %s"
				                     ),
				                                       *DelegateReturnType)
				                     : FString::Printf(TEXT(
					                     "%s"
				                     ),
				                                       *DelegateReturnType);
		}

		if (DelegateReturnParam != nullptr)
		{
			SuperClassContent += TEXT(">>");
		}
		else
		{
			if (!DelegateParams.IsEmpty())
			{
				SuperClassContent += TEXT(">>");
			}
			else
			{
				SuperClassContent += TEXT(">");
			}
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
		"\tpublic class %s : %s\n"
		"\t{\n"
		"%s"
		"%s"
		"\n"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"\t}\n"
		"}\n"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *FullClassContent,
	                               *SuperClassContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               *BindFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *ExecuteFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *DelegateDeclarationContent
	);

	auto ModuleName = NameSpaceContent.Replace(*SCRIPT, TEXT("")).Replace(TEXT("."), TEXT("/"));

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(InDelegateProperty->SignatureFunction), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, DelegateName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

void FDelegateGenerator::Generator(FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return;
	}

	auto SignatureFunction = InMulticastDelegateProperty->SignatureFunction;

	FString UsingNameSpaceContent;

	auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InMulticastDelegateProperty);

	FString FullClassContent;

	FString SuperClassContent;

	FString ContainsFunctionContent;

	FString AddFunctionContent;

	FString AddUniqueFunctionContent;

	FString RemoveFunctionContent;

	FString BroadcastFunctionContent;

	FString DelegateDeclarationContent;

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common"), TEXT("Script.Library")};

	FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InMulticastDelegateProperty);

	auto DelegateFullName = FullClassContent;

	auto DelegateName = DelegateFullName.RightChop(1);

	TArray<FProperty*> DelegateParams;

	TArray<int32> DelegateRefParamIndex;

	FProperty* DelegateReturnParam = nullptr;

	const auto ConstructorContent = FString::Printf(TEXT(
		"\t\tpublic %s() => MulticastDelegateImplementation.MulticastDelegate_RegisterImplementation(this);\n"
	),
	                                                *FullClassContent
	);

	const auto DestructorContent = FString::Printf(TEXT(
		"\n\t\t~%s() => MulticastDelegateImplementation.MulticastDelegate_UnRegisterImplementation(GetHandle());\n"
	),
	                                               *FullClassContent
	);

	for (TFieldIterator<FProperty> ParamIterator(SignatureFunction); ParamIterator && (ParamIterator->PropertyFlags &
		     CPF_Parm); ++ParamIterator)
	{
		if (ParamIterator->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			DelegateReturnParam = *ParamIterator;
		}
		else
		{
			DelegateParams.Emplace(*ParamIterator);
		}

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*ParamIterator));
	}

	FString DelegateReturnType = TEXT("void");

	if (DelegateReturnParam != nullptr)
	{
		DelegateReturnType = FGeneratorCore::GetPropertyType(DelegateReturnParam);
	}

	FString DelegateDeclarationBody;

	for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
	{
		if (DelegateParams[Index]->HasAnyPropertyFlags(CPF_OutParm) && !DelegateParams[Index]->HasAnyPropertyFlags(
			CPF_ConstParm))
		{
			DelegateRefParamIndex.Emplace(Index);

			DelegateDeclarationBody += TEXT("ref ");
		}

		DelegateDeclarationBody += FString::Printf(TEXT(
			"%s %s%s"
		),
		                                           *FGeneratorCore::GetPropertyType(DelegateParams[Index]),
		                                           *FUnrealCSharpFunctionLibrary::Encode(
			                                           DelegateParams[Index]->GetName()),
		                                           Index == DelegateParams.Num() - 1 ? TEXT("") : TEXT(", ")
		);
	}

	auto BroadcastFunctionDeclaration = FString::Printf(TEXT(
		"public %s Broadcast(%s)\n"
	),
	                                                    *DelegateReturnType,
	                                                    *DelegateDeclarationBody
	);

	auto BroadcastFunctionCallBody = FString::Printf(TEXT(
		"MulticastDelegateImplementation.MulticastDelegate_Broadcast%dImplementation(GetHandle()%s"
	),
	                                                 FGeneratorCore::GetFunctionIndex(DelegateReturnParam != nullptr,
		                                                 !DelegateParams.IsEmpty(),
		                                                 !DelegateRefParamIndex.IsEmpty()),
	                                                 DelegateRefParamIndex.IsEmpty()
		                                                 ? TEXT("")
		                                                 : TEXT(", out var __OutValue")
	);

	for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
	{
		if (DelegateRefParamIndex.Contains(Index) == false)
		{
			BroadcastFunctionCallBody += ", " + FGeneratorCore::GetParamName(DelegateParams[Index]);
		}
	}

	BroadcastFunctionCallBody += TEXT(")");

	TArray<FString> BroadcastFunctionOutParams;

	for (auto Index = 0; Index < DelegateRefParamIndex.Num(); ++Index)
	{
		BroadcastFunctionOutParams.Emplace(FString::Printf(TEXT(
			"%s = %s;"
		),
		                                                   *FUnrealCSharpFunctionLibrary::Encode(
			                                                   DelegateParams[DelegateRefParamIndex[Index]]->GetName()),
		                                                   *FGeneratorCore::GetOutParamString(
			                                                   DelegateParams[DelegateRefParamIndex[Index]], Index)));
	}

	FString BroadcastFunctionReturnParamBody;

	if (DelegateReturnParam != nullptr)
	{
		BroadcastFunctionReturnParamBody = FString::Printf(TEXT(
			"return %s;"
		),
		                                                   DelegateRefParamIndex.IsEmpty()
			                                                   ? FGeneratorCore::IsPrimitiveProperty(
				                                                     DelegateReturnParam)
				                                                     ? *FString::Printf(TEXT(
					                                                     "(%s)%s"
				                                                     ),
					                                                     *FGeneratorCore::GetPropertyType(
						                                                     DelegateReturnParam),
					                                                     *BroadcastFunctionCallBody)
				                                                     : *FString::Printf(TEXT(
					                                                     "%s as %s"
				                                                     ),
					                                                     *BroadcastFunctionCallBody,
					                                                     *FGeneratorCore::GetPropertyType(
						                                                     DelegateReturnParam))
			                                                   : FGeneratorCore::IsPrimitiveProperty(
				                                                   DelegateReturnParam)
			                                                   ? *FString::Printf(TEXT(
				                                                   "(%s)__ReturnValue"
			                                                   ),
				                                                   *FGeneratorCore::GetPropertyType(
					                                                   DelegateReturnParam))
			                                                   : *FString::Printf(TEXT(
				                                                   "__ReturnValue as %s"),
				                                                   *FGeneratorCore::GetPropertyType(
					                                                   DelegateReturnParam))
		);
	}

	FString BroadcastFunctionOutParamBody;

	for (auto BroadcastFunctionOutParam : BroadcastFunctionOutParams)
	{
		BroadcastFunctionOutParamBody += FString::Printf(TEXT(
			"\n\t\t\t%s\n"),
		                                                 *BroadcastFunctionOutParam);
	}

	auto BroadcastFunctionImplementationBody = FString::Printf(TEXT(
		"\t\t\t%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
	),
	                                                           DelegateReturnParam != nullptr && !DelegateRefParamIndex.
	                                                           IsEmpty()
		                                                           ? TEXT("var __ReturnValue = ")
		                                                           : TEXT(""),
	                                                           DelegateReturnParam == nullptr || !DelegateRefParamIndex.
	                                                           IsEmpty()
		                                                           ? *BroadcastFunctionCallBody
		                                                           : TEXT(""),
	                                                           DelegateReturnParam == nullptr || !DelegateRefParamIndex.
	                                                           IsEmpty()
		                                                           ? TEXT(";\n")
		                                                           : TEXT(""),
	                                                           *BroadcastFunctionOutParamBody,
	                                                           !BroadcastFunctionOutParamBody.IsEmpty()
		                                                           ? TEXT("\n")
		                                                           : TEXT(""),
	                                                           BroadcastFunctionReturnParamBody.IsEmpty()
		                                                           ? TEXT("")
		                                                           : *FString::Printf(TEXT(
			                                                           "%s%s\n"
		                                                           ),
			                                                           !DelegateRefParamIndex.IsEmpty()
				                                                           ? TEXT("\t\t\t")
				                                                           : TEXT(""),
			                                                           *BroadcastFunctionReturnParamBody));

	BroadcastFunctionContent = FString::Printf(TEXT(
		"\t\t%s"
		"\t\t{\n"
		"%s"
		"\t\t}\n"
	),
	                                           *BroadcastFunctionDeclaration,
	                                           *BroadcastFunctionImplementationBody
	);

	if (!DelegateRefParamIndex.IsEmpty())
	{
		SuperClassContent = TEXT("FRefMulticastDelegate");

		ContainsFunctionContent = TEXT(
			"\t\tpublic Boolean Contains(UObject _, Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(GetHandle(), InDelegate);\n"
			"\n"
			"\t\tpublic Boolean Contains(Delegate InDelegate)=> MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(GetHandle(), InDelegate);\n"
		);

		AddFunctionContent = TEXT(
			"\t\tpublic void Add(UObject _, Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_AddImplementation(GetHandle(), InDelegate);\n"
			"\n"
			"\t\tpublic void Add(Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_AddImplementation(GetHandle(), InDelegate);\n"
		);

		AddUniqueFunctionContent = TEXT(
			"\t\tpublic void AddUnique(UObject _, Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(GetHandle(), InDelegate);\n"
			"\n"
			"\t\tpublic void AddUnique(Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(GetHandle(), InDelegate);\n"
		);

		RemoveFunctionContent = TEXT(
			"\t\tpublic void Remove(UObject _, Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(GetHandle(), InDelegate);\n"
			"\n"
			"\t\tpublic void Remove(Delegate InDelegate) => MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(GetHandle(), InDelegate);\n"
		);

		DelegateDeclarationContent = FString::Printf(TEXT(
			"\t\tpublic delegate %s Delegate(%s);\n"
		),
		                                             *DelegateReturnType,
		                                             *DelegateDeclarationBody);

		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));
	}
	else
	{
		if (DelegateReturnParam != nullptr)
		{
			SuperClassContent = TEXT("FMulticastDelegate<Func<");
		}
		else
		{
			if (!DelegateParams.IsEmpty())
			{
				SuperClassContent = TEXT("FMulticastDelegate<Action<");
			}
			else
			{
				SuperClassContent = TEXT("FMulticastDelegate<Action");
			}
		}

		for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
		{
			SuperClassContent += FString::Printf(TEXT(
				"%s%s"
			),
			                                     Index != 0 ? TEXT(", ") : TEXT(""),
			                                     *FGeneratorCore::GetPropertyType(DelegateParams[Index]));
		}

		if (DelegateReturnParam != nullptr)
		{
			SuperClassContent += !DelegateParams.IsEmpty()
				                     ? FString::Printf(TEXT(
					                     ", %s"
				                     ),
				                                       *DelegateReturnType)
				                     : FString::Printf(TEXT(
					                     "%s"
				                     ),
				                                       *DelegateReturnType);
		}

		if (DelegateReturnParam != nullptr)
		{
			SuperClassContent += TEXT(">>");
		}
		else
		{
			if (!DelegateParams.IsEmpty())
			{
				SuperClassContent += TEXT(">>");
			}
			else
			{
				SuperClassContent += TEXT(">");
			}
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
		"\tpublic class %s : %s\n"
		"\t{\n"
		"%s"
		"%s"
		"\n"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"\t}\n"
		"}\n"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *FullClassContent,
	                               *SuperClassContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               *ContainsFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *AddFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *AddUniqueFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *RemoveFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *BroadcastFunctionContent,
	                               !DelegateRefParamIndex.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *DelegateDeclarationContent
	);

	auto ModuleName = NameSpaceContent.Replace(*SCRIPT, TEXT("")).Replace(TEXT("."), TEXT("/"));

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(InMulticastDelegateProperty->SignatureFunction), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, DelegateName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
