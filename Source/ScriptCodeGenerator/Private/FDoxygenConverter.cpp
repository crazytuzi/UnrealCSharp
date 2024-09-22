#include "FDoxygenConverter.h"

static auto TagParam = FString(TEXT("param"));

static auto TagReturn = FString(TEXT("return"));

static auto TagBrief = FString(TEXT("brief"));

enum class ETokenKind
{
	TagParam,
	TagReturn,
	TagBrief,
	TagOther,
	Name,
	Whitespace,
	Trivial,
	Description,
	EndOfText
};

enum class EExpect
{
	None,
	Name,
	Description
};

struct FTokenData
{
	explicit FTokenData(const ETokenKind InTokenKind, const FTextRange& InTextRange):
		TokenKind(InTokenKind),
		TextRange(InTextRange)
	{
	}

	ETokenKind TokenKind;

	FTextRange TextRange;
};

struct FTagData
{
	explicit FTagData(const FStringView& InName):
		Name(InName)
	{
	}

	bool operator ==(const FStringView& InName) const
	{
		return Name == InName;
	}

	bool operator !=(const FStringView& InName) const
	{
		return Name != InName;
	}

	FStringView Name;

	FStringView ParamName;

	TArray<FStringView> Descriptions;
};

class FTextReader
{
public:
	explicit FTextReader(const FStringView& InText):
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

			OutTextReader.EatWhile([](const int InChar)
			{
				return InChar > 0 && InChar < 128 && FChar::IsAlpha(InChar);
			});

			const auto TokenKind = [](const FStringView& InTag)
			{
				if (InTag == TagParam)
				{
					return ETokenKind::TagParam;
				}

				if (InTag == TagReturn)
				{
					return ETokenKind::TagReturn;
				}

				if (InTag == TagBrief)
				{
					return ETokenKind::TagBrief;
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

			OutTextReader.EatWhile([](const int InChar)
			{
				return InChar != '@' && InChar != '\\';
			});

			return ETokenKind::Trivial;
		}

	case '*':
		{
			OutTextReader.Bump();

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
			OutTextReader.EatWhile([](const int InChar)
			{
				return InChar > 0 && InChar < 128 && (FChar::IsAlnum(InChar) || InChar == '_');
			});

			OutExpect = EExpect::Description;

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

	case EExpect::None:
		{
			OutTextReader.NextChar();

			OutExpect = EExpect::None;

			break;
		}
	}

	return ETokenKind::Trivial;
}

TArray<FTokenData> Tokenize(const FStringView& InText)
{
	TArray<FTokenData> TokenData;

	FTextReader TextReader(InText);

	EExpect Expect{};

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

FDoxygenConverter::FDoxygenConverter(const FString& InIndent):
	Indent(InIndent)
{
}

FString FDoxygenConverter::operator()(const FStringView& InText) const
{
	static auto TagDefault = FString(TEXT("default"));

	auto BriefIndex = 0;

	auto ReturnIndex = 0;

	TArray<FTagData> TagData;

	TagData.Emplace(TagDefault);

	auto TokenData = Tokenize(InText);

	for (auto& Token : TokenData)
	{
		switch (Token.TokenKind)
		{
		case ETokenKind::TagParam:
			{
				TagData.Emplace(Slice(InText, Token.TextRange));

				break;
			}

		case ETokenKind::TagReturn:
			{
				ReturnIndex = TagData.Num();

				TagData.Emplace(Slice(InText, Token.TextRange));

				break;
			}

		case ETokenKind::TagBrief:
			{
				BriefIndex = TagData.Num();

				TagData.Emplace(Slice(InText, Token.TextRange));

				break;
			}

		case ETokenKind::TagOther:
			{
				TagData.Emplace(Slice(InText, Token.TextRange));

				break;
			}

		case ETokenKind::Name:
			{
				TagData.Last().ParamName = Slice(InText, Token.TextRange);

				break;
			}

		case ETokenKind::Description:
			{
				TagData.Last().Descriptions.Emplace(Slice(InText, Token.TextRange));

				break;
			}

		default:
			{
				break;
			}
		}
	}

	TStringBuilder<1024> StringBuilder;

	if (BriefIndex != 0)
	{
		StringBuilder.Append(Indent).Append(TEXT("/// <summary>\n"));

		for (const auto& Description : TagData[BriefIndex].Descriptions)
		{
			StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
		}

		StringBuilder.Append(Indent).Append(TEXT("/// </summary>\n"));
	}

	for (auto& Tag : TagData)
	{
		if (Tag == TagParam)
		{
			StringBuilder.Append(Indent).Append(TEXT("/// <param name=\"")).Append(Tag.ParamName).Append(TEXT("\">\n"));

			for (const auto& Description : Tag.Descriptions)
			{
				StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
			}

			StringBuilder.Append(Indent).Append(TEXT("/// </param>\n"));
		}
		else if (Tag != TagBrief && Tag != TagReturn && Tag != TagDefault)
		{
			StringBuilder.Append(Indent).Append(TEXT("/// <")).Append(Tag.Name).Append(TEXT(">\n"));

			for (const auto& Description : Tag.Descriptions)
			{
				StringBuilder.Append(Indent).Append(TEXT("/// ")).Append(Description).Append(TEXT("\n"));
			}

			StringBuilder.Append(Indent).Append(TEXT("/// </")).Append(Tag.Name).Append(TEXT(">\n"));
		}
	}

	if (ReturnIndex != 0)
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
