using System;
using Script.Common;
using Script.Library;

namespace Script.Engine
{
    public abstract partial class UDataTableFunctionLibrary
    {
        public static Boolean GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
        {
            return DataTableFunctionLibraryImplementation
                .DataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table.GetHandle(), RowName.GetHandle(),
                    out OutRow);
        }
    }
}