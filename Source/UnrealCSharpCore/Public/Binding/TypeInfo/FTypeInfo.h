#pragma once

struct FTypeInfo
{
	virtual ~FTypeInfo() = default;

	virtual FString GetName() const = 0;

	virtual TArray<FString> GetNameSpace() const = 0;
};
