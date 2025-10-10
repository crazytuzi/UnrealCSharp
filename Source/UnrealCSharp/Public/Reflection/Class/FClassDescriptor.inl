#pragma once

template <typename T, typename... Args>
auto FClassDescriptor::AddFunctionDescriptor(UFunction* InFunction, Args&&... InArgs) -> T*
{
	if (InFunction != nullptr)
	{
		const auto NewFunctionDescriptor = new T(InFunction, std::forward<Args>(InArgs)...);

		FunctionHashSet.Add(GetTypeHash(InFunction));

		return NewFunctionDescriptor;
	}

	return nullptr;
}
