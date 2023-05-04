using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Unreal
    {
        // @TODO
        public static T NewObject<T>(UObject Outer, UClass Class, FName Name) where T : UObject
        {
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer, Class, Name, out var OutValue);

            return OutValue;
        }

        public static T NewObject<T>(UObject Outer) where T : UObject, IStaticClass
        {
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer, T.StaticClass(), "", out var OutValue);

            return OutValue;
        }

        // @TODO
        public static T NewObject<T>(UObject Outer, FName Name) where T : UObject, IStaticClass
        {
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer, T.StaticClass(), Name, out var OutValue);

            return OutValue;
        }

        public static T DuplicateObject<T>(UObject SourceObject, UObject Outer, FName Name) where T : UObject
        {
            UnrealImplementation.Unreal_DuplicateObjectImplementation<T>(SourceObject, Outer, Name, out var OutValue);

            return OutValue;
        }

        // @TODO
        public static T LoadObject<T>(UObject Outer, string Name) where T : UObject
        {
            UnrealImplementation.Unreal_LoadObjectImplementation<T>(Outer, Name, out var OutValue);

            return OutValue;
        }

        // @TODO
        public static UClass LoadClass(UObject Outer, string Name)
        {
            UnrealImplementation.Unreal_LoadClassImplementation(Outer, Name, out var OutValue);

            return OutValue;
        }
    }
}