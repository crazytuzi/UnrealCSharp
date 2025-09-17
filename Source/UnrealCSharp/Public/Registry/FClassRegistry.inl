#pragma once

#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

template <typename T>
auto FClassRegistry::GetFunctionDescriptor(const uint32 InFunctionHash) -> T*
{
	const auto FoundFunctionDescriptor = FunctionDescriptorMap.Find(InFunctionHash);

	return FoundFunctionDescriptor != nullptr ? static_cast<T*>(*FoundFunctionDescriptor) : nullptr;
}

template <typename T>
auto FClassRegistry::GetOrAddFunctionDescriptor(const uint32 InFunctionHash) -> T*
{
	if (const auto FoundFunctionDescriptor = GetFunctionDescriptor<T>(InFunctionHash))
	{
		return FoundFunctionDescriptor;
	}

	if constexpr (std::is_same_v<T, FCSharpFunctionDescriptor>)
	{
		if (const auto FoundFunctionHash = CSharpFunctionHashMap.Find(InFunctionHash))
		{
			if (const auto FoundFunctionDescriptor = std::get<0>(*FoundFunctionHash)->AddFunctionDescriptor<T>(
				std::get<1>(*FoundFunctionHash), std::move(std::get<2>(*FoundFunctionHash))))
			{
				CSharpFunctionHashMap.Remove(InFunctionHash);

				FunctionDescriptorMap.Add(InFunctionHash, FoundFunctionDescriptor);

				return FoundFunctionDescriptor;
			}
		}
	}
	else if constexpr (std::is_same_v<T, FUnrealFunctionDescriptor>)
	{
		if (const auto FoundFunctionHash = UnrealFunctionHashMap.Find(InFunctionHash))
		{
			if (const auto FoundFunctionDescriptor = std::get<0>(*FoundFunctionHash)->AddFunctionDescriptor<T>(
				std::get<1>(*FoundFunctionHash)))
			{
				UnrealFunctionHashMap.Remove(InFunctionHash);

				FunctionDescriptorMap.Add(InFunctionHash, FoundFunctionDescriptor);

				return FoundFunctionDescriptor;
			}
		}
	}

	return nullptr;
}

template <typename T, typename... Args>
auto FClassRegistry::AddFunctionHash(uint32 InFunctionHash, Args&&... InArgs) -> void
{
	if constexpr (std::is_same_v<T, FCSharpFunctionDescriptor>)
	{
		CSharpFunctionHashMap.Add(InFunctionHash, std::make_tuple(std::forward<Args>(InArgs)...));
	}
	else if constexpr (std::is_same_v<T, FUnrealFunctionDescriptor>)
	{
		UnrealFunctionHashMap.Add(InFunctionHash, std::make_tuple(std::forward<Args>(InArgs)...));
	}
}
