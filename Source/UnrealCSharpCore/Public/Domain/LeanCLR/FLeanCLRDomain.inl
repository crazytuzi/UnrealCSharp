#pragma once

#if WITH_LEANCLR
template <typename Result>
Result FLeanCLRDomain::Stack_Object_To(const leanclr::interp::RtStackObject& InStackObject)
{
	if constexpr (std::is_same_v<Result, IManagedHandle>)
	{
		return IManagedHandle{InStackObject.i64};
	}
	else if constexpr (std::is_same_v<Result, bool>)
	{
		return InStackObject.i32 != 0;
	}
	else if constexpr (std::is_same_v<Result, int32>)
	{
		return InStackObject.i32;
	}
	else if constexpr (std::is_same_v<Result, int64>)
	{
		return InStackObject.i64;
	}
	else if constexpr (std::is_pointer_v<Result>)
	{
		return static_cast<Result>(InStackObject.ptr);
	}
	else
	{
		return Result{};
	}
}

template <typename T>
struct FLeanCLRDomain::TStackArgument
{
	explicit TStackArgument(const T& InValue):
		Value(Stack_Object_From(InValue))
	{
	}

	auto Get() const -> const leanclr::interp::RtStackObject&
	{
		return Value;
	}

protected:
	leanclr::interp::RtStackObject Value;
};

template <typename Return, typename... Args, auto... Index>
Return FLeanCLRDomain::Bridge_Invoke_Helper(const leanclr::metadata::RtMethodInfo* InManagedMethod,
                                            std::index_sequence<Index...>, Args&&... InArgs)
{
	const std::tuple<TStackArgument<std::decay_t<Args>>...> Argument(std::forward<Args>(InArgs)...);

	leanclr::interp::RtStackObject Parameter[sizeof...(Args) + 1]{std::get<Index>(Argument).Get()...};

	leanclr::interp::RtStackObject OutReturn{};

	Runtime_Invoke(InManagedMethod, sizeof...(Args) != 0 ? Parameter : nullptr,
	               static_cast<int32>(sizeof...(Args)), OutReturn);

	if constexpr (std::is_void_v<Return>)
	{
		return;
	}
	else
	{
		return Stack_Object_To<Return>(OutReturn);
	}
}

template <typename Return, typename... Args>
Return FLeanCLRDomain::Bridge_Invoke(const leanclr::metadata::RtMethodInfo* InManagedMethod, Args&&... InArgs)
{
	return Bridge_Invoke_Helper<Return>(InManagedMethod, std::make_index_sequence<sizeof...(Args)>(),
	                                    std::forward<Args>(InArgs)...);
}
#endif
