#include "FBindingGenerator.h"
#include "FGeneratorCore.h"
#include "Binding/FBindingClass.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/BindingMacro.h"

void FBindingGenerator::Generator()
{
	for (const auto& Class : FBindingClass::GetClasses())
	{
		Generator(Class.Value);
	}
}

void FBindingGenerator::Generator(const FBindingClass& InClass)
{
	GeneratorPartial(InClass);

	GeneratorImplementation(InClass);
}

void FBindingGenerator::GeneratorPartial(const FBindingClass& InClass)
{
	FString UsingNameSpaceContent;

	TSet<FString> UsingNameSpaces{InClass.GetImplementationNameSpace()};

	auto NameSpaceContent = InClass.GetTypeInfo().TypeInfo->GetNameSpace();

	auto FullClassContent = InClass.GetTypeInfo().TypeInfo->GetName();

	auto ClassContent = BINDING_REMOVE_PREFIX_CLASS(FullClassContent);

	FString PropertyContent;

	for (const auto& Property : InClass.GetProperties())
	{
		UsingNameSpaces.Append(Property.TypeInfo->GetNameSpace());

		auto PropertyName = Property.Name;

		auto PropertyType = Property.TypeInfo->GetName();

		FString PropertyGetContent;

		FString PropertySetContent;

		const auto bRead = (static_cast<int32>(Property.Access) &
				static_cast<int32>(EBindingPropertyAccess::OnlyRead))
			== static_cast<int32>(EBindingPropertyAccess::OnlyRead);

		const auto bWrite = (static_cast<int32>(Property.Access) &
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
			                                   bRead ? TEXT("\n") : TEXT(""),
			                                   *PropertySetContent
			);
		}
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
		"\tpublic partial class %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                               *UsingNameSpaceContent,
	                               *NameSpaceContent[0],
	                               *FullClassContent,
	                               *PropertyContent
	);

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(TEXT("/") + NameSpaceContent[0].Replace(TEXT("."), TEXT("/"))),
		FUnrealCSharpFunctionLibrary::GetBindingPath());

	const auto FileName = FPaths::Combine(DirectoryName, ClassContent) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

void FBindingGenerator::GeneratorImplementation(const FBindingClass& InClass)
{
	FString UsingNameSpaceContent;

	auto NameSpaceContent = InClass.GetTypeInfo().TypeInfo->GetNameSpace();

	auto ImplementationNameSpaceContent = InClass.GetImplementationNameSpace();

	TSet<FString> UsingNameSpaces = {TEXT("System"), TEXT("System.Runtime.CompilerServices")};

	UsingNameSpaces.Append(NameSpaceContent);

	auto FullClassContent = InClass.GetTypeInfo().TypeInfo->GetName();

	auto ClassContent = BINDING_REMOVE_PREFIX_CLASS(FullClassContent);

	auto ClassImplementationContent = BINDING_CLASS_IMPLEMENTATION(ClassContent);

	FString FunctionContent;

	for (const auto& Property : InClass.GetProperties())
	{
		auto PropertyName = Property.Name;

		auto PropertyType = Property.TypeInfo->GetName();

		FString GetFunctionContent;

		FString SetFunctionContent;

		const auto bRead = (static_cast<int32>(Property.Access) &
				static_cast<int32>(EBindingPropertyAccess::OnlyRead))
			== static_cast<int32>(EBindingPropertyAccess::OnlyRead);

		const auto bWrite = (static_cast<int32>(Property.Access) &
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
