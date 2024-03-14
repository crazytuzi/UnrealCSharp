#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"

TSet<TPair<FString, FString>> FDelegateGenerator::Delegate;

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

	auto ClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InDelegateProperty);

	if (Delegate.Contains({NameSpaceContent, ClassContent}))
	{
		return;
	}

	Delegate.Add({NameSpaceContent, ClassContent});

	FString SuperClassContent;

	FString BindFunctionContent;

	FString ExecuteFunctionContent;

	FString DelegateDeclarationContent;

	TSet<FString> UsingNameSpaces{
		NAMESPACE_SYSTEM,
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LIBRARY)
	};

	TArray<FProperty*> DelegateParams;

	TArray<int32> DelegateRefParamIndex;

	FProperty* DelegateReturnParam = nullptr;

	const auto ConstructorContent = FString::Printf(TEXT(
		"\t\tpublic %s() => FDelegateImplementation.FDelegate_RegisterImplementation(this);\n"
	),
	                                                *ClassContent
	);

	const auto DestructorContent = FString::Printf(TEXT(
		"\n\t\t~%s() => FDelegateImplementation.FDelegate_UnRegisterImplementation(%s);\n"
	),
	                                               *ClassContent,
	                                               *PROPERTY_GARBAGE_COLLECTION_HANDLE
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
		"FDelegateImplementation.FDelegate_Execute%dImplementation(%s%s"
	),
	                                               FGeneratorCore::GetFunctionIndex(DelegateReturnParam != nullptr,
		                                               !DelegateParams.IsEmpty(),
		                                               !DelegateRefParamIndex.IsEmpty()),
	                                               *PROPERTY_GARBAGE_COLLECTION_HANDLE,
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

		BindFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void Bind(UObject InObject, Delegate InDelegate) => FDelegateImplementation.FDelegate_BindImplementation(%s, InDelegate);\n"
			"\n"
			"\t\tpublic void Bind(Delegate InDelegate) => FDelegateImplementation.FDelegate_BindImplementation(%s, InDelegate);\n"
		),
		                                      *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                      *PROPERTY_GARBAGE_COLLECTION_HANDLE
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
	                               *ClassContent,
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

	auto ModuleRelativePath = FPaths::Combine(FPaths::GetPath(InDelegateProperty->GetMetaData(TEXT("ModuleRelativePath"))),
		(SignatureFunction->GetOuterUClass()->ClassGeneratedBy == nullptr ? TEXT("F") : TEXT("")) + InDelegateProperty->GetName());

	auto FileName = FPaths::Combine(DirectoryName, ModuleRelativePath);

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

	auto ClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InMulticastDelegateProperty);

	if (Delegate.Contains({NameSpaceContent, ClassContent}))
	{
		return;
	}

	Delegate.Add({NameSpaceContent, ClassContent});

	FString SuperClassContent;

	FString ContainsFunctionContent;

	FString AddFunctionContent;

	FString AddUniqueFunctionContent;

	FString RemoveFunctionContent;

	FString BroadcastFunctionContent;

	FString DelegateDeclarationContent;

	TSet<FString> UsingNameSpaces{
		NAMESPACE_SYSTEM,
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LIBRARY)
	};

	TArray<FProperty*> DelegateParams;

	TArray<int32> DelegateRefParamIndex;

	FProperty* DelegateReturnParam = nullptr;

	const auto ConstructorContent = FString::Printf(TEXT(
		"\t\tpublic %s() => FMulticastDelegateImplementation.FMulticastDelegate_RegisterImplementation(this);\n"
	),
	                                                *ClassContent
	);

	const auto DestructorContent = FString::Printf(TEXT(
		"\n\t\t~%s() => FMulticastDelegateImplementation.FMulticastDelegate_UnRegisterImplementation(%s);\n"
	),
	                                               *ClassContent,
	                                               *PROPERTY_GARBAGE_COLLECTION_HANDLE
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
		"FMulticastDelegateImplementation.FMulticastDelegate_Broadcast%dImplementation(%s%s"
	),
	                                                 FGeneratorCore::GetFunctionIndex(DelegateReturnParam != nullptr,
		                                                 !DelegateParams.IsEmpty(),
		                                                 !DelegateRefParamIndex.IsEmpty()),
	                                                 *PROPERTY_GARBAGE_COLLECTION_HANDLE,
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

		ContainsFunctionContent = FString::Printf(TEXT(
			"\t\tpublic bool Contains(UObject _, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(%s, InDelegate);\n"
			"\n"
			"\t\tpublic bool Contains(Delegate InDelegate)=> FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(%s, InDelegate);\n"
		),
		                                          *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                          *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		AddFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void Add(UObject _, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(%s, InDelegate);\n"
			"\n"
			"\t\tpublic void Add(Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(%s, InDelegate);\n"
		),
		                                     *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                     *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		AddUniqueFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void AddUnique(UObject _, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(%s, InDelegate);\n"
			"\n"
			"\t\tpublic void AddUnique(Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(%s, InDelegate);\n"
		),
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		RemoveFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void Remove(UObject _, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(%s, InDelegate);\n"
			"\n"
			"\t\tpublic void Remove(Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(%s, InDelegate);\n"
		),
		                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE
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
	                               *ClassContent,
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

	auto ModuleRelativePath = FPaths::Combine(FPaths::GetPath(InMulticastDelegateProperty->GetMetaData(TEXT("ModuleRelativePath"))),
		(SignatureFunction->GetOuterUClass()->ClassGeneratedBy == nullptr ? TEXT("F") : TEXT("")) + InMulticastDelegateProperty->GetName());

	auto FileName = FPaths::Combine(DirectoryName, ModuleRelativePath);

	FGeneratorCore::SaveStringToFile(FileName + TEXT(".cs"), Content);
}
