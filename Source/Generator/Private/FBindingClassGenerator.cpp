#include "FBindingClassGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/BindingMacro.h"
#include "UEVersion.h"

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

	FString GCHandleContent;

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
				"\t\t\t\t%s.%s(%s, out var value);\n\n"
				"\t\t\t\treturn (%s)value;\n"
				"\t\t\t}\n"
			),
			                                     *BINDING_CLASS_IMPLEMENTATION(ClassContent),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName)),
			                                     Property.IsStatic() ? TEXT("IntPtr.Zero") : TEXT("GetHandle()"),
			                                     *PropertyType
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
			                                     Property.IsStatic() ? TEXT("IntPtr.Zero") : TEXT("GetHandle()")
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

		TArray<int32> FunctionOutParamIndex;

		TArray<FString> FunctionParamName;

#if UE_ARRAY_IS_EMPTY
		if (!Function.GetParamNames().IsEmpty())
#else
		if (Function.GetParamNames().Num() > 0)
#endif
		{
			FunctionParamName = Function.GetParamNames();

			for (auto Index = 0; Index < Params.Num(); ++Index)
			{
				if (Params[Index]->IsRef())
				{
					FunctionOutParamIndex.Add(Index);

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
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"%s%s%s%s%s%s%s(%s)"
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
		                                           *FunctionDeclarationBody
		);

		auto FunctionCallBody = FString::Printf(TEXT(
			"\t\t\t%s.%s(%s, out var __ReturnValue, out var __OutValue"
		),
		                                        *BINDING_CLASS_IMPLEMENTATION(ClassContent),
		                                        *BINDING_COMBINE_FUNCTION(
			                                        ClassContent, Function.GetFunctionImplementationName()),
		                                        Function.IsStatic() == true
			                                        ? TEXT("IntPtr.Zero")
			                                        : (Function.IsConstructor() ? TEXT("this") : TEXT("GetHandle()"))
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
				"\n\t\t\t%s = (%s)__OutValue[%d];\n"
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

		if (Function.IsConstructor())
		{
			FunctionImplementationBody = FString::Printf(TEXT(
				"\t\t\tif (GetType() == typeof(%s))\n"
				"\t\t\t{\n"
				"\t%s"
				"\t\t\t}\n"
			),
			                                             *FullClassContent,
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

	if (!InClass.IsReflection() && InClass.GetBase().IsEmpty())
	{
		GCHandleContent = TEXT(
			"\t\tpublic unsafe void SetHandle(void* InHandle)\n"
			"\t\t{\n"
			"\t\t\tGCHandle = new IntPtr(InHandle);\n"
			"\t\t}\n"
			"\n"
			"\t\tpublic IntPtr GetHandle()\n"
			"\t\t{\n"
			"\t\t\treturn GCHandle;\n"
			"\t\t}\n"
			"\n"
			"\t\tprivate IntPtr GCHandle;\n");

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
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent[0],
	                               *FullClassContent,
	                               InClass.GetBase().IsEmpty()
		                               ? (InClass.IsReflection() ? TEXT("") : TEXT(" : IGCHandle"))
		                               : *FString::Printf(TEXT(
			                               " : %s"
		                               ),
		                                                  *InClass.GetBase()
		                               ),
	                               *PropertyContent,
	                               !PropertyContent.IsEmpty() && !FunctionContent.IsEmpty() ? TEXT("\n") : TEXT(""),
	                               *FunctionContent,
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
				"\t\tpublic static extern void %s(IntPtr InObject, out Object OutValue);\n"
			),
			                                     *BINDING_COMBINE_FUNCTION(
				                                     ClassContent, (BINDING_PROPERTY_GET + PropertyName))
			);
		}

		if (bWrite)
		{
			SetFunctionContent = FString::Printf(TEXT(
				"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
				"\t\tpublic static extern void %s(IntPtr InObject, Object InValue);\n"
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
		FString FunctionAccessSpecifiers = TEXT("public");

		for (auto Param : Function.GetParams())
		{
			UsingNameSpaces.Append(Param->GetNameSpace());
		}

		auto FunctionDeclaration = FString::Printf(TEXT(
			"\t\t[MethodImpl(MethodImplOptions.InternalCall)]\n"
			"\t\tpublic static extern void %s(%s InObject, out Object ReturnValue, out Object[] OutValue, params Object[] InValue);\n"
		),
		                                           *BINDING_COMBINE_FUNCTION(
			                                           ClassContent, Function.GetFunctionImplementationName()),
		                                           Function.IsConstructor() ? *FullClassContent : TEXT("IntPtr")
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
