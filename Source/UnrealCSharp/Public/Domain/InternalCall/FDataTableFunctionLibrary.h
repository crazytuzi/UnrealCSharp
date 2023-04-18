#pragma once

#include "mono/metadata/object.h"

class FDataTableFunctionLibraryImplementation
{
public:
	static bool DataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
		const MonoObject* Table, MonoString* RowName, MonoObject** OutRow);
};
