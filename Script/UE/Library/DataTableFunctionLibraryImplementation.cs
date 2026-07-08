using Interop;

namespace Script.Library
{
    public static partial class UDataTableFunctionLibraryImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint*, byte>
            __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation;

        public static unsafe bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(
            nint Table, nint RowName, out T OutRow)
        {
            if (__UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation == null)
            {
                __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint*, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UDataTableFunctionLibraryImplementation::UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation");
            }

            nint OutHandle = 0;

            var Result = __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table, RowName, &OutHandle);

            OutRow = OutHandle != 0 ? (T)HandleData.GetObject(OutHandle) : default;

            return Result != 0;
        }
    }
}