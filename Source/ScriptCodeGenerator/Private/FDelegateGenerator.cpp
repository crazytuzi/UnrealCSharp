#include "FDelegateGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/BufferMacro.h"
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
		                                           *FUnrealCSharpFunctionLibrary::Encode(DelegateParams[Index]),
		                                           Index == DelegateParams.Num() - 1 ? TEXT("") : TEXT(", ")
		);
	}

	auto ExecuteFunctionDeclaration = FString::Printf(TEXT(
		"public %s Execute(%s)\n"
	),
	                                                  *DelegateReturnType,
	                                                  *DelegateDeclarationBody
	);

	FString InBufferBody;

	auto bHasInBuffer = false;

	if (!DelegateParams.IsEmpty())
	{
		auto BufferSize = 0;

		for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
		{
			InBufferBody += FString::Printf(TEXT(
				"\t\t\t\t*(%s*)(%s%s) = %s;\n\n"
			),
			                                *FGeneratorCore::GetBufferCast(DelegateParams[Index]),
			                                IN_BUFFER_TEXT,
			                                BufferSize == 0
				                                ? TEXT("")
				                                : *FString::Printf(TEXT(
					                                " + %d"),
				                                                   BufferSize),
			                                *FGeneratorCore::GetParamName(DelegateParams[Index])
			);

			BufferSize += FGeneratorCore::GetBufferSize(DelegateParams[Index]);
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

	if (!DelegateRefParamIndex.IsEmpty())
	{
		auto BufferSize = 0;

		for (auto Index = 0; Index < DelegateRefParamIndex.Num(); ++Index)
		{
			BufferSize += FGeneratorCore::GetBufferSize(DelegateParams[DelegateRefParamIndex[Index]]);
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

	if (DelegateReturnParam != nullptr)
	{
		bHasReturnBuffer = true;

		ReturnBufferBody = FString::Printf(TEXT(
			"\t\t\t\tvar %s = stackalloc byte[%d];\n\n"
		),
		                                   RETURN_BUFFER_TEXT,
		                                   FGeneratorCore::GetBufferSize(DelegateReturnParam)
		);
	}

	auto ExecuteFunctionCallBody = FString::Printf(TEXT(
		"FDelegateImplementation.FDelegate_%sExecute%dImplementation(%s%s%s%s);\n"
	),
	                                               *FGeneratorCore::GetFunctionPrefix(DelegateReturnParam),
	                                               FGeneratorCore::GetFunctionIndex(DelegateReturnParam != nullptr,
		                                               !DelegateParams.IsEmpty(),
		                                               !DelegateRefParamIndex.IsEmpty(),
		                                               false,
		                                               false),
	                                               *PROPERTY_GARBAGE_COLLECTION_HANDLE,
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

	FString ExecuteFunctionReturnParamBody;

	if (DelegateReturnParam != nullptr)
	{
		ExecuteFunctionReturnParamBody = FString::Printf(TEXT(
			"return *(%s*)%s;"
		),
		                                                 *DelegateReturnType,
		                                                 RETURN_BUFFER_TEXT
		);
	}

	FString ExecuteFunctionOutParamBody;

	if (bHasOutBuffer)
	{
		auto BufferSize = 0;

		for (auto Index = 0; Index < DelegateRefParamIndex.Num(); ++Index)
		{
			ExecuteFunctionOutParamBody += FString::Printf(TEXT(
				"\n\t\t\t\t%s = *(%s*)(%s%s);\n"
			),
			                                               *FUnrealCSharpFunctionLibrary::Encode(
				                                               DelegateParams[DelegateRefParamIndex[Index]]),
			                                               *FGeneratorCore::GetPropertyType(
				                                               DelegateParams[DelegateRefParamIndex[Index]]),
			                                               OUT_BUFFER_TEXT,
			                                               BufferSize == 0
				                                               ? TEXT("")
				                                               : *FString::Printf(TEXT(
					                                               " + %d"),
					                                               BufferSize)
			);

			BufferSize += FGeneratorCore::GetBufferSize(DelegateParams[DelegateRefParamIndex[Index]]);
		}
	}

	auto ExecuteFunctionImplementationBody = FString::Printf(TEXT(
		"%s"
		"%s"
		"%s"
		"\t\t\t\t%s"
		"%s"
		"%s"
		"%s"
	),
	                                                         *InBufferBody,
	                                                         *OutBufferBody,
	                                                         *ReturnBufferBody,
	                                                         *ExecuteFunctionCallBody,
	                                                         *ExecuteFunctionOutParamBody,
	                                                         !ExecuteFunctionOutParamBody.IsEmpty() ||
	                                                         !ExecuteFunctionReturnParamBody.IsEmpty()
		                                                         ? TEXT("\n")
		                                                         : TEXT(""),
	                                                         ExecuteFunctionReturnParamBody.IsEmpty()
		                                                         ? TEXT("")
		                                                         : *FString::Printf(TEXT(
			                                                         "\t\t\t\t%s\n"
		                                                         ),
			                                                         *ExecuteFunctionReturnParamBody));

	ExecuteFunctionContent = FString::Printf(TEXT(
		"\t\t%s"
		"\t\t{\n"
		"\t\t\tunsafe\n"
		"\t\t\t{\n"
		"%s"
		"\t\t\t}\n"
		"\t\t}\n"
	),
	                                         *ExecuteFunctionDeclaration,
	                                         *ExecuteFunctionImplementationBody
	);

	if (!DelegateRefParamIndex.IsEmpty())
	{
		SuperClassContent = TEXT("FRefDelegate");

		BindFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void Bind(UObject InObject, Delegate InDelegate) => FDelegateImplementation.FDelegate_BindImplementation(%s, InObject.%s, InDelegate);\n"
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

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FGeneratorCore::GetFileName(InDelegateProperty), Content);
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
		DelegateParams.Emplace(*ParamIterator);

		UsingNameSpaces.Append(FGeneratorCore::GetPropertyTypeNameSpace(*ParamIterator));
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
		                                           *FUnrealCSharpFunctionLibrary::Encode(DelegateParams[Index]),
		                                           Index == DelegateParams.Num() - 1 ? TEXT("") : TEXT(", ")
		);
	}

	auto BroadcastFunctionDeclaration = FString::Printf(TEXT(
		"public void Broadcast(%s)\n"
	),
	                                                    *DelegateDeclarationBody
	);

	FString InBufferBody;

	auto bHasInBuffer = false;

	if (!DelegateParams.IsEmpty())
	{
		auto BufferSize = 0;

		for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
		{
			InBufferBody += FString::Printf(TEXT(
				"\t\t\t\t*(%s*)(%s%s) = %s;\n\n"
			),
			                                *FGeneratorCore::GetBufferCast(DelegateParams[Index]),
			                                IN_BUFFER_TEXT,
			                                BufferSize == 0
				                                ? TEXT("")
				                                : *FString::Printf(TEXT(
					                                " + %d"),
				                                                   BufferSize),
			                                *FGeneratorCore::GetParamName(DelegateParams[Index])
			);

			BufferSize += FGeneratorCore::GetBufferSize(DelegateParams[Index]);
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

	if (!DelegateRefParamIndex.IsEmpty())
	{
		auto BufferSize = 0;

		for (auto Index = 0; Index < DelegateRefParamIndex.Num(); ++Index)
		{
			BufferSize += FGeneratorCore::GetBufferSize(DelegateParams[DelegateRefParamIndex[Index]]);
		}

		OutBufferBody = FString::Printf(TEXT(
			"\t\t\t\tvar %s = stackalloc byte[%d];\n\n"
		),
		                                OUT_BUFFER_TEXT,
		                                BufferSize
		);

		bHasOutBuffer = BufferSize != 0;
	}

	auto BroadcastFunctionCallBody = FString::Printf(TEXT(
		"FMulticastDelegateImplementation.FMulticastDelegate_%sBroadcast%dImplementation(%s%s%s);"
	),
	                                                 *FGeneratorCore::GetFunctionPrefix(nullptr),
	                                                 FGeneratorCore::GetFunctionIndex(false,
		                                                 !DelegateParams.IsEmpty(),
		                                                 !DelegateRefParamIndex.IsEmpty(),
		                                                 false,
		                                                 false),
	                                                 *PROPERTY_GARBAGE_COLLECTION_HANDLE,
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
		                                                 : TEXT("")
	);

	FString BroadcastFunctionOutParamBody;

	if (bHasOutBuffer)
	{
		auto BufferSize = 0;

		for (auto Index = 0; Index < DelegateRefParamIndex.Num(); ++Index)
		{
			BroadcastFunctionOutParamBody += FString::Printf(TEXT(
				"\n\t\t\t\t%s = *(%s*)(%s%s);\n"
			),
			                                                 *FUnrealCSharpFunctionLibrary::Encode(
				                                                 DelegateParams[DelegateRefParamIndex[Index]]),
			                                                 *FGeneratorCore::GetPropertyType(
				                                                 DelegateParams[DelegateRefParamIndex[Index]]),
			                                                 OUT_BUFFER_TEXT,
			                                                 BufferSize == 0
				                                                 ? TEXT("")
				                                                 : *FString::Printf(TEXT(
					                                                 " + %d"),
					                                                 BufferSize)
			);

			BufferSize += FGeneratorCore::GetBufferSize(DelegateParams[DelegateRefParamIndex[Index]]);
		}
	}

	auto BroadcastFunctionImplementationBody = FString::Printf(TEXT(
		"%s"
		"%s"
		"\t\t\t\t%s\n"
		"%s"
		"%s"
	),
	                                                           *InBufferBody,
	                                                           *OutBufferBody,
	                                                           *BroadcastFunctionCallBody,
	                                                           *BroadcastFunctionOutParamBody,
	                                                           !BroadcastFunctionOutParamBody.IsEmpty()
		                                                           ? TEXT("\n")
		                                                           : TEXT("")
	);

	BroadcastFunctionContent = FString::Printf(TEXT(
		"\t\t%s"
		"\t\t{\n"
		"\t\t\tunsafe\n"
		"\t\t\t{\n"
		"%s"
		"\t\t\t}\n"
		"\t\t}\n"
	),
	                                           *BroadcastFunctionDeclaration,
	                                           *BroadcastFunctionImplementationBody
	);

	if (!DelegateRefParamIndex.IsEmpty())
	{
		SuperClassContent = TEXT("FRefMulticastDelegate");

		ContainsFunctionContent = FString::Printf(TEXT(
			"\t\tpublic bool Contains(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(%s, InObject.%s, InDelegate);\n"
		),
		                                          *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                          *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		AddFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void Add(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(%s, InObject.%s, InDelegate);\n"
		),
		                                     *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                     *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		AddUniqueFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void AddUnique(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(%s, InObject.%s, InDelegate);\n"
		),
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		RemoveFunctionContent = FString::Printf(TEXT(
			"\t\tpublic void Remove(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(%s, InObject.%s, InDelegate);\n"
		),
		                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		DelegateDeclarationContent = FString::Printf(TEXT(
			"\t\tpublic delegate void Delegate(%s);\n"
		),
		                                             *DelegateDeclarationBody);

		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));
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

		for (auto Index = 0; Index < DelegateParams.Num(); ++Index)
		{
			SuperClassContent += FString::Printf(TEXT(
				"%s%s"
			),
			                                     Index != 0 ? TEXT(", ") : TEXT(""),
			                                     *FGeneratorCore::GetPropertyType(DelegateParams[Index]));
		}

		if (!DelegateParams.IsEmpty())
		{
			SuperClassContent += TEXT(">>");
		}
		else
		{
			SuperClassContent += TEXT(">");
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

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FGeneratorCore::GetFileName(InMulticastDelegateProperty), Content);
}
