#pragma once

#include "EFunctionType.h"
#include "FFunctionInfo.h"
#include "TDefaultArguments.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <auto, EFunctionType FunctionType, typename Result, typename... Args>
struct TFunctionInfo final : FFunctionInfo
{
	TFunctionInfo():
		FunctionInteract(EFunctionInteract::None),
		Return{TTypeInfo<Result>::Get()},
		Argument{TTypeInfo<Args>::Get()...}
	{
	}

	explicit TFunctionInfo(const TArray<FString>& InParamNames, const TArray<FString>& InDefaultArguments):
		ParamNames(InParamNames),
		DefaultArguments(InDefaultArguments),
		FunctionInteract(EFunctionInteract::None),
		Return{TTypeInfo<Result>::Get()},
		Argument{TTypeInfo<Args>::Get()...}
	{
	}

	explicit TFunctionInfo(const EFunctionInteract InFunctionInteract):
		FunctionInteract(InFunctionInteract),
		Return{TTypeInfo<Result>::Get()},
		Argument{TTypeInfo<Args>::Get()...}
	{
	}

	explicit TFunctionInfo(const TArray<FString>& InParamNames, const EFunctionInteract InFunctionInteract,
	                       const TArray<FString>& InDefaultArguments):
		ParamNames(InParamNames),
		DefaultArguments(InDefaultArguments),
		FunctionInteract(InFunctionInteract),
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

	virtual const TArray<FString>& GetParamNames() const override
	{
		return ParamNames;
	}

	virtual void SetParamNames(const TArray<FString>& InParamNames) override
	{
		ParamNames = InParamNames;
	}

	virtual const TArray<FString>& GetDefaultArguments() const override
	{
		return DefaultArguments;
	}

	virtual EFunctionInteract GetFunctionInteract() const override
	{
		return FunctionInteract;
	}

	static FFunctionInfo* Get()
	{
		static TFunctionInfo Instance;

		return &Instance;
	}

	template <typename... DefaultArguments>
	static FFunctionInfo* Get(const TArray<FString>& InParamNames,
	                          DefaultArguments&&... InDefaultArguments)
	{
		static TFunctionInfo Instance(InParamNames,
		                              TDefaultArguments<Args...>::Get(
			                              std::forward<DefaultArguments>(InDefaultArguments)...));

		return &Instance;
	}

	static FFunctionInfo* Get(const EFunctionInteract InFunctionInteract)
	{
		static TFunctionInfo Instance(InFunctionInteract);

		return &Instance;
	}

	template <typename... DefaultArguments>
	static FFunctionInfo* Get(const TArray<FString>& InParamNames, const EFunctionInteract InFunctionInteract,
	                          DefaultArguments&&... InDefaultArguments)
	{
		static TFunctionInfo Instance(InParamNames,
		                              InFunctionInteract,
		                              TDefaultArguments<Args...>::Get(
			                              std::forward<DefaultArguments>(InDefaultArguments)...));

		return &Instance;
	}

private:
	TArray<FString> ParamNames;

	TArray<FString> DefaultArguments;

	EFunctionInteract FunctionInteract;

	FTypeInfo* Return;

	TArray<FTypeInfo*> Argument;
};
