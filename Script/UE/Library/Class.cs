using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public UObject GetDefaultObject(Boolean bCreateIfNeeded = true)
        {
            return ClassImplementation.Class_GetDefaultObjectImplementation(GetHandle(), bCreateIfNeeded);
        }
    }
}