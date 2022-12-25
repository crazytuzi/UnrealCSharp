#include "FEnumGenerator.h"
#include "FGeneratorCore.h"

void FEnumGenerator::Generator()
{
	for (TObjectIterator<UEnum> EnumIterator; EnumIterator; ++EnumIterator)
	{
		Generator(*EnumIterator);
	}
}

void FEnumGenerator::Generator(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return;
	}

	FString UsingNameSpaceContent;

	const auto NameSpaceContent = FGeneratorCore::GetClassNameSpace(InEnum);

	const auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InEnum);

	const auto FullClassContent = FGeneratorCore::GetFullClass(InEnum);

	FString EnumeratorContent;

	auto ClassName = InEnum->GetName();

	TSet<FString> UsingNameSpaces{TEXT("Script.Common")};

	for (auto Index = 0; Index < InEnum->NumEnums(); ++Index)
	{
		auto EnumeratorString = InEnum->GetNameStringByIndex(Index);

		const auto EnumeratorValue = InEnum->GetValueByIndex(Index);

		EnumeratorContent += FString::Printf(TEXT(
			"\t\t%s = %lld%s\n"
		),
		                                     *EnumeratorString,
		                                     EnumeratorValue, Index == InEnum->NumEnums() - 1 ? TEXT("") : TEXT(","));
	}

	for (auto UsingNameSpace : UsingNameSpaces)
	{
		UsingNameSpaceContent += FString::Printf(TEXT(
			"using %s;\n"
		),
		                                         *UsingNameSpace);
	}

	const auto Content = FString::Printf(TEXT(
		"%s\n"
		"namespace %s\n"
		"{\n"
		"\t[PathName(\"%s\")]\n"
		"\tpublic enum %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                                     *UsingNameSpaceContent,
	                                     *NameSpaceContent,
	                                     *PathNameAttributeContent,
	                                     *FullClassContent,
	                                     *EnumeratorContent
	);

	auto ModuleName = FGeneratorCore::GetModuleName(InEnum);

	auto DirectoryName = FPaths::Combine(FGeneratorCore::GetBasePath(), ModuleName);

	const auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
