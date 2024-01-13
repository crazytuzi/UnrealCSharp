using Script.Common;
using Script.Library;

namespace Script.Engine
{
    public abstract partial class UDataTableFunctionLibrary
    {
        public static bool GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
        {
            return DataTableFunctionLibraryImplementation
                .DataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
                    Table.GarbageCollectionHandle,
                    RowName.GarbageCollectionHandle,
                    out OutRow);
        }
    }
}