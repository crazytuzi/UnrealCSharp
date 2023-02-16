#pragma once

template <class T>
struct TClassName
{
	static FString Get() { return T::StaticClass()->GetName(); }
};

template <>
struct TClassName<UObject>
{
	static FString Get() { return TEXT("Object"); }
};

template <>
struct TClassName<UClass>
{
	static FString Get() { return TEXT("Class"); }
};
