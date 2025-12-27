#pragma once

template <typename T, typename Enable = void>
struct TStaticName
{
	static auto IsEmpty()
	{
		return true;
	}

	static auto Get()
	{
		return FString();
	}
};
