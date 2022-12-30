using System;
using Script.Binding;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public UObject ClassDefaultObject
        {
            get
            {
                ClassImplementation.Class_GetClassDefaultObjectImplementation(this, out var __OutValue);

                return __OutValue;
            }
        }

        public UObject GetDefaultObject(Boolean bCreateIfNeeded = true)
        {
            ClassImplementation.Class_GetDefaultObjectImplementation(this, bCreateIfNeeded, out var __OutValue);

            return __OutValue;
        }
    }
}