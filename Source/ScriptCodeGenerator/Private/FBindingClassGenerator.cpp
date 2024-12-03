#include "FBindingClassGenerator.h"
#include "Binding/FBinding.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/BindingMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "FGeneratorCore.h"

void FBindingClassGenerator::Generator()
{
	for (const auto& Class : FBinding::Get().GetClasses())
	{
		Generator(Class);
	}
}

void FBindingClassGenerator::Generator(const FBindingClass* InClass)
{
	if (InClass->IsSet())
	{
		GeneratorPartial(InClass);

		GeneratorImplementation(InClass);
	}
}

void FBindingClassGenerator::GeneratorPartial(const FBindingClass* InClass)
{
	FString UsingNameSpaceContent;

	TSet<FString> UsingNameSpaces{InClass->GetImplementationNameSpace()};

	const auto& NameSpaceContent = InClass->GetTypeInfo().GetNameSpace();

	auto ClassContent = InClass->GetClass();

	FString SubscriptContent;

	FString PropertyContent;

	FString FunctionContent;

	FString GCHandleContent;

	bool bHasEqualTo = false;

	if (InClass->GetSubscript().IsSet())
	{
		UsingNameSpaces.Append(InClass->GetSubscript().GetReturn()->GetNameSpace());

		UsingNameSpaces.Append(InClass->GetSubscript().GetParams()[0]->GetNameSpace());

		auto SubscriptGetContent = FString::Printf(TEXT(
			"\t\t\tget => %s%s.%s(%s, %s)%s;\n"
		),
		                                           InClass->GetSubscript().GetReturn()->IsPrimitive()
			                                           ? *FString::Printf(TEXT(
				                                           "(%s)"
			                                           ),
			                                                              *InClass->GetSubscript().GetReturn()->
			                                                              GetName()
			                                           )
			                                           : TEXT(""),
		                                           *BINDING_COMBINE_CLASS_IMPLEMENTATION(ClassContent),
		                                           *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
			                                           ClassContent,
			                                           InClass->GetSubscript().GetGetImplementationName()),
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                           *InClass->GetSubscript().GetParamNames()[0],
		                                           !InClass->GetSubscript().GetReturn()->IsPrimitive()
			                                           ? *FString::Printf(TEXT(
				                                           " as %s"
			                                           ),
			                                                              *InClass->GetSubscript().GetReturn()->
			                                                              GetName())
			                                           : TEXT("")

		);

		auto SubscriptSetContent = FString::Printf(TEXT(
			"\t\t\tset => %s.%s(%s, %s, %s);\n"
		),
		                                           *BINDING_COMBINE_CLASS_IMPLEMENTATION(ClassContent),
		                                           *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
			                                           ClassContent,
			                                           InClass->GetSubscript().GetSetImplementationName()),
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                           *InClass->GetSubscript().GetParamNames()[0],
		                                           InClass->GetSubscript().GetParams()[0]->IsPrimitive()
			                                           ? TEXT("value")
			                                           : *FString::Printf(TEXT(
				                                           "value.%s"),
			                                                              *PROPERTY_GARBAGE_COLLECTION_HANDLE
			                                           )
		);

		SubscriptContent = FString::Printf(TEXT(
			"\t\tpublic %s %s[%s %s]\n"
			"\t\t{\n"
			"%s"
			"\n"
			"%s"
			"\t\t}\n"
		),
		                                   *InClass->GetSubscript().GetReturn()->GetName(),
		                                   *InClass->GetSubscript().GetFunctionName(),
		                                   *InClass->GetSubscript().GetParams()[0]->GetName(),
		                                   *InClass->GetSubscript().GetParamNames()[0],
		                                   *SubscriptGetContent,
		                                   *SubscriptSetContent
		);
	}

	for (const auto& Property : InClass->GetProperties())
	{
		UsingNameSpaces.Append(Property.GetNameSpace());

		auto PropertyName = Property.GetPropertyName();

		auto PropertyType = Property.GetName();

		FString PropertyGetContent;

		FString PropertySetContent;

		const auto bRead = (static_cast<int32>(Property.GetAccess()) &
				static_cast<int32>(EBindingPropertyAccess::OnlyRead))
			== static_cast<int32>(EBindingPropertyAccess::OnlyRead);

		const auto bWrite = (static_cast<int32>(Property.GetAccess()) &
				static_cast<int32>(EBindingPropertyAccess::OnlyWrite))
			== static_cast<int32>(EBindingPropertyAccess::OnlyWrite);

		if (bRead)
		{
			PropertyGetContent = FString::Printf(TEXT(
				"\t\t\tget\n"
				"\t\t\t{\n"
				"\t\t\t\tunsafe\n"
				"\t\t\t\t{\n"
				"\t\t\t\t\tvar __ReturnBuffer = stackalloc byte[%d];\n"
				"\n"
				"\t\t\t\t\t%s.%s(%s, __ReturnBuffer);\n"
				"\n"
				"\t\t\t\t\treturn *(%s*)__ReturnBuffer;\n"
				""
				"\t\t\t\t}\n"
				"\t\t\t}\n"
			),
			                                     Property.GetBufferSize(),
			                                     *BINDING_COMBINE_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName)),
			                                     Property.IsStatic()
				                                     ? TEXT("nint.Zero")
				                                     : *PROPERTY_GARBAGE_COLLECTION_HANDLE,
			                                     *Property.GetName()

			);
		}

		if (bWrite)
		{
			PropertySetContent = FString::Printf(TEXT(
				"\t\t\tset\n"
				"\t\t\t{\n"
				"\t\t\t\tunsafe\n"
				"\t\t\t\t{\n"
				"\t\t\t\t\tvar __InBuffer = stackalloc byte[%d];\n"
				"\n"
				"\t\t\t\t\t*(%s*)__InBuffer = %s;\n"
				"\n"
				"\t\t\t\t\t%s.%s(%s, __InBuffer);\n"
				"\t\t\t\t}\n"
				"\t\t\t}\n"
			),
			                                     Property.GetBufferSize(),
			                                     Property.IsPrimitive()
				                                     ? *Property.GetName()
				                                     : TEXT("nint"),
			                                     Property.IsPrimitive()
				                                     ? TEXT("value")
				                                     : *FString::Printf(TEXT(
					                                     "value?.%s ?? nint.Zero"),
				                                                        *PROPERTY_GARBAGE_COLLECTION_HANDLE
				                                     ),
			                                     *BINDING_COMBINE_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
				                                     ClassContent, (BINDING_PROPERTY_SET + PropertyName)),
			                                     Property.IsStatic()
				                                     ? TEXT("nint.Zero")
				                                     : *PROPERTY_GARBAGE_COLLECTION_HANDLE


			);
		}

		if (bRead || bWrite)
		{
			PropertyContent += FString::Printf(TEXT(
				"%s"
				"\t\tpublic %s%s %s\n"
				"\t\t{\n"
				"%s"
				"%s"
				"%s"
				"\t\t}\n"
			),
			                                   PropertyContent.IsEmpty() ? TEXT("") : TEXT("\n"),
			                                   Property.IsStatic() ? TEXT("static ") : TEXT(""),
			                                   *PropertyType,
			                                   *PropertyName,
			                                   *PropertyGetContent,
			                                   bWrite ? TEXT("\n") : TEXT(""),
			                                   *PropertySetContent
			);
		}
	}

	TArray<FString> OverrideFunctions;

	if (InClass->IsReflectionClass())
	{
		OverrideFunctions = FGeneratorCore::GetOverrideFunctions(NameSpaceContent[0], ClassContent);
	}

	for (const auto& Function : InClass->GetFunctions())
	{
		if (InClass->IsReflectionClass())
		{
			if (OverrideFunctions.Contains(Function.GetFunctionName()))
			{
				continue;
			}
		}

		if (!bHasEqualTo)
		{
			if (Function.GetFunctionName() == TEXT("operator =="))
			{
				bHasEqualTo = true;
			}
		}

		FString FunctionStatic = Function.IsStatic() ? TEXT("static") : TEXT("");

		FString FunctionAccessSpecifiers = TEXT("public");

		const auto& Params = Function.GetParams();

		for (auto Param : Params)
		{
			UsingNameSpaces.Append(Param->GetNameSpace());
		}

		FString FunctionReturnType = TEXT("void");

		if (Function.GetReturn() != nullptr)
		{
			FunctionReturnType = Function.GetReturn()->GetName();

			UsingNameSpaces.Append(Function.GetReturn()->GetNameSpace());
		}

		FString FunctionDeclarationBody;

		TArray<int32> FunctionRefParamIndex;

		TArray<FString> FunctionParamName;

		FString FunctionDefaultParamBody;

		const auto& DefaultArguments = Function.GetDefaultArguments();

		if (!Function.GetParamNames().IsEmpty())
		{
			FunctionParamName = Function.GetParamNames();

			auto DefaultArgumentIndex = 0;

			for (auto Index = 0; Index < Params.Num(); ++Index)
			{
				if (Params[Index]->IsRef())
				{
					FunctionRefParamIndex.Add(Index);

					FunctionDeclarationBody += TEXT("ref ");
				}

				FString DefaultParam;

				if (Params.Num() - Index <= DefaultArguments.Num())
				{
					if (Params[Index]->IsPrimitive())
					{
						DefaultParam = FString::Printf(TEXT(
							" = %s"),
						                               *DefaultArguments[DefaultArgumentIndex]
						);
					}
					else
					{
						DefaultParam = TEXT(" = null");

						if (!DefaultArguments[DefaultArgumentIndex].IsEmpty())
						{
							FunctionDefaultParamBody += FString::Printf(TEXT(
								"%s\t\t\t%s \?\?= %s;\n"),
							                                            FunctionDefaultParamBody.IsEmpty()
								                                            ? TEXT("")
								                                            : TEXT("\n"),
							                                            *FunctionParamName[Index],
							                                            *DefaultArguments[DefaultArgumentIndex]
							);
						}
					}

					DefaultArgumentIndex++;
				}

				FunctionDeclarationBody += FString::Printf(TEXT(
					"%s %s%s%s"
				),
				                                           *Params[Index]->GetName(),
				                                           *FunctionParamName[Index],
				                                           *DefaultParam,
				                                           Index == Params.Num() - 1 ? TEXT("") : TEXT(", ")
				);
			}
		}
		else
		{
			for (auto Index = 0; Index < Params.Num(); ++Index)
			{
				if (Params[Index]->IsRef())
				{
					FunctionRefParamIndex.Add(Index);

					FunctionDeclarationBody += TEXT("ref ");

					FunctionParamName.Add(FString::Printf(TEXT(
						"OutValue%d"
					),
					                                      FunctionRefParamIndex.Num() - 1
					));
				}
				else
				{
					FunctionParamName.Add(FString::Printf(TEXT(
						"InValue%d"
					),
					                                      Index - FunctionRefParamIndex.Num()
					));
				}

				FunctionDeclarationBody += FString::Printf(TEXT(
					"%s %s%s"
				),
				                                           *Params[Index]->GetName(),
				                                           *FunctionParamName[Index],
				                                           Index == Params.Num() - 1 ? TEXT("") : TEXT(", ")
				);
			}
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"%s%s%s%s%s%s%s%s(%s)"
		),
		                                           Function.IsDestructor() == true
			                                           ? TEXT("")
			                                           : *FunctionAccessSpecifiers,
		                                           Function.IsDestructor() == true ? TEXT("") : TEXT(" "),
		                                           *FunctionStatic,
		                                           FunctionStatic.IsEmpty() == true ? TEXT("") : TEXT(" "),
		                                           [Function]()
		                                           {
			                                           static auto FunctionInteract =
				                                           TMap<EFunctionInteract, const TCHAR*>
				                                           {
					                                           {EFunctionInteract::None, TEXT("")},
					                                           {EFunctionInteract::New, TEXT("new ")},
					                                           {EFunctionInteract::Virtual, TEXT("virtual ")},
					                                           {EFunctionInteract::Override, TEXT("override ")},
				                                           };

			                                           return FunctionInteract[Function.GetFunctionInteract()];
		                                           }(),
		                                           (Function.IsConstructor() == true || Function.IsDestructor() == true)
			                                           ? TEXT("")
			                                           : *FunctionReturnType,
		                                           (Function.IsConstructor() == true || Function.IsDestructor() == true)
			                                           ? TEXT("")
			                                           : TEXT(" "),
		                                           *Function.GetFunctionName(),
		                                           *FunctionDeclarationBody
		);

		FString InBufferBody;

		auto bHasInBuffer = false;

		if (!Params.IsEmpty())
		{
			auto BufferSize = 0;

			for (auto Index = 0; Index < Params.Num(); ++Index)
			{
				InBufferBody += FString::Printf(TEXT(
					"\t\t\t\t*(%s*)(__InBuffer%s) = %s;\n\n"
				),
				                                *Params[Index]->GetName(),
				                                BufferSize == 0
					                                ? TEXT("")
					                                : *FString::Printf(TEXT(
						                                " + %d"),
					                                                   BufferSize),
				                                *FunctionParamName[Index]
				);

				BufferSize += Params[Index]->GetBufferSize();
			}

			InBufferBody = FString::Printf(TEXT(
				"\t\t\t\tvar __InBuffer = stackalloc byte[%d];\n\n"
				"%s"
			),
			                               BufferSize,
			                               *InBufferBody
			);

			bHasInBuffer = BufferSize != 0;
		}

		FString OutBufferBody;

		auto bHasOutBuffer = false;

		if (!FunctionRefParamIndex.IsEmpty())
		{
			auto BufferSize = 0;

			for (auto Index = 0; Index < FunctionRefParamIndex.Num(); ++Index)
			{
				BufferSize += Params[FunctionRefParamIndex[Index]]->GetBufferSize();
			}

			OutBufferBody = FString::Printf(TEXT(
				"\t\t\t\tvar __OutBuffer = stackalloc byte[%d];\n\n"
			),
			                                BufferSize
			);

			bHasOutBuffer = BufferSize != 0;
		}

		FString ReturnBufferBody;

		auto bHasReturnBuffer = false;

		if (Function.GetReturn() != nullptr)
		{
			bHasReturnBuffer = true;

			ReturnBufferBody = FString::Printf(TEXT(
				"\t\t\t\tvar __ReturnBuffer = stackalloc byte[%d];\n\n"
			),
			                                   Function.GetReturn()->GetBufferSize()
			);
		}

		auto FunctionCallBody = FString::Printf(TEXT(
			"%s.%s(%s%s%s%s);\n"
		),
		                                        *BINDING_COMBINE_CLASS_IMPLEMENTATION(ClassContent),
		                                        *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
			                                        ClassContent, Function.GetFunctionImplementationName()),
		                                        Function.IsStatic() == true
			                                        ? TEXT("nint.Zero")
			                                        : Function.IsConstructor()
			                                        ? TEXT("this")
			                                        : *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                        bHasInBuffer ? TEXT(", __InBuffer") : TEXT(""),
		                                        bHasOutBuffer ? TEXT(", __OutBuffer") : TEXT(""),
		                                        bHasReturnBuffer ? TEXT(", __ReturnBuffer") : TEXT("")
		);

		FString FunctionReturnParamBody;

		if (Function.GetReturn() != nullptr)
		{
			FunctionReturnParamBody = FString::Printf(TEXT(
				"return *(%s*)__ReturnBuffer;"
			),
			                                          *FunctionReturnType
			);
		}

		FString FunctionOutParamBody;

		if (bHasOutBuffer)
		{
			auto FunctionOutBufferIndex = FunctionRefParamIndex;

			FunctionOutBufferIndex.Sort();

			auto BufferSize = 0;

			for (auto Index = 0; Index < FunctionOutBufferIndex.Num(); ++Index)
			{
				FunctionOutParamBody += FString::Printf(TEXT(
					"\n\t\t\t\t%s = *(%s*)(__OutBuffer%s);\n"
				),
				                                        *FunctionParamName[FunctionOutBufferIndex[Index]],
				                                        *Params[FunctionOutBufferIndex[Index]]->GetName(),
				                                        BufferSize == 0
					                                        ? TEXT("")
					                                        : *FString::Printf(TEXT(
						                                        " + %d"),
					                                                           BufferSize)
				);

				BufferSize += Params[FunctionOutBufferIndex[Index]]->GetBufferSize();
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

		if (Function.IsConstructor())
		{
			FunctionImplementationBody = FString::Printf(TEXT(
				"\t\t\t\tif (GetType() == typeof(%s))\n"
				"\t\t\t\t{\n"
				"%s"
				"\t\t\t\t}\n"
			),
			                                             *ClassContent,
			                                             *FunctionImplementationBody.Replace(
				                                             TEXT("\t\t\t\t"), TEXT("\t\t\t\t\t"))
			);
		}

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
		                                   FunctionContent.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                   *FunctionDeclaration,
		                                   *FunctionImplementationBody
		);
	}

	if (bHasEqualTo)
	{
		FunctionContent += FString::Printf(TEXT(
			"\n\t\tpublic override bool Equals(object Other) => this == Other as %s;\n\n"
			"\t\tpublic override int GetHashCode() => (int)%s;\n"
		),
		                                   *ClassContent,
		                                   *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);
	}

	if (!InClass->IsReflectionClass() && InClass->GetBaseClass().IsEmpty())
	{
		GCHandleContent = FString::Printf(TEXT(
			"\t\tpublic nint %s { get; set; }\n"
		),
		                                  *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);

		UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()));
	}

	UsingNameSpaces.Remove(NameSpaceContent[0]);

	for (const auto& UsingNameSpace : UsingNameSpaces)
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
		"\tpublic partial class %s%s\n"
		"\t{\n"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"%s"
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent[0],
	                               *ClassContent,
	                               InClass->GetBaseClass().IsEmpty()
		                               ? (InClass->IsReflectionClass() ? TEXT("") : TEXT(" : IGarbageCollectionHandle"))
		                               : *FString::Printf(TEXT(
			                               " : %s"
		                               ),
		                                                  *InClass->GetBaseClass()
		                               ),
	                               *SubscriptContent,
	                               !SubscriptContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *PropertyContent,
	                               !PropertyContent.IsEmpty() && !FunctionContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *FunctionContent,
	                               !GCHandleContent.IsEmpty() && !FunctionContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *GCHandleContent
	);

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(TEXT("/") + NameSpaceContent[0].Replace(TEXT("."), TEXT("/"))),
		FUnrealCSharpFunctionLibrary::GetBindingDirectory());

	auto FileBaseName = InClass->IsReflectionClass() ? ClassContent.RightChop(1) : ClassContent;

	const auto FileName = FPaths::Combine(DirectoryName, FileBaseName) + CSHARP_SUFFIX;

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FileName, Content);
}

void FBindingClassGenerator::GeneratorImplementation(const FBindingClass* InClass)
{
	FString UsingNameSpaceContent;

	auto NameSpaceContent = InClass->GetTypeInfo().GetNameSpace();

	auto ImplementationNameSpaceContent = InClass->GetImplementationNameSpace();

	TSet<FString> UsingNameSpaces = {TEXT("System.Runtime.CompilerServices")};

	UsingNameSpaces.Append(NameSpaceContent);

	auto ClassContent = InClass->GetClass();

	auto ClassImplementationContent = BINDING_COMBINE_CLASS_IMPLEMENTATION(ClassContent);

	FString FunctionContent;

	if (InClass->GetSubscript().IsSet())
	{
		for (auto Param : InClass->GetSubscript().GetParams())
		{
			UsingNameSpaces.Append(Param->GetNameSpace());
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern object %s(nint InObject, params object[] InValue);\n"
		),
		                                           *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
			                                           ClassContent, InClass->GetSubscript().GetGetImplementationName())
		);

		FunctionContent += FString::Printf(TEXT(
			"%s"
			"%s"
		),
		                                   FunctionContent.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                   *FunctionDeclaration
		);

		FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern void %s(nint InObject, params object[] InValue);\n"
		),
		                                      *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
			                                      ClassContent, InClass->GetSubscript().GetSetImplementationName())
		);

		FunctionContent += FString::Printf(TEXT(
			"%s"
			"%s"
		),
		                                   FunctionContent.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                   *FunctionDeclaration
		);
	}

	for (const auto& Property : InClass->GetProperties())
	{
		UsingNameSpaces.Append(Property.GetNameSpace());

		auto PropertyName = Property.GetPropertyName();

		auto PropertyType = Property.GetName();

		FString GetFunctionContent;

		FString SetFunctionContent;

		const auto bRead = (static_cast<int32>(Property.GetAccess()) &
				static_cast<int32>(EBindingPropertyAccess::OnlyRead))
			== static_cast<int32>(EBindingPropertyAccess::OnlyRead);

		const auto bWrite = (static_cast<int32>(Property.GetAccess()) &
				static_cast<int32>(EBindingPropertyAccess::OnlyWrite))
			== static_cast<int32>(EBindingPropertyAccess::OnlyWrite);

		if (bRead)
		{
			GetFunctionContent = FString::Printf(TEXT(
				"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
				"\t\tpublic static extern void %s(nint InObject, byte* ReturnBuffer);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName))
			);
		}

		if (bWrite)
		{
			SetFunctionContent = FString::Printf(TEXT(
				"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
				"\t\tpublic static extern void %s(nint InObject, byte* InBuffer);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
				                                     ClassContent, (BINDING_PROPERTY_SET + PropertyName))
			);
		}

		if (bRead || bWrite)
		{
			FunctionContent += FString::Printf(TEXT(
				"%s"
				"%s"
				"%s"
				"%s"
			),
			                                   FunctionContent.IsEmpty() ? TEXT("") : TEXT("\n"),
			                                   *GetFunctionContent,
			                                   bRead && bWrite ? TEXT("\n") : TEXT(""),
			                                   *SetFunctionContent
			);
		}
	}

	TArray<FString> OverrideFunctions;

	if (InClass->IsReflectionClass())
	{
		OverrideFunctions = FGeneratorCore::GetOverrideFunctions(NameSpaceContent[0], ClassContent);
	}

	for (const auto& Function : InClass->GetFunctions())
	{
		if (InClass->IsReflectionClass())
		{
			if (OverrideFunctions.Contains(Function.GetFunctionName()))
			{
				continue;
			}
		}

		auto bHasRef = false;

		for (auto Param : Function.GetParams())
		{
			UsingNameSpaces.Append(Param->GetNameSpace());

			bHasRef = bHasRef ? bHasRef : Param->IsRef();
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern void %s(%s InObject%s%s%s);\n"
		),
		                                           *BINDING_COMBINE_FUNCTION_IMPLEMENTATION(
			                                           ClassContent, Function.GetFunctionImplementationName()),
		                                           Function.IsConstructor() ? *ClassContent : TEXT("nint"),
		                                           !Function.GetParams().IsEmpty()
			                                           ? TEXT(", byte* InBuffer")
			                                           : TEXT(""),
		                                           bHasRef
			                                           ? TEXT(", byte* OutBuffer")
			                                           : TEXT(""),
		                                           Function.GetReturn() != nullptr
			                                           ? TEXT(", byte* ReturnBuffer")
			                                           : TEXT("")
		);

		FunctionContent += FString::Printf(TEXT(
			"%s"
			"%s"
		),
		                                   FunctionContent.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                   *FunctionDeclaration
		);
	}

	for (const auto& UsingNameSpace : UsingNameSpaces)
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
		"\tpublic static unsafe partial class %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *ImplementationNameSpaceContent,
	                               *ClassImplementationContent,
	                               *FunctionContent
	);

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(TEXT("/") + NameSpaceContent[0].Replace(TEXT("."), TEXT("/"))),
		FUnrealCSharpFunctionLibrary::GetBindingDirectory());

	auto FileBaseName = InClass->IsReflectionClass() ? ClassContent.RightChop(1) : ClassContent;

	const auto FileName = FPaths::Combine(DirectoryName,
	                                      BINDING_COMBINE_CLASS_IMPLEMENTATION(FileBaseName)) + CSHARP_SUFFIX;

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FileName, Content);
}
