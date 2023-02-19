#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "FUnrealCSharpFunctionLibrary.h"

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

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common"), TEXT("Script.Reflection.Delegate")};

	FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InDelegateProperty);

	auto DelegateFullName = FullClassContent;

	auto DelegateName = DelegateFullName.RightChop(1);

	TArray<FProperty*> DelegateParams;

	TArray<int32> DelegateOutParamIndex;

	FProperty* DelegateReturnParam = nullptr;

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
			DelegateOutParamIndex.Emplace(Index);

			DelegateDeclarationBody += TEXT("ref ");
		}

		DelegateDeclarationBody += FString::Printf(TEXT(
			"%s %s%s"
		),
		                                           *FGeneratorCore::GetPropertyType(DelegateParams[Index]),
		                                           *FGeneratorCore::GetName(DelegateParams[Index]->GetName()),
		                                           Index == DelegateParams.Num() - 1 ? TEXT("") : TEXT(", ")
		);
	}

	auto bIsSafeExecuteFunction = true;

	for (auto Index = 0; Index < DelegateOutParamIndex.Num(); ++Index)
	{
		if (!FGeneratorCore::IsSafeProperty(DelegateParams[DelegateOutParamIndex[Index]]))
		{
			bIsSafeExecuteFunction = false;

			break;
		}
	}

	auto ExecuteFunctionDeclaration = FString::Printf(TEXT(
		"public %s%s Execute(%s)\n"
	),
	                                                  bIsSafeExecuteFunction == true ? TEXT("") : TEXT("unsafe "),
	                                                  *DelegateReturnType,
	                                                  *DelegateDeclarationBody
	);

	auto ExecuteFunctionCallBody = FString::Printf(TEXT(
		"DelegateUtils.Delegate_Execute<%s>(this, out var __ReturnValue, out var __OutValue"
	),
	                                               DelegateReturnParam != nullptr
		                                               ? *FGeneratorCore::GetReturnParamType(DelegateReturnParam)
		                                               : TEXT("Object")
	);

	for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
	{
		if (DelegateOutParamIndex.Contains(Index) == false)
		{
			ExecuteFunctionCallBody += ", " + FGeneratorCore::GetParamName(DelegateParams[Index]);
		}
	}

	ExecuteFunctionCallBody += TEXT(");");

	TArray<FString> ExecuteFunctionOutParams;

	for (auto Index = 0; Index < DelegateOutParamIndex.Num(); ++Index)
	{
		ExecuteFunctionOutParams.Emplace(FString::Printf(TEXT(
			"%s = %s;"
		),
		                                                 *FGeneratorCore::GetName(
			                                                 DelegateParams[DelegateOutParamIndex[Index]]->GetName()),
		                                                 *FGeneratorCore::GetOutParamString(
			                                                 DelegateParams[DelegateOutParamIndex[Index]], Index)));
	}

	FString ExecuteFunctionReturnParamBody;

	if (DelegateReturnParam != nullptr)
	{
		ExecuteFunctionReturnParamBody = FString::Printf(TEXT(
			"return %s;"
		),
		                                                 *FGeneratorCore::GetReturnParamName(DelegateReturnParam));
	}

	if (bIsSafeExecuteFunction == false)
	{
		UsingNameSpaces.Add(TEXT("IntPtr = Script.Common.IntPtr"));
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
		"\t\t\t%s\n"
		"%s"
		"%s"
		"%s"
	),
	                                                         *ExecuteFunctionCallBody,
	                                                         *ExecuteFunctionOutParamBody,
	                                                         ExecuteFunctionReturnParamBody.IsEmpty()
		                                                         ? TEXT("")
		                                                         : TEXT("\n"),
	                                                         ExecuteFunctionReturnParamBody.IsEmpty()
		                                                         ? TEXT("")
		                                                         : *FString::Printf(TEXT(
			                                                         "\t\t\t%s\n"),
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

	if (DelegateOutParamIndex.Num() > 0)
	{
		SuperClassContent = TEXT("FRefDelegate");

		BindFunctionContent = TEXT(
			"\t\tpublic void Bind(UObject InObject, Delegate InDelegate) => DelegateUtils.Delegate_Bind(this, InDelegate);\n"
			"\n"
			"\t\tpublic void Bind(Delegate InDelegate) => DelegateUtils.Delegate_Bind(this, InDelegate);\n"
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
			if (DelegateParams.Num() > 0)
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
			SuperClassContent += DelegateParams.Num() > 0
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
			if (DelegateParams.Num() > 0)
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
	                               *BindFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *ExecuteFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *DelegateDeclarationContent
	);

	auto ModuleName = GetModuleName(InDelegateProperty);

	auto DirectoryName = FPaths::Combine(GetGenerationPath(InDelegateProperty), ModuleName);

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

	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common"), TEXT("Script.Reflection.Delegate")};

	FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InMulticastDelegateProperty);

	auto DelegateFullName = FullClassContent;

	auto DelegateName = DelegateFullName.RightChop(1);

	TArray<FProperty*> DelegateParams;

	TArray<int32> DelegateOutParamIndex;

	FProperty* DelegateReturnParam = nullptr;

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
			DelegateOutParamIndex.Emplace(Index);

			DelegateDeclarationBody += TEXT("ref ");
		}

		DelegateDeclarationBody += FString::Printf(TEXT(
			"%s %s%s"
		),
		                                           *FGeneratorCore::GetPropertyType(DelegateParams[Index]),
		                                           *FGeneratorCore::GetName(DelegateParams[Index]->GetName()),
		                                           Index == DelegateParams.Num() - 1 ? TEXT("") : TEXT(", ")
		);
	}

	auto bIsSafeBroadcastFunction = true;

	for (auto Index = 0; Index < DelegateOutParamIndex.Num(); ++Index)
	{
		if (!FGeneratorCore::IsSafeProperty(DelegateParams[DelegateOutParamIndex[Index]]))
		{
			bIsSafeBroadcastFunction = false;

			break;
		}
	}

	auto BroadcastFunctionDeclaration = FString::Printf(TEXT(
		"public %s%s Broadcast(%s)\n"
	),
	                                                    bIsSafeBroadcastFunction == true ? TEXT("") : TEXT("unsafe "),
	                                                    *DelegateReturnType,
	                                                    *DelegateDeclarationBody
	);

	auto BroadcastFunctionCallBody = FString(TEXT(
		"MulticastDelegateUtils.MulticastDelegate_Broadcast(this, out var __OutValue"));

	for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
	{
		if (DelegateOutParamIndex.Contains(Index) == false)
		{
			BroadcastFunctionCallBody += ", " + FGeneratorCore::GetParamName(DelegateParams[Index]);
		}
	}

	BroadcastFunctionCallBody += TEXT(");");

	TArray<FString> BroadcastFunctionOutParams;

	for (auto Index = 0; Index < DelegateOutParamIndex.Num(); ++Index)
	{
		BroadcastFunctionOutParams.Emplace(FString::Printf(TEXT(
			"%s = %s;"
		),
		                                                   *FGeneratorCore::GetName(
			                                                   DelegateParams[DelegateOutParamIndex[Index]]->GetName()),
		                                                   *FGeneratorCore::GetOutParamString(
			                                                   DelegateParams[DelegateOutParamIndex[Index]], Index)));
	}

	FString BroadcastFunctionReturnParamBody;

	if (DelegateReturnParam != nullptr)
	{
		BroadcastFunctionReturnParamBody = FString::Printf(TEXT(
			"return %s;"
		),
		                                                   *FGeneratorCore::GetReturnParamName(DelegateReturnParam));
	}

	if (bIsSafeBroadcastFunction == false)
	{
		UsingNameSpaces.Add(TEXT("IntPtr = Script.Common.IntPtr"));
	}

	FString BroadcastFunctionOutParamBody;

	for (auto BroadcastFunctionOutParam : BroadcastFunctionOutParams)
	{
		BroadcastFunctionOutParamBody += FString::Printf(TEXT(
			"\n\t\t\t%s\n"),
		                                                 *BroadcastFunctionOutParam);
	}

	auto BroadcastFunctionImplementationBody = FString::Printf(TEXT(
		"\t\t\t%s\n"
		"%s"
		"%s"
		"%s"
	),
	                                                           *BroadcastFunctionCallBody,
	                                                           *BroadcastFunctionOutParamBody,
	                                                           BroadcastFunctionReturnParamBody.IsEmpty()
		                                                           ? TEXT("")
		                                                           : TEXT("\n"),
	                                                           BroadcastFunctionReturnParamBody.IsEmpty()
		                                                           ? TEXT("")
		                                                           : *FString::Printf(TEXT(
			                                                           "\t\t\t%s\n"),
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

	if (DelegateOutParamIndex.Num() > 0)
	{
		SuperClassContent = TEXT("FRefMulticastDelegate");

		ContainsFunctionContent = TEXT(
			"\t\tpublic Boolean Contains(UObject _, Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_Contains(this, InDelegate);\n"
			"\n"
			"\t\tpublic Boolean Contains(Delegate InDelegate)=> MulticastDelegateUtils.MulticastDelegate_Contains(this, InDelegate);\n"
		);

		AddFunctionContent = TEXT(
			"\t\tpublic void Add(UObject _, Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_Add(this, InDelegate);\n"
			"\n"
			"\t\tpublic void Add(Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_Add(this, InDelegate);\n"
		);

		AddUniqueFunctionContent = TEXT(
			"\t\tpublic void AddUnique(UObject _, Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_AddUnique(this, InDelegate);\n"
			"\n"
			"\t\tpublic void AddUnique(Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_AddUnique(this, InDelegate);\n"
		);

		RemoveFunctionContent = TEXT(
			"\t\tpublic void Remove(UObject _, Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_Remove(this, InDelegate);\n"
			"\n"
			"\t\tpublic void Remove(Delegate InDelegate) => MulticastDelegateUtils.MulticastDelegate_Remove(this, InDelegate);\n"
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
			if (DelegateParams.Num() > 0)
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
			SuperClassContent += DelegateParams.Num() > 0
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
			if (DelegateParams.Num() > 0)
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
	                               *ContainsFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *AddFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *AddUniqueFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *RemoveFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *BroadcastFunctionContent,
	                               DelegateOutParamIndex.Num() > 0 ? TEXT("\n") : TEXT(""),
	                               *DelegateDeclarationContent
	);

	auto ModuleName = GetModuleName(InMulticastDelegateProperty);

	auto DirectoryName = FPaths::Combine(GetGenerationPath(InMulticastDelegateProperty), ModuleName);

	auto FileName = FPaths::Combine(DirectoryName, DelegateName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

FString FDelegateGenerator::GetModuleName(const FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	return FUnrealCSharpFunctionLibrary::GetModuleName(InDelegateProperty->SignatureFunction);
}

FString FDelegateGenerator::GetModuleName(const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	return FUnrealCSharpFunctionLibrary::GetModuleName(InMulticastDelegateProperty->SignatureFunction);
}

FString FDelegateGenerator::GetGenerationPath(const FField* InField)
{
	if (InField == nullptr || InField->GetOutermost() == nullptr)
	{
		return TEXT("");
	}

	return FUnrealCSharpFunctionLibrary::GetGenerationPath(InField->GetOutermost()->GetName());
}
