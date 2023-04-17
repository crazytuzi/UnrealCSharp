#pragma once
#include "mono/metadata/object.h"

class UDataTableFunctionLibraryImplementation
{
public:
	static bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(MonoObject* InTable, MonoString* InRowName, MonoObject** OutRow);
};