using Script.Library;
using Script.Common;
using Script.Engine;

namespace Script.CoreUObject
{
    public partial class UObject
    {
        public UClass GetClass()
        {
            ObjectImplementation.Object_GetClassImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString GetName()
        {
            ObjectImplementation.Object_GetNameImplementation(this, out var OutValue);

            return OutValue;
        }

        public UWorld GetWorld()
        {
            ObjectImplementation.Object_GetWorldImplementation(this, out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            return GetName().ToString();
        }
    }
}