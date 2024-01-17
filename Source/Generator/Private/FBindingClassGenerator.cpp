#include "FBindingClassGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/BindingMacro.h"
#include "CoreMacro/PropertyMacro.h"

void FBindingClassGenerator::Generator()
{
	for (const auto& Class : FBindingClass::GetClasses())
	{
		Generator(Class.Value);
	}
}

void FBindingClassGenerator::Generator(const FBindingClass& InClass)
{
	GeneratorPartial(InClass);

	GeneratorImplementation(InClass);
}

void FBindingClassGenerator::GeneratorPartial(const FBindingClass& InClass)
{
	FString UsingNameSpaceContent;

	TSet<FString> UsingNameSpaces{InClass.GetImplementationNameSpace()};

	const auto& NameSpaceContent = InClass.GetTypeInfo().GetNameSpace();

	auto ClassContent = InClass.GetClass();

	FString SubscriptContent;

	FString PropertyContent;

	FString FunctionContent;

	FString GCHandleContent;

	bool bHasEqualTo = false;

	if (InClass.GetSubscript() != nullptr)
	{
		UsingNameSpaces.Append(InClass.GetSubscript()->GetReturn()->GetNameSpace());

		UsingNameSpaces.Append(InClass.GetSubscript()->GetParams()[0]->GetNameSpace());

		auto SubscriptGetContent = FString::Printf(TEXT(
			"\t\t\tget => %s%s.%s(%s, %s)%s;\n"
		),
		                                           InClass.GetSubscript()->GetReturn()->IsPrimitive()
			                                           ? *FString::Printf(TEXT(
				                                           "(%s)"
			                                           ),
			                                                              *InClass.GetSubscript()->GetReturn()->
			                                                              GetName()
			                                           )
			                                           : TEXT(""),
		                                           *BINDING_CLASS_IMPLEMENTATION(ClassContent),
		                                           *BINDING_COMBINE_FUNCTION(
			                                           ClassContent,
			                                           InClass.GetSubscript()->GetGetImplementationName()),
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                           *InClass.GetSubscript()->GetParamNames()[0],
		                                           !InClass.GetSubscript()->GetReturn()->IsPrimitive()
			                                           ? *FString::Printf(TEXT(
				                                           " as %s"
			                                           ),
			                                                              *InClass.GetSubscript()->GetReturn()->
			                                                              GetName())
			                                           : TEXT("")

		);

		auto SubscriptSetContent = FString::Printf(TEXT(
			"\t\t\tset => %s.%s(%s, %s, value);\n"
		),
		                                           *BINDING_CLASS_IMPLEMENTATION(ClassContent),
		                                           *BINDING_COMBINE_FUNCTION(
			                                           ClassContent,
			                                           InClass.GetSubscript()->GetSetImplementationName()),
		                                           *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                           *InClass.GetSubscript()->GetParamNames()[0]
		);

		SubscriptContent = FString::Printf(TEXT(
			"\t\tpublic %s %s[%s %s]\n"
			"\t\t{\n"
			"%s"
			"\n"
			"%s"
			"\t\t}\n"
		),
		                                   *InClass.GetSubscript()->GetReturn()->GetName(),
		                                   *InClass.GetSubscript()->GetFunctionName(),
		                                   *InClass.GetSubscript()->GetParams()[0]->GetName(),
		                                   *InClass.GetSubscript()->GetParamNames()[0],
		                                   *SubscriptGetContent,
		                                   *SubscriptSetContent
		);
	}

	for (const auto& Property : InClass.GetProperties())
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
				"\t\t\tget => %s%s.%s(%s)%s;\n"
			),
			                                     Property.IsPrimitive()
				                                     ? *FString::Printf(TEXT(
					                                     "(%s)"
				                                     ),
				                                                        *PropertyType
				                                     )
				                                     : TEXT(""),
			                                     *BINDING_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName)),
			                                     Property.IsStatic()
				                                     ? TEXT("nint.Zero")
				                                     : *PROPERTY_GARBAGE_COLLECTION_HANDLE,
			                                     !Property.IsPrimitive()
				                                     ? *FString::Printf(TEXT(
					                                     " as %s"
				                                     ),
				                                                        *PropertyType)
				                                     : TEXT("")
			);
		}

		if (bWrite)
		{
			PropertySetContent = FString::Printf(TEXT(
				"\t\t\tset => %s.%s(%s, value);\n"
			),
			                                     *BINDING_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION(
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

	for (const auto& Function : InClass.GetFunctions())
	{
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

		if (!Function.GetParamNames().IsEmpty())
		{
			FunctionParamName = Function.GetParamNames();

			for (auto Index = 0; Index < Params.Num(); ++Index)
			{
				if (Params[Index]->IsRef())
				{
					FunctionRefParamIndex.Add(Index);

					FunctionDeclarationBody += TEXT("ref ");
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
		                                           Function.GetFunctionInteract() == EFunctionInteract::None
			                                           ? TEXT("")
			                                           : Function.GetFunctionInteract() == EFunctionInteract::New
			                                           ? TEXT("new ")
			                                           : TEXT("override"),
		                                           (Function.IsConstructor() == true || Function.IsDestructor() == true)
			                                           ? TEXT("")
			                                           : *FunctionReturnType,
		                                           (Function.IsConstructor() == true || Function.IsDestructor() == true)
			                                           ? TEXT("")
			                                           : TEXT(" "),
		                                           *Function.GetFunctionName(),
		                                           *FunctionDeclarationBody
		);

		auto FunctionCallBody = FString::Printf(TEXT(
			"%s.%s(%s%s"
		),
		                                        *BINDING_CLASS_IMPLEMENTATION(ClassContent),
		                                        *BINDING_COMBINE_FUNCTION(
			                                        ClassContent, Function.GetFunctionImplementationName()),
		                                        Function.IsStatic() == true
			                                        ? TEXT("nint.Zero")
			                                        : Function.IsConstructor()
			                                        ? TEXT("this")
			                                        : *PROPERTY_GARBAGE_COLLECTION_HANDLE,
		                                        FunctionRefParamIndex.IsEmpty()
			                                        ? TEXT("")
			                                        : TEXT(", out var __OutValue")
		);

		for (auto Index = 0; Index < Params.Num(); ++Index)
		{
			FunctionCallBody += FString::Printf(TEXT(
				", %s"
			),
			                                    *FunctionParamName[Index]
			);
		}

		FunctionCallBody += TEXT(")");

		FString FunctionReturnParamBody;

		if (Function.GetReturn() != nullptr)
		{
			FunctionReturnParamBody = FString::Printf(TEXT(
				"return %s;"
			),
			                                          FunctionRefParamIndex.IsEmpty()
				                                          ? Function.GetReturn()->IsPrimitive()
					                                            ? *FString::Printf(TEXT(
						                                            "(%s)%s"
					                                            ),
						                                            *FunctionReturnType,
						                                            *FunctionCallBody)
					                                            : *FString::Printf(TEXT(
						                                            "%s as %s"
					                                            ),
						                                            *FunctionCallBody,
						                                            *FunctionReturnType)
				                                          : Function.GetReturn()->IsPrimitive()
				                                          ? *FString::Printf(TEXT(
					                                          "(%s)__ReturnValue"
				                                          ),
				                                                             *FunctionReturnType
				                                          )
				                                          : *FString::Printf(TEXT(
					                                          "__ReturnValue as %s"
				                                          ),
				                                                             *FunctionReturnType
				                                          ));
		}

		FString FunctionRefParamBody;

		for (auto Index = 0; Index < FunctionRefParamIndex.Num(); ++Index)
		{
			FunctionRefParamBody += FString::Printf(TEXT(
				"\n\t\t\t%s = %s__OutValue[%d]%s;\n"
			),
			                                        *FunctionParamName[FunctionRefParamIndex[Index]],
			                                        Params[FunctionRefParamIndex[Index]]->IsPrimitive()
				                                        ? *FString::Printf(TEXT(
					                                        "(%s)"
				                                        ),
				                                                           *Params[FunctionRefParamIndex[Index]]->
				                                                           GetName()
				                                        )
				                                        : TEXT(""),
			                                        Index,
			                                        !Params[FunctionRefParamIndex[Index]]->IsPrimitive()
				                                        ? *FString::Printf(TEXT(
					                                        " as %s"
				                                        ),
				                                                           *Params[FunctionRefParamIndex[Index]]->
				                                                           GetName())
				                                        : TEXT("")
			);
		}

		auto FunctionImplementationBody = FString::Printf(TEXT(
			"\t\t\t%s"
			"%s"
			"%s"
			"%s"
			"%s"
			"%s"
		),
		                                                  Function.GetReturn() != nullptr && !FunctionRefParamIndex.
		                                                  IsEmpty()
			                                                  ? TEXT("var __ReturnValue = ")
			                                                  : TEXT(""),
		                                                  Function.GetReturn() == nullptr || !FunctionRefParamIndex.
		                                                  IsEmpty()
			                                                  ? *FunctionCallBody
			                                                  : TEXT(""),
		                                                  Function.GetReturn() == nullptr || !FunctionRefParamIndex.
		                                                  IsEmpty()
			                                                  ? TEXT(";\n")
			                                                  : TEXT(""),
		                                                  *FunctionRefParamBody,
		                                                  !FunctionRefParamBody.IsEmpty() && !FunctionReturnParamBody.
		                                                  IsEmpty()
			                                                  ? TEXT("\n")
			                                                  : TEXT(""),
		                                                  FunctionReturnParamBody.IsEmpty()
			                                                  ? TEXT("")
			                                                  : *FString::Printf(TEXT(
				                                                  "%s%s\n"
			                                                  ),
				                                                  !FunctionRefParamIndex.IsEmpty()
					                                                  ? TEXT("\t\t\t")
					                                                  : TEXT(""),
				                                                  *FunctionReturnParamBody));

		if (Function.IsConstructor())
		{
			FunctionImplementationBody = FString::Printf(TEXT(
				"\t\t\tif (GetType() == typeof(%s))\n"
				"\t\t\t{\n"
				"\t%s"
				"\t\t\t}\n"
			),
			                                             *ClassContent,
			                                             *FunctionImplementationBody
			);
		}

		FunctionContent += FString::Printf(TEXT(
			"%s"
			"\t\t%s\n"
			"\t\t{\n"
			"%s"
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

	if (!InClass.IsReflection() && InClass.GetBase().IsEmpty())
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
	                               InClass.GetBase().IsEmpty()
		                               ? (InClass.IsReflection() ? TEXT("") : TEXT(" : IGarbageCollectionHandle"))
		                               : *FString::Printf(TEXT(
			                               " : %s"
		                               ),
		                                                  *InClass.GetBase()
		                               ),
	                               *SubscriptContent,
	                               !SubscriptContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *PropertyContent,
	                               !PropertyContent.IsEmpty() && !FunctionContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *FunctionContent,
	                               !FunctionContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *GCHandleContent
	);

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(TEXT("/") + NameSpaceContent[0].Replace(TEXT("."), TEXT("/"))),
		FUnrealCSharpFunctionLibrary::GetBindingPath());

	const auto FileName = FPaths::Combine(DirectoryName, ClassContent) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

void FBindingClassGenerator::GeneratorImplementation(const FBindingClass& InClass)
{
	FString UsingNameSpaceContent;

	auto NameSpaceContent = InClass.GetTypeInfo().GetNameSpace();

	auto ImplementationNameSpaceContent = InClass.GetImplementationNameSpace();

	TSet<FString> UsingNameSpaces = {TEXT("System.Runtime.CompilerServices")};

	UsingNameSpaces.Append(NameSpaceContent);

	auto ClassContent = InClass.GetClass();

	auto ClassImplementationContent = BINDING_CLASS_IMPLEMENTATION(ClassContent);

	FString FunctionContent;

	if (InClass.GetSubscript() != nullptr)
	{
		for (auto Param : InClass.GetSubscript()->GetParams())
		{
			UsingNameSpaces.Append(Param->GetNameSpace());
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern object %s(nint InObject, params object[] InValue);\n"
		),
		                                           *BINDING_COMBINE_FUNCTION(
			                                           ClassContent, InClass.GetSubscript()->GetGetImplementationName())
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
		                                      *BINDING_COMBINE_FUNCTION(
			                                      ClassContent, InClass.GetSubscript()->GetSetImplementationName())
		);

		FunctionContent += FString::Printf(TEXT(
			"%s"
			"%s"
		),
		                                   FunctionContent.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                   *FunctionDeclaration
		);
	}

	for (const auto& Property : InClass.GetProperties())
	{
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
				"\t\tpublic static extern object %s(nint InObject);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName))
			);
		}

		if (bWrite)
		{
			SetFunctionContent = FString::Printf(TEXT(
				"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
				"\t\tpublic static extern void %s(nint InObject, object InValue);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION(
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

	for (const auto& Function : InClass.GetFunctions())
	{
		auto bHasRef = false;

		for (auto Param : Function.GetParams())
		{
			UsingNameSpaces.Append(Param->GetNameSpace());

			bHasRef = bHasRef ? bHasRef : Param->IsRef();
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern %s %s(%s InObject%s%s);\n"
		),
		                                           Function.GetReturn() != nullptr ? TEXT("object") : TEXT("void"),
		                                           *BINDING_COMBINE_FUNCTION(
			                                           ClassContent, Function.GetFunctionImplementationName()),
		                                           Function.IsConstructor() ? *ClassContent : TEXT("nint"),
		                                           bHasRef ? TEXT(", out object[] OutValue") : TEXT(""),
		                                           !Function.GetParams().IsEmpty()
			                                           ? TEXT(", params object[] InValue")
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
		"\tpublic static partial class %s\n"
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
		FUnrealCSharpFunctionLibrary::GetBindingPath());

	const auto FileName = FPaths::Combine(DirectoryName, ClassImplementationContent) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
