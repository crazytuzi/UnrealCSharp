#pragma once

struct FNameSpace
{
	virtual ~FNameSpace() = default;

	virtual FString Get() const = 0;
};

struct FPrimitiveNameSpace final : FNameSpace
{
	virtual FString Get() const override
	{
		return TEXT("System");
	}

	static FPrimitiveNameSpace Instance;
};
