using System;
using System.Runtime.CompilerServices;
using Script.Engine;

namespace Script.Library
{
    public static class DataTableFunctionLibraryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(UDataTable Table,
            string RowName, out T OutRow);
    }
}