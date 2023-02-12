#pragma once

#include "CoreMinimal.h"

class FEnumGenerator
{
public:
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(const UEnum* InEnum);


	static GENERATOR_API void EmplaceEnumUnderlyingCache(const UEnum* Enum, FNumericProperty* Property);

	static GENERATOR_API FFieldClass* GetEnumUnderlyingCache(const UEnum* Enum);
	
	static GENERATOR_API void ClearEnumUnderlyingCache();
	
};
