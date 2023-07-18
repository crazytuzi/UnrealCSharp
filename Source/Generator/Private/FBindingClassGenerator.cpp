#include "FBindingClassGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/BindingMacro.h"

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

	TSet<FString> UsingNameSpaces{InClass.GetImplementationNameSpace(), TEXT("System")};

	const auto& NameSpaceContent = InClass.GetTypeInfo().GetNameSpace();

	auto ClassContent = InClass.GetClass();

	auto FullClassContent = InClass.GetFullClass();

	FString PropertyContent;

	FString FunctionContent;

	if (!InClass.IsReflection())
	{
		FunctionContent = FString::Printf(TEXT(
			"\t\tprotected %s(Type InValue)%s\n"
			"\t\t{\n"
			"\t\t}\n"
		),
		                                  *FullClassContent,
		                                  InClass.GetBase().IsEmpty()
			                                  ? TEXT("")
			                                  : *FString::Printf(TEXT(
				                                  " : base(typeof(%s))"
			                                  ),
			                                                     *FullClassContent
			                                  ));
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
				"\t\t\tget\n"
				"\t\t\t{\n"
				"\t\t\t\t%s.%s(this, out var value);\n\n"
				"\t\t\t\treturn (%s)value;\n"
				"\t\t\t}\n"
			),
			                                     *BINDING_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName)),
			                                     *PropertyType
			);
		}

		if (bWrite)
		{
			PropertySetContent = FString::Printf(TEXT(
				"\t\t\tset => %s.%s(this, value);\n"
			),
			                                     *BINDING_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_SET + PropertyName))
			);
		}

		if (bRead || bWrite)
		{
			PropertyContent += FString::Printf(TEXT(
				"%s"
				"\t\tpublic %s %s\n"
				"\t\t{\n"
				"%s"
				"%s"
				"%s"
				"\t\t}\n"
			),
			                                   PropertyContent.IsEmpty() ? TEXT("") : TEXT("\n"),
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
		}

		FString FunctionDeclarationBody;

		TArray<int32> FunctionOutParamIndex;

		TArray<FString> FunctionParamName;

		for (auto Index = 0; Index < Params.Num(); ++Index)
		{
			if (Params[Index]->IsOut())
			{
				FunctionOutParamIndex.Add(Index);

				FunctionDeclarationBody += TEXT("ref ");

				FunctionParamName.Add(FString::Printf(TEXT(
					"OutValue%d"
				),
				                                      FunctionOutParamIndex.Num() - 1
				));
			}
			else
			{
				FunctionParamName.Add(FString::Printf(TEXT(
					"InValue%d"
				),
				                                      Index - FunctionOutParamIndex.Num()
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

		FString Base;

		if (!InClass.IsReflection() && !InClass.GetBase().IsEmpty() && Function.IsConstructor())
		{
			Base = FString::Printf(TEXT(
				" : base(typeof(%s))"
			),
			                       *FullClassContent);
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"%s%s%s%s%s%s%s(%s)%s"
		),
		                                           Function.IsDestructor() == true
			                                           ? TEXT("")
			                                           : *FunctionAccessSpecifiers,
		                                           Function.IsDestructor() == true ? TEXT("") : TEXT(" "),
		                                           *FunctionStatic,
		                                           FunctionStatic.IsEmpty() == true ? TEXT("") : TEXT(" "),
		                                           (Function.IsConstructor() == true || Function.IsDestructor() == true)
			                                           ? TEXT("")
			                                           : *FunctionReturnType,
		                                           (Function.IsConstructor() == true || Function.IsDestructor() == true)
			                                           ? TEXT("")
			                                           : TEXT(" "),
		                                           *Function.GetFunctionName(),
		                                           *FunctionDeclarationBody,
		                                           *Base
		);

		auto FunctionCallBody = FString::Printf(TEXT(
			"\t\t\t%s.%s(%s, out var __ReturnValue, out var __OutValue"
		),
		                                        *BINDING_CLASS_IMPLEMENTATION(ClassContent),
		                                        *BINDING_COMBINE_FUNCTION(
			                                        ClassContent, Function.GetFunctionImplementationName()),
		                                        Function.IsStatic() == true ? TEXT("null") : TEXT("this")
		);

		for (auto Index = 0; Index < Params.Num(); ++Index)
		{
			FunctionCallBody += FString::Printf(TEXT(
				", %s"
			),
			                                    *FunctionParamName[Index]
			);
		}

		FunctionCallBody += TEXT(");\n");

		FString FunctionReturnParamBody;

		if (Function.GetReturn() != nullptr)
		{
			FunctionReturnParamBody = FString::Printf(TEXT(
				"\t\t\treturn (%s) __ReturnValue;\n"
			),
			                                          *FunctionReturnType
			);
		}

		FString FunctionOutParamBody;

		for (auto Index = 0; Index < FunctionOutParamIndex.Num(); ++Index)
		{
			FunctionOutParamBody += FString::Printf(TEXT(
				"\n\t\t\t%s = (%s)__OutValue.Value[%d];\n"
			),
			                                        *FunctionParamName[FunctionOutParamIndex[Index]],
			                                        *Params[FunctionOutParamIndex[Index]]->GetName(),
			                                        Index
			);
		}

		auto FunctionImplementationBody = FString::Printf(TEXT(
			"%s"
			"%s"
			"%s"
			"%s"
		),
		                                                  *FunctionCallBody,
		                                                  *FunctionOutParamBody,
		                                                  FunctionReturnParamBody.IsEmpty() ? TEXT("") : TEXT("\n"),
		                                                  *FunctionReturnParamBody
		);

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
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent[0],
	                               *FullClassContent,
	                               InClass.GetBase().IsEmpty()
		                               ? TEXT("")
		                               : *FString::Printf(TEXT(
			                               " : %s"
		                               ),
		                                                  *InClass.GetBase()
		                               ),
	                               *PropertyContent,
	                               !PropertyContent.IsEmpty() && !FunctionContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *FunctionContent
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

	TSet<FString> UsingNameSpaces = {TEXT("System"), TEXT("System.Runtime.CompilerServices")};

	UsingNameSpaces.Append(NameSpaceContent);

	auto ClassContent = InClass.GetClass();

	auto FullClassContent = InClass.GetFullClass();

	auto ClassImplementationContent = BINDING_CLASS_IMPLEMENTATION(ClassContent);

	FString FunctionContent;

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
				"\t\tpublic static extern void %s(%s InObject, out Object OutValue);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName)),
			                                     *FullClassContent
			);
		}

		if (bWrite)
		{
			SetFunctionContent = FString::Printf(TEXT(
				"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
				"\t\tpublic static extern void %s(%s InObject, Object InValue);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_SET + PropertyName)),
			                                     *FullClassContent
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
		FString FunctionAccessSpecifiers = TEXT("public");

		UsingNameSpaces.Add("Script.Common");

		for (auto Param : Function.GetParams())
		{
			UsingNameSpaces.Append(Param->GetNameSpace());
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern void %s(%s InObject, out Object ReturnValue, out ObjectList OutValue, params Object[] InValue);\n"
		),
		                                           *BINDING_COMBINE_FUNCTION(
			                                           ClassContent, Function.GetFunctionImplementationName()),
		                                           *FullClassContent
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
