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
	const auto& NameSpaceContent = InEnum.GetTypeInfo().GetNameSpace();

	auto ClassContent = InEnum.GetEnum();

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

	const auto Content = FString::Printf(TEXT(
		"namespace %s\n"
		"{\n"
		"\tpublic enum %s : %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                                     *NameSpaceContent[0],
	                                     *ClassContent,
	                                     *InEnum.GetUnderlyingType(),
	                                     *EnumeratorContent
	);

	auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGenerationPath(TEXT("/") + NameSpaceContent[0].Replace(TEXT("."), TEXT("/"))),
		FUnrealCSharpFunctionLibrary::GetBindingPath());

	const auto FileName = FPaths::Combine(DirectoryName, ClassContent) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
