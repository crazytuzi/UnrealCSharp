#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static partial class UDataTableFunctionLibraryImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(nint Table,
            nint RowName, out T OutRow);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint*, int>
            __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation;

        public static unsafe bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(
            nint Table, nint RowName, out T OutRow)
        {
            if (__UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation == null)
            {
                __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint*, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.UDataTableFunctionLibraryImplementation::UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation");
            }

            nint OutHandle = 0;

            var Result = __UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table, RowName, &OutHandle);

            OutRow = OutHandle != 0 ? (T)HandleData.GetObject(OutHandle) : default;

            return Result != 0;
        }
#endif
    }
}