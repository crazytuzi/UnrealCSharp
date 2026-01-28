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

	FString DelegateDeclarationContent;

	FString ExecuteFunctionContent;

	FString BindFunctionContent;

	FString IsBoundFunctionContent;

	FString UnbindFunctionContent;

	FString ClearFunctionContent;

	FString GCHandleContent;

	TSet<FString> UsingNameSpaces{
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
		"\n\t\t~%s() => FDelegateImplementation.FDelegate_UnRegisterImplementation(%s);\n\n"
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
		"\t\t}\n\n"
	),
	                                         *ExecuteFunctionDeclaration,
	                                         *ExecuteFunctionImplementationBody
	);

	DelegateDeclarationContent = FString::Printf(TEXT(
		"\t\tpublic delegate %s Delegate(%s);\n\n"
	),
	                                             *DelegateReturnType,
	                                             *DelegateDeclarationBody);

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));

	BindFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void Bind(UObject InObject, Delegate InDelegate) => FDelegateImplementation.FDelegate_BindImplementation(%s, InObject.%s, InDelegate);\n\n"
	),
	                                      *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                      *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	UnbindFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void Unbind() => FDelegateImplementation.FDelegate_UnBindImplementation(%s);\n\n"
	),
	                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	ClearFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void Clear() => FDelegateImplementation.FDelegate_ClearImplementation(%s);\n\n"
	),
	                                       *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	IsBoundFunctionContent = FString::Printf(TEXT(
		"\t\tpublic bool IsBound() => FDelegateImplementation.FDelegate_IsBoundImplementation(%s);\n\n"
	),
	                                         *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	GCHandleContent = FString::Printf(TEXT(
		"\t\tpublic nint %s { get; set; }\n"
	),
	                                  *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

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
		"%s\n"
		"namespace %s\n"
		"{\n"
		"\tpublic class %s : IGarbageCollectionHandle\n"
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
		"\t}\n"
		"}\n"
	),
	                               *FGeneratorCore::GetGeneratorHeaderComment(),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *ClassContent,
	                               *DelegateDeclarationContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               *ExecuteFunctionContent,
	                               *BindFunctionContent,
	                               *UnbindFunctionContent,
	                               *ClearFunctionContent,
	                               *IsBoundFunctionContent,
	                               *GCHandleContent
	);

	const auto FileName = FGeneratorCore::GetFileName(InDelegateProperty);

	FGeneratorCore::AddGeneratorFile(FileName);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FileName, Content);
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

	FString DelegateDeclarationContent;

	FString BroadcastFunctionContent;

	FString IsBoundFunctionContent;

	FString ContainsFunctionContent;

	FString AddFunctionContent;

	FString AddUniqueFunctionContent;

	FString RemoveFunctionContent;

	FString RemoveAllFunctionContent;

	FString ClearFunctionContent;

	FString GCHandleContent;

	TSet<FString> UsingNameSpaces{
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
		"\n\t\t~%s() => FMulticastDelegateImplementation.FMulticastDelegate_UnRegisterImplementation(%s);\n\n"
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
		"\t\t}\n\n"
	),
	                                           *BroadcastFunctionDeclaration,
	                                           *BroadcastFunctionImplementationBody
	);

	DelegateDeclarationContent = FString::Printf(TEXT(
		"\t\tpublic delegate void Delegate(%s);\n\n"
	),
	                                             *DelegateDeclarationBody);

	IsBoundFunctionContent = FString::Printf(TEXT(
		"\t\tpublic bool IsBound() => FMulticastDelegateImplementation.FMulticastDelegate_IsBoundImplementation(%s);\n\n"
	),
	                                         *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	ContainsFunctionContent = FString::Printf(TEXT(
		"\t\tpublic bool Contains(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(%s, InObject.%s, InDelegate);\n\n"
	),
	                                          *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                          *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	AddFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void Add(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(%s, InObject.%s, InDelegate);\n\n"
	),
	                                     *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                     *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	AddUniqueFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void AddUnique(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(%s, InObject.%s, InDelegate);\n\n"
	),
	                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	RemoveFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void Remove(UObject InObject, Delegate InDelegate) => FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(%s, InObject.%s, InDelegate);\n\n"
	),
	                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	RemoveAllFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void RemoveAll(UObject InObject) => FMulticastDelegateImplementation.FMulticastDelegate_RemoveAllImplementation(%s, InObject.%s);\n\n"
	),
	                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
	                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	ClearFunctionContent = FString::Printf(TEXT(
		"\t\tpublic void Clear() => FMulticastDelegateImplementation.FMulticastDelegate_ClearImplementation(%s);\n\n"
	),
	                                       *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	GCHandleContent = FString::Printf(TEXT(
		"\t\tpublic nint %s { get; set; }\n"
	),
	                                  *PROPERTY_GARBAGE_COLLECTION_HANDLE
	);

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));

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
		"\tpublic class %s : IGarbageCollectionHandle\n"
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
		"%s"
		"\t}\n"
		"}\n"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent,
	                               *ClassContent,
	                               *DelegateDeclarationContent,
	                               *ConstructorContent,
	                               *DestructorContent,
	                               *BroadcastFunctionContent,
	                               *IsBoundFunctionContent,
	                               *ContainsFunctionContent,
	                               *AddFunctionContent,
	                               *AddUniqueFunctionContent,
	                               *RemoveFunctionContent,
	                               *RemoveAllFunctionContent,
	                               *ClearFunctionContent,
	                               *GCHandleContent
	);

	const auto FileName = FGeneratorCore::GetFileName(InMulticastDelegateProperty);

	FGeneratorCore::AddGeneratorFile(FileName);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FileName, Content);
}
