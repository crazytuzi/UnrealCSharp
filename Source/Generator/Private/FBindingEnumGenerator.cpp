#include "FBindingEnumGenerator.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

void FBindingEnumGenerator::Generator()
{
	for (const auto& Enum : FBindingEnum::GetEnums())
	{
		Generator(Enum.Value);
	}
}

void FBindingEnumGenerator::Generator(const FBindingEnum& InEnum)
{
	TSet<FString> UsingNameSpaces{TEXT("System"), TEXT("Script.Common")};

	FString UsingNameSpaceContent;

	const auto& NameSpaceContent = InEnum.GetTypeInfo().GetNameSpace();

	auto ClassContent = InEnum.GetEnum();

	const auto FullClassContent = InEnum.GetFullEnum();

	FString EnumeratorContent;

	TArray<FString> Keys;

	InEnum.GetEnumerators().GetKeys(Keys);

	for (auto Index = 0; Index < Keys.Num(); ++Index)
	{
		const auto EnumeratorValue = InEnum.GetEnumerators()[Keys[Index]];

		auto EnumeratorString = Keys[Index];

		EnumeratorContent += FString::Printf(TEXT(
			"\t\t%s = %lld%s\n"
		),
		                                     *EnumeratorString,
		                                     EnumeratorValue,
		                                     Index == Keys.Num() - 1 ? TEXT("") : TEXT(","));
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
		"\tpublic enum %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                                     *UsingNameSpaceContent,
	                                     *NameSpaceContent[0],
	                                     *FullClassContent,
	                                     *EnumeratorContent
	);

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(TEXT("/") + NameSpaceContent[0].Replace(TEXT("."), TEXT("/"))),
		FUnrealCSharpFunctionLibrary::GetBindingPath());

	const auto FileName = FPaths::Combine(DirectoryName, ClassContent) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
