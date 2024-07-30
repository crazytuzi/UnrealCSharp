#pragma once

#include "EFunctionType.h"
#include "FFunctionInfo.h"
#include "TDefaultArguments.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <auto, auto FunctionType, typename Result, typename... Args>
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

	virtual auto IsConstructor() const -> bool override
	{
		return FunctionType == EFunctionType::Constructor;
	}

	virtual auto IsDestructor() const -> bool override
	{
		return FunctionType == EFunctionType::Destructor;
	}

	virtual auto IsStatic() const -> bool override
	{
		return FunctionType == EFunctionType::Static;
	}

	virtual auto GetReturn() const -> FTypeInfo* override
	{
		return Return;
	}

	virtual auto GetParams() const -> const TArray<FTypeInfo*>& override
	{
		return Argument;
	}

	virtual auto GetParamNames() const -> const TArray<FString>& override
	{
		return ParamNames;
	}

	virtual auto SetParamNames(const TArray<FString>& InParamNames) -> void override
	{
		ParamNames = InParamNames;
	}

	virtual auto GetDefaultArguments() const -> const TArray<FString>& override
	{
		return DefaultArguments;
	}

	virtual auto GetFunctionInteract() const -> EFunctionInteract override
	{
		return FunctionInteract;
	}

	static auto Get() -> FFunctionInfo*
	{
		static TFunctionInfo Instance;

		return &Instance;
	}

	template <typename... DefaultArguments>
	static auto Get(const TArray<FString>& InParamNames, DefaultArguments&&... InDefaultArguments) -> FFunctionInfo*
	{
		static TFunctionInfo Instance(InParamNames,
		                              TDefaultArguments<Args...>::Get(
			                              std::forward<DefaultArguments>(InDefaultArguments)...));

		return &Instance;
	}

	static auto Get(const EFunctionInteract InFunctionInteract) -> FFunctionInfo*
	{
		static TFunctionInfo Instance(InFunctionInteract);

		return &Instance;
	}

	template <typename... DefaultArguments>
	static auto Get(const TArray<FString>& InParamNames, const EFunctionInteract InFunctionInteract,
	                DefaultArguments&&... InDefaultArguments) -> FFunctionInfo*
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
