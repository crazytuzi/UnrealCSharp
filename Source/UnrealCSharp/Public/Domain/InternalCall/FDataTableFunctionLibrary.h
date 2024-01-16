#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FDataTableFunctionLibraryImplementation
{
public:
	static bool DataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* RowName, MonoObject** OutRow);
};
