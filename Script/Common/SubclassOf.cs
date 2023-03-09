using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSubclassOf<T> where T : UObject
    {
        public TSubclassOf()
        {
        }

        ~TSubclassOf() => SubclassOfImplementation.SubclassOf_UnRegisterImplementation(this);

        public TSubclassOf(UClass InClass) => SubclassOfImplementation.SubclassOf_RegisterImplementation(this, InClass);

        public static implicit operator TSubclassOf<T>(UClass InClass) => new TSubclassOf<T>(InClass);

        public UClass Get()
        {
            SubclassOfImplementation.SubclassOf_GetImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}