#pragma once

#include "EFunctionType.h"
#include "FFunctionInfo.h"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <EFunctionType FunctionType, typename Result, typename... Args>
struct TFunctionInfo final : FFunctionInfo
{
	TFunctionInfo():
		Return{TTypeInfo<Result>::Get()},
		Argument{TTypeInfo<Args>::Get()...}
	{
	}

	virtual bool IsConstructor() const override
	{
		return FunctionType == EFunctionType::Constructor;
	}

	virtual bool IsDestructor() const override
	{
		return FunctionType == EFunctionType::Destructor;
	}

	virtual bool IsStatic() const override
	{
		return FunctionType == EFunctionType::Static;
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
