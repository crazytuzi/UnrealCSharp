#pragma once

#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T, typename... Args>
auto FClassDescriptor::AddFunctionDescriptor(UFunction* InFunction, Args&&... InArgs) -> T*
{
	if (InFunction != nullptr)
	{
		const auto NewFunctionDescriptor = new T(InFunction, std::forward<Args>(InArgs)...);

		FunctionHashSet.Add(FUnrealCSharpFunctionLibrary::GetHash(InFunction));

		return NewFunctionDescriptor;
	}

	return nullptr;
}
