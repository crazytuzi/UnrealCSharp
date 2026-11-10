using Script.CoreUObject;
using Script.Library;
using Interop;

namespace Script.Engine
{
    public abstract partial class UDataTableFunctionLibrary
    {
        public static bool GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
            where T : IStaticStruct
        {
            if (Table == null)
            {
                OutRow = default;

                return false;
            }

            return UDataTableFunctionLibraryImplementation
                .UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
                    HandleData.GetHandle(Table),
                    HandleData.GetHandle(RowName),
                    out OutRow);
        }
    }
}