using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class DataTableFunctionLibraryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool DataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(nint Table,
            nint RowName, out T OutRow);
    }
}