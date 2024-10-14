#include "FEnumGenerator.h"
#include "FGeneratorCore.h"
#include "Engine/UserDefinedEnum.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Dynamic/FDynamicEnumGenerator.h"

TMap<const UEnum*, EEnumUnderlyingType> FEnumGenerator::EnumUnderlyingType;

void FEnumGenerator::Generator()
{
	for (TObjectIterator<UEnum> EnumIterator; EnumIterator; ++EnumIterator)
	{
		Generator(*EnumIterator);
	}

	GeneratorCollisionChannel();
}

void FEnumGenerator::Generator(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return;
	}

	if (FDynamicEnumGenerator::IsDynamicEnum(InEnum))
	{
		return;
	}

	if (!FGeneratorCore::IsSupported(InEnum))
	{
		return;
	}

	if (FUnrealCSharpFunctionLibrary::IsSpecialEnum(InEnum))
	{
		return;
	}

	const auto UserDefinedEnum = Cast<UUserDefinedEnum>(InEnum);

	FString UsingNameSpaceContent;

	const auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InEnum);

	const auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InEnum);

	const auto FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InEnum);

	FString EnumeratorContent;

	auto ClassName = InEnum->GetName();

	TSet<FString> UsingNameSpaces{COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)};

	for (auto Index = 0; Index < InEnum->NumEnums(); ++Index)
	{
		const auto EnumeratorValue = InEnum->GetValueByIndex(Index);

		if (EnumeratorValue == InEnum->GetMaxEnumValue())
		{
			break;
		}

		auto EnumeratorString = UserDefinedEnum != nullptr
			                        ? UserDefinedEnum->GetDisplayNameTextByIndex(Index).ToString()
			                        : InEnum->GetNameStringByIndex(Index);

		EnumeratorContent += FString::Printf(TEXT(
			"\t\t%s = %lld%s\n"
		),
		                                     *FUnrealCSharpFunctionLibrary::Encode(
			                                     EnumeratorString, InEnum->IsNative()),
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
		"\tpublic enum %s : %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                                     *UsingNameSpaceContent,
	                                     *NameSpaceContent,
	                                     *PathNameAttributeContent,
	                                     *FullClassContent,
	                                     *GetEnumUnderlyingTypeName(InEnum),
	                                     *EnumeratorContent
	);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FGeneratorCore::GetFileName(InEnum), Content);
}

void FEnumGenerator::AddEnumUnderlyingType(const UEnum* InEnum, const FNumericProperty* InNumericProperty)
{
	if (InEnum == nullptr || InNumericProperty == nullptr)
	{
		return;
	}

	if (EnumUnderlyingType.Contains(InEnum))
	{
		return;
	}

	auto UnderlyingType = EEnumUnderlyingType::None;

	if (CastField<FInt8Property>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::Int8;
	}
	else if (CastField<FByteProperty>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::UInt8;
	}
	else if (CastField<FInt16Property>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::Int16;
	}
	else if (CastField<FUInt16Property>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::UInt16;
	}
	else if (CastField<FIntProperty>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::Int;
	}
	else if (CastField<FUInt32Property>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::UInt32;
	}
	else if (CastField<FInt64Property>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::Int64;
	}
	else if (CastField<FUInt64Property>(InNumericProperty))
	{
		UnderlyingType = EEnumUnderlyingType::UInt64;
	}

	EnumUnderlyingType.Emplace(InEnum, UnderlyingType);
}

void FEnumGenerator::GeneratorCollisionChannel()
{
	const auto InEnum = LoadObject<UEnum>(UCollisionProfile::StaticClass()->GetPackage(), TEXT("ECollisionChannel"));

	if (InEnum == nullptr)
	{
		return;
	}

	FString UsingNameSpaceContent;

	const auto NameSpaceContent = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InEnum);

	const auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InEnum);

	const auto FullClassContent = FUnrealCSharpFunctionLibrary::GetFullClass(InEnum);

	FString EnumeratorContent;

	auto ClassName = InEnum->GetName();

	TSet<FString> UsingNameSpaces{COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)};

	const auto CollisionProfile = UCollisionProfile::Get();

	for (auto Index = 0; Index < InEnum->NumEnums(); ++Index)
	{
		const auto EnumeratorValue = InEnum->GetValueByIndex(Index);

		if (EnumeratorValue == InEnum->GetMaxEnumValue())
		{
			break;
		}

		EnumeratorContent += FString::Printf(TEXT(
			"\t\t%s = %lld%s\n"
		),
		                                     *CollisionProfile->ReturnChannelNameFromContainerIndex(Index).ToString(),
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
		"\tpublic enum %s : %s\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                                     *UsingNameSpaceContent,
	                                     *NameSpaceContent,
	                                     *PathNameAttributeContent,
	                                     *FullClassContent,
	                                     *GetEnumUnderlyingTypeName(InEnum),
	                                     *EnumeratorContent
	);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FGeneratorCore::GetFileName(InEnum), Content);
}

FString FEnumGenerator::GetEnumUnderlyingTypeName(const UEnum* InEnum)
{
	static TMap<EEnumUnderlyingType, FString> EnumUnderlyingTypeName
	{
		{EEnumUnderlyingType::None, TEXT("byte")},
		{EEnumUnderlyingType::Int8, TEXT("sbyte")},
		{EEnumUnderlyingType::UInt8, TEXT("byte")},
		{EEnumUnderlyingType::Int16, TEXT("short")},
		{EEnumUnderlyingType::UInt16, TEXT("ushort")},
		{EEnumUnderlyingType::Int, TEXT("int")},
		{EEnumUnderlyingType::UInt32, TEXT("uint")},
		{EEnumUnderlyingType::Int64, TEXT("long")},
		{EEnumUnderlyingType::UInt64, TEXT("ulong")}
	};

	if (const auto FoundEnumUnderlyingType = EnumUnderlyingType.Find(InEnum))
	{
		return EnumUnderlyingTypeName[*FoundEnumUnderlyingType];
	}

	return InEnum->IsA(UUserDefinedEnum::StaticClass()) ? TEXT("byte") : TEXT("long");
}
