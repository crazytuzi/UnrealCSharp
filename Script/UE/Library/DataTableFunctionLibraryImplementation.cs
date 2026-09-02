using Interop;

namespace Script.Library
{
    public static partial class UDataTableFunctionLibraryImplementation
    {
        private static unsafe partial byte __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(nint Table, nint RowName, nint* OutRow);

        public static unsafe bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(
            nint Table, nint RowName, out T OutRow)
        {
            nint OutHandle = 0;

            var Result = __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table, RowName, &OutHandle);

            OutRow = OutHandle != 0 ? (T)HandleData.GetObject(OutHandle) : default;

            return Result != 0;
        }
    }
}