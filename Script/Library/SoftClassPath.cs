using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FSoftClassPath
    {
        // @TODO
        // TryLoadClass
        // ResolveClass
        // SerializeFromMismatchedTag

        public static FSoftClassPath GetOrCreateIDForClass(UClass InClass)
        {
            SoftClassPathImplementation.SoftClassPath_GetOrCreateIDForClassImplementation(InClass, out var OutValue);

            return OutValue;
        }
    }
}