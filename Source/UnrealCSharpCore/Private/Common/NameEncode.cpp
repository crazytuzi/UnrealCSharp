#include "Common/NameEncode.h"

#define ESCAPE_SYMBOL_FIRST TEXT('_')
#define ESCAPE_SYMBOL_SECOND TEXT('h')
#define ESCAPE_SYMBOL TEXT("_h")
#define ESCAPE_SYMBOL_LEN 2
#define ESCAPE_END_SYMBOL TEXT('_')

#define ESCAPE_HEAD_NUMBER 0x01
#define ESCAPE_HEAD_NUMBER_SYMBOL TEXT("01")

#define ESCAPE_UNICODE_IDENT_LE TEXT('u')
#define ESCAPE_UNICODE_IDENT_BE TEXT('U')
#define ESCAPE_UNICODE_IDENT (IsLittleEndian() ? ESCAPE_UNICODE_IDENT_LE : ESCAPE_UNICODE_IDENT_BE)


static bool ShouldEscape(const int C)
{
	return C <= 0x7F && !(::isalnum(C) || C == '_');
}

static bool IsLittleEndian()
{
	static struct FV
	{
		FV()
		{
			unsigned short N = 1;

			Bool = static_cast<bool>(reinterpret_cast<unsigned char*>(&N)[0]);
		}

		bool Bool;
	} Local;

	return Local.Bool;
}

static const char* HexList = "0123456789ABCDEF";

static void ByteToHex(const uint8 Value, TCHAR* Out)
{
	Out[0] = HexList[Value / 16];

	Out[1] = HexList[Value % 16];
}

static uint8 HexToByte(const TCHAR Str)
{
	return Str >= 'A' ? Str - 'A' + 10 : Str - '0';
}

static uint8 HexToByte(const TCHAR* Str)
{
	return HexToByte(Str[0]) * 16 + HexToByte(Str[1]);
}

FString FNameEncode::Encode(const FString& InName, const bool bEncodeWideString)
{
	constexpr auto kNormal = 1;

	constexpr auto kEscapeChar = 2;

	constexpr auto kUnicodeString = 3;

	FString Ret;

	Ret.Reserve(InName.Len() + 4);

	const auto LastIndex = InName.Len() - 1;

	auto LastState = kNormal;

	for (auto i = 0; i < InName.Len(); ++i)
	{
		const auto C = InName[i];

		if (C == ESCAPE_HEAD_NUMBER)
		{
			// @TODO

			return {};
		}

		const auto bEscapeSymbol = C == ESCAPE_SYMBOL_FIRST && i != LastIndex && InName[i + 1] == ESCAPE_SYMBOL_SECOND;

		const auto bDigitHead = i == 0 && ::isdigit(C);

		if (bDigitHead)
		{
			Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);

			Ret.AppendChars(ESCAPE_HEAD_NUMBER_SYMBOL, 2);

			Ret.AppendChar(ESCAPE_END_SYMBOL);

			Ret.AppendChar(C);

			LastState = kEscapeChar;
		}
		else if (bEscapeSymbol || ShouldEscape(C))
		{
			Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);

			TCHAR Hex[2];

			ByteToHex(C, Hex);

			Ret.AppendChars(Hex, 2);

			// skip escape symbol
			if (bEscapeSymbol)
			{
				++i;
			}

			Ret.AppendChar(ESCAPE_END_SYMBOL);

			LastState = kEscapeChar;
		}
		else if (bEncodeWideString && C > 0x7F)
		{
			if (LastState != kUnicodeString)
			{
				Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);

				// add endian info
				Ret.AppendChar(ESCAPE_UNICODE_IDENT);
			}

			auto _C = static_cast<unsigned short>(C);

			const auto P = reinterpret_cast<unsigned char*>(&_C);

			TCHAR Hex[4];

			ByteToHex(P[0], Hex);

			ByteToHex(P[1], Hex + 2);

			Ret.AppendChars(Hex, 4);

			const auto bNext = bEncodeWideString && i != LastIndex && InName[i + 1] > 0x7F;

			if (bNext)
			{
				// next
			}
			else
			{
				Ret.AppendChar(ESCAPE_END_SYMBOL);
			}

			LastState = kUnicodeString;
		}
		else
		{
			// a-z A-Z 0-9 _
			Ret.AppendChar(C);

			LastState = kNormal;
		}
	}

	return Ret;
}

void FNameEncode::Encode(TArray<FString>& InNames)
{
	for (auto& Name : InNames)
	{
		Name = Encode(Name);
	}
}

FString FNameEncode::Decode(const FString& InName)
{
	constexpr auto kNormal = 1;

	constexpr auto kEscapeChar = 2;

	constexpr auto kUnicodeString = 3;

	FString Ret;

	Ret.Reserve(InName.Len());

	const auto LastIndex = InName.Len() - 1;

	auto State = kNormal;

	auto UnicodeStringCtx_LE = true;

	auto UnicodeStringCtx_Collected = false;

	unsigned char UnicodeStringCtx_CollectedByte{};

	for (auto i = 0; i < InName.Len(); ++i)
	{
		const auto C = InName[i];

		switch (State)
		{
		case kNormal:
			{
				const auto bEscape =
					C == ESCAPE_SYMBOL_FIRST &&
					i < LastIndex - 1 &&
					InName[i + 1] == ESCAPE_SYMBOL_SECOND;

				if (bEscape)
				{
					State = kEscapeChar;

					// skip escape symbol
					i += 1;

					break;
				}

				Ret.AppendChar(C);
			}
			break;
		case kEscapeChar:
			{
				if (C == ESCAPE_UNICODE_IDENT_LE || C == ESCAPE_UNICODE_IDENT_BE)
				{
					UnicodeStringCtx_LE = C == ESCAPE_UNICODE_IDENT_LE;

					State = kUnicodeString;

					break;
				}

				const auto Hex = HexToByte(GetData(InName) + i);

				if (i == 2 /* hex start offset */ && Hex == ESCAPE_HEAD_NUMBER)
				{
					// do nothing.
				}
				else if (Hex == '_')
				{
					Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
				}
				else
				{
					Ret.AppendChar(Hex);
				}

				//skip next char and end symbol
				i += 2;

				State = kNormal;
			}
			break;
		case kUnicodeString:
			{
				if (i + 1 >= InName.Len())
				{
					// @TODO

					return {};
				}

				const unsigned char Byte = HexToByte(GetData(InName) + i);

				if (!UnicodeStringCtx_Collected)
				{
					UnicodeStringCtx_CollectedByte = Byte;

					UnicodeStringCtx_Collected = true;

					++i;

					break;
				}

				UnicodeStringCtx_Collected = false;

				short WideChar;

				unsigned char* P = reinterpret_cast<unsigned char*>(&WideChar);

				P[0] = UnicodeStringCtx_CollectedByte;

				P[1] = Byte;

				// endian mismatch
				if (IsLittleEndian() && !UnicodeStringCtx_LE)
				{
					const auto Temp = P[0];

					P[0] = P[1];

					P[1] = Temp;
				}

				++i;

				// peek next
				if (i != LastIndex && InName[i + 1] != ESCAPE_END_SYMBOL)
				{
					// next
					Ret.AppendChar(WideChar);
				}
				else
				{
					// skip end symbol
					++i;

					Ret.AppendChar(WideChar);

					State = kNormal;
				}
			}
			break;
		default: ;
		}
	}

	return Ret;
}

void FNameEncode::Decode(TArray<FString>& InNames)
{
	for (auto& Name : InNames)
	{
		Name = Decode(Name);
	}
}
