using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class DataTableFunctionLibraryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(IntPtr Table,
            FName RowName, out T OutRow);
    }
}