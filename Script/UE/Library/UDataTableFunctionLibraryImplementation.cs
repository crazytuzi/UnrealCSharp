using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class UDataTableFunctionLibraryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(nint Table,
            nint RowName, out T OutRow);
    }
}