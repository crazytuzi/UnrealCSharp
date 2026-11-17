#include "FDoxygenConverter.h"

static auto TagParam = FString(TEXT("param"));

static auto TagReturn = FString(TEXT("return"));

static auto TagReturns = FString(TEXT("returns"));

static auto TagBrief = FString(TEXT("brief"));

static auto TagCode = FString(TEXT("code"));

static auto TagEndCode = FString(TEXT("endcode"));

enum class ETokenKind
{
	TagParam,
	TagReturn,
	TagBrief,
	TagCode,
	TagEndCode,
	TagOther,
	Name,
	Whitespace,
	Trivial,
	Description,
	EndOfText
};

enum class EExpect
{
	Name,
	Description
};

enum class ETagKind
{
	Default,
	Param,
	Return,
	Brief,
	Code,
	Other
};

struct FTokenData
{
	explicit FTokenData(const ETokenKind InTokenKind, const FTextRange& InTextRange) :
		TokenKind(InTokenKind),
		TextRange(InTextRange)
	{
	}

	ETokenKind TokenKind;

	FTextRange TextRange;
};

struct FTagData
{
	explicit FTagData(const FStringView& InName, const ETagKind InKind) :
		Name(InName),
		Kind(InKind)
	{
	}

	FStringView Name;

	FStringView ParamName;

	TArray<FStringView> Descriptions;

	ETagKind Kind;
};

class FTextReader
{
public:
	explicit FTextReader(const FStringView& InText) :
		Text(InText),
		bHasSaveText(false),
		BeginIndex(0),
		EndIndex(0),
		bIsEof(false),
		CurrentIndex(0)
	{
	}

	void NextChar()
	{
		if (CurrentIndex + 1 < Text.Len())
		{
			++CurrentIndex;
		}
		else
		{
			++CurrentIndex;

			if (CurrentIndex >= Text.Len())
			{
				bIsEof = true;
			}
		}
	}

	void Bump()
	{
		Save();

		NextChar();
	}

	void Save()
	{
		if (!bHasSaveText)
		{
			bHasSaveText = true;

			BeginIndex = CurrentIndex;
		}

		EndIndex = CurrentIndex;
	}

	int GetCurrentChar() const
	{
		return !bIsEof && CurrentIndex < Text.Len() ? Text[CurrentIndex] : INDEX_NONE;
	}

	FTextRange GetTokenRange() const
	{
		return FTextRange(BeginIndex, EndIndex + 1);
	}

	FStringView GetSaveText() const
	{
		return Text.SubStr(BeginIndex, bHasSaveText ? EndIndex - BeginIndex + 1 : 0);
	}

	void ResetBuffer()
	{
		bHasSaveText = false;

		BeginIndex = 0;

		EndIndex = 0;
	}

	int32 EatWhile(const TFunction<bool(const int)>& InFunction)
	{
		auto Count = 0;

		while (!IsEof() && InFunction(GetCurrentChar()))
		{
			Bump();

			Count++;
		}

		return Count;
	}

	bool IsEof() const
	{
		return bIsEof;
	}

private:
	FStringView Text;

	bool bHasSaveText;

	int32 BeginIndex;

	int32 EndIndex;

	bool bIsEof;

	int32 CurrentIndex;
};

ETokenKind Lex(FTextReader& OutTextReader, EExpect& OutExpect)
{
	OutTextReader.ResetBuffer();

	switch (OutTextReader.GetCurrentChar())
	{
	case ' ':

	case '\t':

	case '\f':

	case '\v':

	case '\r':

	case '\n':
		{
			OutTextReader.EatWhile([](const int InChar)
			{
				return InChar == ' ' ||
					InChar == '\t' ||
					InChar == '\f' ||
					InChar == '\v' ||
					InChar == '\r' ||
					InChar == '\n';
			});

			return ETokenKind::Whitespace;
		}

	case '@':

	case '\\':
		{
			OutTextReader.NextChar();

			if (OutTextReader.EatWhile([](const int InChar)
			{
				return InChar > 0 && InChar < 128 && FChar::IsAlpha(InChar);
			}) == 0)
			{
				OutTextReader.Save();

				return ETokenKind::Trivial;
			}

			const auto TokenKind = [](const FStringView& InTag)
			{
				if (InTag == TagParam)
				{
					return ETokenKind::TagParam;
				}

				if (InTag == TagReturn || InTag == TagReturns)
				{
					return ETokenKind::TagReturn;
				}

				if (InTag == TagBrief)
				{
					return ETokenKind::TagBrief;
				}

				if (InTag == TagCode)
				{
					return ETokenKind::TagCode;
				}

				if (InTag == TagEndCode)
				{
					return ETokenKind::TagEndCode;
				}

				return ETokenKind::TagOther;
			}(OutTextReader.GetSaveText());

			if (TokenKind == ETokenKind::TagParam)
			{
				OutExpect = EExpect::Name;
			}
			else
			{
				OutExpect = EExpect::Description;
			}

			return TokenKind;
		}

	case '/':
		{
			OutTextReader.Bump();

			if (OutTextReader.GetCurrentChar() == '/' ||
				OutTextReader.GetCurrentChar() == '*' ||
				OutTextReader.GetCurrentChar() == '!')
			{
				while (OutTextReader.GetCurrentChar() == '/' ||
					OutTextReader.GetCurrentChar() == '*' ||
					OutTextReader.GetCurrentChar() == '!')
				{
					OutTextReader.Bump();
				}

				return ETokenKind::Trivial;
			}

			if (OutTextReader.GetCurrentChar() == INDEX_NONE ||
				OutTextReader.GetCurrentChar() == '\n' ||
				OutTextReader.GetCurrentChar() == '\r')
			{
				return ETokenKind::Trivial;
			}

			OutTextReader.EatWhile([](const int InChar)
			{
				return InChar != '\n' && InChar != '\r';
			});

			return ETokenKind::Description;
		}

	case '*':
		{
			OutTextReader.Bump();

			if (OutTextReader.GetCurrentChar() == '/')
			{
				OutTextReader.Bump();
			}

			return ETokenKind::Trivial;
		}

	case INDEX_NONE:
		return ETokenKind::EndOfText;

	default:
		{
			break;
		}
	}

	switch (OutExpect)
	{
	case EExpect::Name:
		{
			if (OutTextReader.GetCurrentChar() == ':')
			{
				OutTextReader.NextChar();
			}

			if (OutTextReader.GetCurrentChar() == '[')
			{
				while (!OutTextReader.IsEof() && OutTextReader.GetCurrentChar() != ']')
				{
					OutTextReader.NextChar();
				}

				if (!OutTextReader.IsEof())
				{
					OutTextReader.NextChar();
				}
			}

			while (!OutTextReader.IsEof() &&
				(OutTextReader.GetCurrentChar() == ' ' || OutTextReader.GetCurrentChar() == '\t'))
			{
				OutTextReader.NextChar();
			}

			OutExpect = EExpect::Description;

			if (OutTextReader.EatWhile([](const int InChar)
			{
				return InChar > 0 && InChar < 128 && (FChar::IsAlnum(InChar) || InChar == '_');
			}) == 0)
			{
				OutTextReader.Save();

				return ETokenKind::Trivial;
			}

			return ETokenKind::Name;
		}

	case EExpect::Description:
		{
			OutTextReader.EatWhile([](const int InChar)
			{
				return InChar != '\n' && InChar != '\r';
			});

			return ETokenKind::Description;
		}
	}

	return ETokenKind::Trivial;
}

TArray<FTokenData> Tokenize(const FStringView& InText)
{
	TArray<FTokenData> TokenData;

	FTextReader TextReader(InText);

	EExpect Expect = EExpect::Description;

	while (!TextReader.IsEof())
	{
		auto TokenKind = Lex(TextReader, Expect);

		if (TokenKind == ETokenKind::EndOfText)
		{
			break;
		}

		auto TokenRange = TextReader.GetTokenRange();

		if (TokenRange.IsEmpty())
		{
			break;
		}

		TokenData.Emplace(TokenKind, TokenRange);
	}

	return TokenData;
}

FStringView Slice(const FStringView& InText, const FTextRange& InTextRange)
{
	return InText.SubStr(InTextRange.BeginIndex, InTextRange.Len());
}

FDoxygenConverter::FDoxygenConverter(const FString& InIndent) :
	Indent(InIndent)
{
}

FString FDoxygenConverter::operator()(const FStringView& InText) const
{
	static auto TagDefault = FString(TEXT("default"));

	auto TextLen = InText.Len();

	while (TextLen > 0 &&
		(InText[TextLen - 1] == '\n' || InText[TextLen - 1] == '\r' ||
			InText[TextLen - 1] == ' ' || InText[TextLen - 1] == '\t'))
	{
		--TextLen;
	}

	if (TextLen >= 2 && InText[TextLen - 2] == '*' && InText[TextLen - 1] == '/')
	{
		TextLen -= 2;
	}

	auto Text = InText.SubStr(0, TextLen);

	int32 BriefIndex = INDEX_NONE;

	int32 ReturnIndex = INDEX_NONE;

	int32 CodeIndex = INDEX_NONE;

	int32 CodeParentIndex = 0;

	int32 DescriptionIndex = 0;

	TArray<FTagData> TagData;

	TagData.Emplace(TagDefault, ETagKind::Default);

	auto TokenData = Tokenize(Text);

	for (auto& Token : TokenData)
	{
		switch (Token.TokenKind)
		{
		case ETokenKind::TagParam:
			{
				TagData.Emplace(Slice(Text, Token.TextRange), ETagKind::Param);

				DescriptionIndex = TagData.Num() - 1;

				break;
			}

		case ETokenKind::TagReturn:
			{
				ReturnIndex = TagData.Num();

				TagData.Emplace(Slice(Text, Token.TextRange), ETagKind::Return);

				DescriptionIndex = TagData.Num() - 1;

				break;
			}

		case ETokenKind::TagBrief:
			{
				BriefIndex = TagData.Num();

				TagData.Emplace(Slice(Text, Token.TextRange), ETagKind::Brief);

				DescriptionIndex = TagData.Num() - 1;

				break;
			}

		case ETokenKind::TagCode:
			{
				if (CodeIndex == INDEX_NONE)
				{
					CodeParentIndex = DescriptionIndex;

					CodeIndex = TagData.Num();

					TagData.Emplace(Slice(Text, Token.TextRange), ETagKind::Code);

					DescriptionIndex = CodeIndex;
				}

				break;
			}

		case ETokenKind::TagEndCode:
			{
				if (CodeIndex != INDEX_NONE)
				{
					CodeIndex = INDEX_NONE;

					DescriptionIndex = CodeParentIndex;
				}

				break;
			}

		case ETokenKind::TagOther:
			{
				TagData.Emplace(Slice(Text, Token.TextRange), ETagKind::Other);

				DescriptionIndex = TagData.Num() - 1;

				break;
			}

		case ETokenKind::Name:
			{
				TagData[DescriptionIndex].ParamName = Slice(Text, Token.TextRange);

				break;
			}

		case ETokenKind::Description:
			{
				TagData[DescriptionIndex].Descriptions.Emplace(Slice(Text, Token.TextRange));

				break;
			}

		default:
			{
				break;
			}
		}
	}

	TStringBuilder<1024> StringBuilder;

	auto SummaryIndex = BriefIndex;

	if (SummaryIndex == INDEX_NONE && !TagData[0].Descriptions.IsEmpty())
	{
		SummaryIndex = 0;
	}

	if (SummaryIndex != INDEX_NONE)
	{
		StringBuilder.Append(Indent).Append(TEXT("/// <summary>\n"));

		for (const auto& Description : TagData[SummaryIndex].Descriptions)
		{
			StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
		}

		StringBuilder.Append(Indent).Append(TEXT("/// </summary>\n"));
	}

	for (auto& Tag : TagData)
	{
		if (Tag.Kind == ETagKind::Param)
		{
			if (Tag.ParamName.IsEmpty())
			{
				for (const auto& Description : Tag.Descriptions)
				{
					StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
				}
			}
			else
			{
				StringBuilder.Append(Indent).Append(TEXT("/// <param name=\""));

				StringBuilder.Append(Tag.ParamName).Append(TEXT("\">\n"));

				for (const auto& Description : Tag.Descriptions)
				{
					StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
				}

				StringBuilder.Append(Indent).Append(TEXT("/// </param>\n"));
			}
		}
		else if (Tag.Kind == ETagKind::Code)
		{
			StringBuilder.Append(Indent).Append(TEXT("/// <code>\n"));

			for (const auto& Description : Tag.Descriptions)
			{
				StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
			}

			StringBuilder.Append(Indent).Append(TEXT("/// </code>\n"));
		}
		else if (Tag.Kind == ETagKind::Other)
		{
			for (auto Index = 0; Index < Tag.Descriptions.Num(); ++Index)
			{
				StringBuilder.Append(Indent).Append(TEXT("/// "));

				if (Index == 0)
				{
					StringBuilder.Append(Tag.Name).Append(TEXT(": "));
				}

				StringBuilder.Append(Tag.Descriptions[Index]).Append(TEXT("\n"));
			}
		}
	}

	if (ReturnIndex != INDEX_NONE)
	{
		StringBuilder.Append(Indent).Append(TEXT("/// <returns>\n"));

		for (const auto& Description : TagData[ReturnIndex].Descriptions)
		{
			StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
		}

		StringBuilder.Append(Indent).Append(TEXT("/// </returns>\n"));
	}

	return StringBuilder.ToString();
}
