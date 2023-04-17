#pragma once

#include "Kismet/DataTableFunctionLibrary.h"

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

template <>
struct TClassName<UWorld>
{
	static FString Get() { return TEXT("World"); }
};

template <>
struct TClassName<UDataTableFunctionLibrary>
{
	static FString Get() { return TEXT("DataTableFunctionLibrary"); }
};
