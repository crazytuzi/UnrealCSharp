#pragma once

template <typename InKeyType, typename InValueType>
class TMapping
{
public:
	typedef InKeyType KeyType;

	typedef InValueType ValueType;

public:
	auto operator[](const KeyType& InKey) -> ValueType&
	{
		return Map[InKey];
	}

	auto operator[](const KeyType& InKey) const -> const ValueType&
	{
		return Map[InKey];
	}

	auto Empty()
	{
		Map.Empty();
	}

	auto Add(const KeyType& InKey, const ValueType& InValue)
	{
		Map.Add(InKey, InValue);
	}

	auto Remove(const KeyType& InKey)
	{
		return Map.Remove(InKey);
	}

	auto Find(const KeyType& InKey)
	{
		return Map.Find(InKey);
	}

	auto Contains(const KeyType& InKey) const
	{
		return Map.Contains(InKey);
	}

public:
	auto Get() -> TMap<KeyType, ValueType>&
	{
		return Map;
	}

private:
	TMap<KeyType, ValueType> Map;
};
