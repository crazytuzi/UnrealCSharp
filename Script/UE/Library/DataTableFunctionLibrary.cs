﻿using System;
using Script.Common;
using Script.Library;

namespace Script.Engine
{
    public partial class UDataTableFunctionLibrary
    {
        public static Boolean GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
        {
            return DataTableFunctionLibraryImplementation
                .DataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table.GetHandle(), RowName.ToString(),
                    out OutRow);
        }
    }
}