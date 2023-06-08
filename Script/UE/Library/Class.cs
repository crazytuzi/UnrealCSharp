using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public UObject ClassDefaultObject
        {
            get
            {
                ClassImplementation.Class_GetClassDefaultObjectImplementation(this, out var __OutValue);

                return (UObject)__OutValue;
            }
        }

        public UObject GetDefaultObject(Boolean bCreateIfNeeded = true)
        {
            ClassImplementation.Class_GetDefaultObjectImplementation(this, bCreateIfNeeded, out var __OutValue);

            return __OutValue;
        }
    }
}