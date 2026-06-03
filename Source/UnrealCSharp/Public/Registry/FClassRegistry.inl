#pragma once

#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

template <typename T>
auto FClassRegistry::GetFunctionDescriptor(const uint32 InFunctionHash) -> T*
{
	if constexpr (std::is_same_v<T, FCSharpFunctionDescriptor>)
	{
		const auto FoundFunctionDescriptor = CSharpFunctionDescriptorMap.Find(InFunctionHash);

		return FoundFunctionDescriptor != nullptr ? *FoundFunctionDescriptor : nullptr;
	}
	else if constexpr (std::is_same_v<T, FUnrealFunctionDescriptor>)
	{
		const auto FoundFunctionDescriptor = UnrealFunctionDescriptorMap.Find(InFunctionHash);

		return FoundFunctionDescriptor != nullptr ? *FoundFunctionDescriptor : nullptr;
	}
	else
	{
		return nullptr;
	}
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

				CSharpFunctionDescriptorMap.Add(InFunctionHash, FoundFunctionDescriptor);

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

				UnrealFunctionDescriptorMap.Add(InFunctionHash, FoundFunctionDescriptor);

				return FoundFunctionDescriptor;
			}
		}
	}

	return nullptr;
}

template <typename T>
void FClassRegistry::AddFunctionDescriptor(uint32 InFunctionHash, T* InFunctionDescriptor)
{
	if constexpr (std::is_same_v<T, FCSharpFunctionDescriptor>)
	{
		CSharpFunctionDescriptorMap.Add(InFunctionHash, InFunctionDescriptor);
	}
	else if constexpr (std::is_same_v<T, FUnrealFunctionDescriptor>)
	{
		UnrealFunctionDescriptorMap.Add(InFunctionHash, InFunctionDescriptor);
	}
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
