#pragma once

#include "UEVersion.h"

template <typename T>
static FString TGetUTF8String(T&& InFunction)
{
	constexpr int32 StackBufferSize = 512;

	constexpr int32 MaxBufferSize = 64 * 1024;

	uint8 StackString[StackBufferSize];

	auto Length = InFunction(StackString, StackBufferSize);

	if (Length <= 0)
	{
		return {};
	}

	if (Length < StackBufferSize - 1)
	{
#if UE_F_STRING_CONSTRUCT_FROM_PTR_SIZE
		return FString::ConstructFromPtrSize(reinterpret_cast<const UTF8CHAR*>(StackString), Length);
#else
		return FString(Length, reinterpret_cast<const UTF8CHAR*>(StackString));
#endif
	}

	TArray<uint8> HeapString;

	for (auto BufferSize = StackBufferSize * 2; BufferSize <= MaxBufferSize; BufferSize *= 2)
	{
		HeapString.SetNumUninitialized(BufferSize);

		Length = InFunction(HeapString.GetData(), BufferSize);

		if (Length <= 0)
		{
			return {};
		}

		if (Length < BufferSize - 1)
		{
#if UE_F_STRING_CONSTRUCT_FROM_PTR_SIZE
			return FString::ConstructFromPtrSize(reinterpret_cast<const UTF8CHAR*>(HeapString.GetData()), Length);
#else
			return FString(Length, reinterpret_cast<const UTF8CHAR*>(HeapString.GetData()));
#endif
		}
	}

	return {};
}
