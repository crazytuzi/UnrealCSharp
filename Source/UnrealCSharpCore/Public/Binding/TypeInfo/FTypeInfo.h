#pragma once

#define WITH_PROPERTY_INFO WITH_EDITOR

struct FTypeInfo
{
	virtual ~FTypeInfo() = default;

	virtual FString GetName() const = 0;

	virtual const TArray<FString>& GetNameSpace() const = 0;

	virtual bool IsOut() const = 0;
};
