#pragma once

struct FTypeInfo
{
	virtual ~FTypeInfo() = default;

	virtual FString GetName() const = 0;

	virtual const TArray<FString>& GetNameSpace() const = 0;

	virtual bool IsRef() const = 0;

	virtual bool IsStatic() const = 0;

	virtual bool IsPrimitive() const = 0;
};
