using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.Engine;
using Script.Library;

namespace Script.Library
{
    public static class UDataTableFunctionLibraryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(UDataTable Table, string RowName, out T OutRow);
    }
}

namespace Script.Engine
{
    public partial class UDataTableFunctionLibrary : UBlueprintFunctionLibrary
    {
        public static Boolean GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
        {
            return UDataTableFunctionLibraryImplementation
                .UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table, RowName.ToString(), out OutRow);
        }
    }
}