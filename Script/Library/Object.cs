using Script.Library;
using Script.Common;

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

        public virtual FString ToFString()
        {
            return GetName();
        }

        public override string ToString()
        {
            return ToFString().ToString();
        }
    }
}