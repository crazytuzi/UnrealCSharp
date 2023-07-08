#pragma once

#include "FFunctionInfo.h"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <bool bIsStatic, typename Result, typename... Args>
struct TFunctionInfo final : FFunctionInfo
{
	TFunctionInfo():
		Return{TTypeInfo<Result>::Get()},
		Argument{TTypeInfo<Args>::Get()...}
	{
	}

	virtual bool IsStatic() const override
	{
		return bIsStatic;
	}

	virtual FTypeInfo* GetReturn() const override
	{
		return Return;
	}

	virtual const TArray<FTypeInfo*>& GetParams() const override
	{
		return Argument;
	}

	static FFunctionInfo* Get()
	{
		static TFunctionInfo Instance;

		return &Instance;
	}

private:
	FTypeInfo* Return;

	TArray<FTypeInfo*> Argument;
};
