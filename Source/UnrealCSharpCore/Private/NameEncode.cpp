#include "NameEncode.h"

#include <ctype.h>

#define ESCAPE_SYMBOL TEXT("__")
#define ESCAPE_SYMBOL_LEN 2
#define ESCAPE_END_SYMBOL TEXT('_')
#define ESCAPE_HEAD_NUMBER 1
#define ESCAPE_HEAD_NUMBER_SYMBOL TEXT("01")

/*
 * 转义规则：
 * 对在a-z A-Z 0-9 _ 以外 并在[0, 127]的ascii范围内的可见字符进行转义
 * 转义结果为 双下划綫开头+ascii码+单下划线结尾，如字符 - 会被转换为 __2D_
 * 双下划綫 __ 会被视作转义符，对后面的内容进行转义
 * 如原字符串中存在转义符 __ ，那么会将双下划綫转义为下划线的ascii码， 字符串 __ 转换为 __5F_
 * 以数字开头的字符串，将会在前面添加__01_转义，如 3DWidget 转换为 __01_3DWidget
 * 单下划线不会被转义
 *
 * 总结：
 * 只使用a-z A-Z 0-9 _ 和非ascii字符 将不会被转义
 * ascii的特殊符号 一个以上连续的下划线 和数字开头的名字会被转义
 */


static inline bool ShouldEscape(int C)
{
	return C <= 127 && !(::isalnum(C) || C == '_');
}

static const char* HexList = "0123456789ABCDEF";

static void ByteToHex(uint8_t Value, TCHAR* Out)
{
	Out[0] = HexList[Value / 16];
	Out[1] = HexList[Value % 16];
}

static uint8 HexToByte(TCHAR Str)
{
	return Str >= 'A' ? Str - 'A' + 10 : Str - '0';
}

static uint8 HexToByte(const TCHAR* Str)
{
	return HexToByte(Str[0]) * 16 + HexToByte(Str[1]);
}

FString FNameEncode::Encode(const FString& Name)
{
	FString Ret;
	Ret.Reserve(Name.Len() + 4);
	for (int i = 0; i < Name.Len(); ++i)
	{
		auto C = Name[i];

		// escape __
		bool bEscape = C == TEXT('_') && i != Name.Len() - 2 && Name[i + 1] == TEXT('_');
		bool bHeadDigit = i == 0 && ::isdigit(C);

		if (bHeadDigit)
		{
			Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
			Ret.AppendChars(ESCAPE_HEAD_NUMBER_SYMBOL, 2);
			Ret.AppendChar(ESCAPE_END_SYMBOL);
			Ret.AppendChar(C);
		}
		else if (bEscape || ShouldEscape(C))
		{
			Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
			TCHAR Hex[2];
			ByteToHex(C, Hex);
			Ret.AppendChars(Hex, 2);
			Ret.AppendChar(ESCAPE_END_SYMBOL);
			if (bEscape)
			{
				++i;
			}
		}
		else
		{
			Ret.AppendChar(C);
		}
	}

	return Ret;
}

void FNameEncode::Encode(TArray<FString>& Names)
{
	for (auto& Name : Names)
	{
		Name = Encode(Name);
	}
}

FString FNameEncode::Decode(const FString& Name)
{
	FString Ret;
	Ret.Reserve(Name.Len());

	for (int i = 0; i < Name.Len(); ++i)
	{
		auto C = Name[i];
		bool bEscape = C == TEXT('_') && i != Name.Len() - 2 && Name[i + 1] == TEXT('_');

		if (bEscape)
		{
			// format error
			check(i + 3 >= Name.Len() || Name[i + 3] != ESCAPE_END_SYMBOL);

			auto Hex = HexToByte(GetData(Name) + i + 2);

			if (Hex == ESCAPE_HEAD_NUMBER)
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
			i += 4;
		}
		else
		{
			Ret.AppendChar(C);
		}
	}
	return Ret;
}

void FNameEncode::Decode(TArray<FString>& Names)
{
	for (auto& Name : Names)
	{
		Name = Decode(Name);
	}
}

/*
void FNameEncode::UnitTest()
{
	auto h0 = HexToByte(TEXT('A'));
	check(h0 == 10)
	
	auto h1 = HexToByte(TEXT('C'));
	check(h1 == 12)

	auto h2 = HexToByte(TEXT('3'));
	check(h2 == 3)

	auto h3 = HexToByte(TEXT("FF"));
	check(h3 == 255);

	TCHAR Char3[2];
	ByteToHex(TEXT('3'), Char3);
	check(Char3[0] == TEXT('3') && Char3[1] == TEXT('3'));

	FString v1s = TEXT("3DWidget");
	auto v1 = Encode(v1s);
	auto v1r = Decode(v1);
	check(v1s == v1r);
	
	FString v2s = TEXT("__01_3DWidget");
	auto v2 = Encode(v2s);
	auto v2r = Decode(v2);
	check(v2s == v2r);
	
	FString v3s = TEXT("Anim");
	auto v3 = Encode(v3s);
	auto v3r = Decode(v3);
	check(v3s == v3r);
	
	FString v4s = TEXT("Anim-a");
	auto v4 = Encode(v4s);
	auto v4r = Decode(v4);
	check(v4s == v4r);
	
	FString v5s = TEXT("Anim_v1");
	auto v5 = Encode(v5s);
	auto v5r = Decode(v5);
	check(v5s == v5r);
	
	FString v6s = TEXT("Anim__v2");
	auto v6 = Encode(v6s);
	auto v6r = Decode(v6);
	check(v6s == v6r);
	
	FString v7s = TEXT("Anim___v3");
	auto v7 = Encode(v7s);
	auto v7r = Decode(v7);
	check(v7s == v7r);
	
	FString v8s = TEXT("IsCtrl?");
	auto v8 = Encode(v8s);
	auto v8r = Decode(v8);
	check(v8s == v8r);
	
	FString v9s = TEXT("get data");
	auto v9 = Encode(v9s);
	auto v9r = Decode(v9);
	check(v9s == v9r);
	
	FString v10s = TEXT("技能3");
	auto v10 = Encode(v10s);
	auto v10r = Decode(v10);
	check(v10s == v10r);
	
	FString v11s = TEXT("+5/-*)(<>.!?#$%^&@");
	auto v11 = Encode(v11s);
	auto v11r = Decode(v11);
	check(v11s == v11r);
	
}
*/
