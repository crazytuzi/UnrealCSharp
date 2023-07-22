#pragma once

struct FTypeInfo
{
	virtual ~FTypeInfo() = default;

	virtual FString GetName() const = 0;

	virtual const TArray<FString>& GetNameSpace() const = 0;

	virtual bool IsOut() const = 0;
};
