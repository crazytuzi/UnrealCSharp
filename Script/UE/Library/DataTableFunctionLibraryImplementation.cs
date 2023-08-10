using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class DataTableFunctionLibraryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(IntPtr Table,
            string RowName, out T OutRow);
    }
}