#pragma once


#include "CoreMinimal.h"

class FNameEncode
{
public:
	static UNREALCSHARPCORE_API FString Encode(const FString& Name, bool bEncodeWideString = false);

	static UNREALCSHARPCORE_API void Encode(TArray<FString>& Names);
	
	static UNREALCSHARPCORE_API FString Decode(const FString& Name);
	
	static UNREALCSHARPCORE_API void Decode(TArray<FString>& Names);
	
	// static UNREALCSHARPCORE_API void UnitTest();
};

