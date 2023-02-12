#include "FEnumGenerator.h"
#include "FGeneratorCore.h"
#include "Engine/UserDefinedEnum.h"

void FEnumGenerator::Generator()
{
	for (TObjectIterator<UEnum> EnumIterator; EnumIterator; ++EnumIterator)
	{
		Generator(*EnumIterator);
	}
}

static bool GetUnderlyingTypeName(const FFieldClass* Class, FString& Name)
{
	static TMap<FFieldClass*, FString> Map
	{
		{ FInt8Property::StaticClass()   , TEXT("sbyte")  },
		{ FByteProperty::StaticClass()   , TEXT("byte")   },
		{ FInt16Property::StaticClass()  , TEXT("short")  },
		{ FUInt16Property::StaticClass() , TEXT("ushort") },
		{ FIntProperty::StaticClass()    , TEXT("int")    },
		{ FUInt32Property::StaticClass() , TEXT("uint")   },
		{ FInt64Property::StaticClass()  , TEXT("long")   },
		{ FUInt64Property::StaticClass() , TEXT("ulong")  },
	};

	if(Map.Contains(Class))
	{
		Name = Map[Class];
		
		return true;
	}

	return false;
}
void FEnumGenerator::Generator(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return;
	}

	auto UserDefinedEnum = Cast<UUserDefinedEnum>(InEnum);

	FString UsingNameSpaceContent;

	const auto NameSpaceContent = FGeneratorCore::GetClassNameSpace(InEnum);

	const auto PathNameAttributeContent = FGeneratorCore::GetPathNameAttribute(InEnum);

	const auto FullClassContent = FGeneratorCore::GetFullClass(InEnum);

	FString EnumeratorContent;

	auto ClassName = InEnum->GetName();

	TSet<FString> UsingNameSpaces{TEXT("Script.Common")};

	auto EnumFieldClass = GetEnumUnderlyingCache(InEnum);
	
	FString UnderlyingType;

	if(!GetUnderlyingTypeName(EnumFieldClass, UnderlyingType))
	{
		GetUnderlyingTypeName(FInt64Property::StaticClass(), UnderlyingType);
	}
	
	for (auto Index = 0; Index < InEnum->NumEnums(); ++Index)
	{
		auto EnumeratorString = InEnum->GetNameStringByIndex(Index);

		// Skip auto generation
		if(EnumeratorString.EndsWith(TEXT("_MAX")))
		{
			continue;
		}
		
		if (UserDefinedEnum != nullptr)
		{
			EnumeratorString = InEnum->GetDisplayNameTextByIndex(Index).ToString();
		}

		const auto EnumeratorValue = InEnum->GetValueByIndex(Index);
		
		EnumeratorContent += FString::Printf(TEXT(
			"\t\t%s = %lld%s\n"
		),
		                                     *FGeneratorCore::GetName(EnumeratorString),
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
	                                     *UnderlyingType,
	                                     *EnumeratorContent
	);

	auto ModuleName = FGeneratorCore::GetModuleName(InEnum);

	auto DirectoryName = FPaths::Combine(FGeneratorCore::GetBasePath(), ModuleName);

	const auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}

static TMap<const UEnum*, FFieldClass*> EnumSizeCache;

void FEnumGenerator::EmplaceEnumUnderlyingCache(const UEnum* Enum, FNumericProperty* Property)
{
	check(Enum && Property);
	
	if(EnumSizeCache.Contains(Enum))
	{
		return;
	}
	
	EnumSizeCache.Add(Enum, Property->GetClass());
}

FFieldClass* FEnumGenerator::GetEnumUnderlyingCache(const UEnum* Enum)
{
	if(EnumSizeCache.Contains(Enum))
	{
		return EnumSizeCache[Enum];
	}
	
	return nullptr;
}

void FEnumGenerator::ClearEnumUnderlyingCache()
{
	EnumSizeCache.Reset();
}
