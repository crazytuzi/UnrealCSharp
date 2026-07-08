using Script.CoreUObject;
using Script.Library;
using Interop;

namespace Script.Engine
{
    public abstract partial class UDataTableFunctionLibrary
    {
        public static bool GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
        {
            return UDataTableFunctionLibraryImplementation
                .UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
                    HandleData.GetHandle(Table),
                    HandleData.GetHandle(RowName),
                    out OutRow);
        }
    }
}