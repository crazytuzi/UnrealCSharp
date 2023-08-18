#pragma once

template <typename InKeyType, typename InValueType>
class TMapping
{
public:
	typedef InKeyType KeyType;

	typedef InValueType ValueType;

public:
	ValueType& operator[](const KeyType& InKey)
	{
		return Map[InKey];
	}

	const ValueType& operator[](const KeyType& InKey) const
	{
		return Map[InKey];
	}

	void Empty()
	{
		Map.Empty();
	}

	void Add(const KeyType& InKey, const ValueType& InValue)
	{
		Map.Add(InKey, InValue);
	}

	int32 Remove(const KeyType& InKey)
	{
		return Map.Remove(InKey);
	}

	ValueType* Find(const KeyType& InKey)
	{
		return Map.Find(InKey);
	}

	bool Contains(const KeyType& InKey) const
	{
		return Map.Contains(InKey);
	}

public:
	TMap<KeyType, ValueType>& Get()
	{
		return Map;
	}

private:
	TMap<KeyType, ValueType> Map;
};
