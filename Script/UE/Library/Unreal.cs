using System;
using Script.Common;
using Script.CoreUObject;
using Script.Engine;
using Script.UMG;

namespace Script.Library
{
    public static class Unreal
    {
        // @TODO
        public static T NewObject<T>(UObject Outer, UClass Class, FName Name) where T : UObject
        {
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer.GetHandle(), Class.GetHandle(), Name,
                out var OutValue);

            return OutValue;
        }

        public static T NewObject<T>(UObject Outer) where T : UObject, IStaticClass
        {
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer.GetHandle(), T.StaticClass().GetHandle(), "",
                out var OutValue);

            return OutValue;
        }

        // @TODO
        public static T NewObject<T>(UObject Outer, FName Name) where T : UObject, IStaticClass
        {
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer.GetHandle(), T.StaticClass().GetHandle(), Name,
                out var OutValue);

            return OutValue;
        }

        public static T DuplicateObject<T>(UObject SourceObject, UObject Outer, FName Name) where T : UObject
        {
            UnrealImplementation.Unreal_DuplicateObjectImplementation<T>(SourceObject.GetHandle(), Outer.GetHandle(),
                Name, out var OutValue);

            return OutValue;
        }

        // @TODO
        public static T LoadObject<T>(UObject Outer, String Name) where T : UObject
        {
            UnrealImplementation.Unreal_LoadObjectImplementation<T>(Outer.GetHandle(), Name, out var OutValue);

            return OutValue;
        }

        public static T LoadObject<T>(UObject Outer) where T : UObject
        {
            UnrealImplementation.Unreal_LoadObjectImplementation<T>(Outer.GetHandle(), Utils.GetPathName(typeof(T)),
                out var OutValue);

            return OutValue;
        }

        // @TODO
        public static UClass LoadClass(UObject Outer, String Name)
        {
            UnrealImplementation.Unreal_LoadClassImplementation(Outer.GetHandle(), Name, out var OutValue);

            return OutValue;
        }

        public static T CreateWidget<T>(UWidget OwningObject) where T : UUserWidget, IStaticClass
        {
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GetHandle(),
                T.StaticClass().GetHandle(), out var OutValue);

            return OutValue;
        }

        public static T CreateWidget<T>(UWidgetTree OwningObject) where T : UUserWidget, IStaticClass
        {
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GetHandle(),
                T.StaticClass().GetHandle(), out var OutValue);

            return OutValue;
        }

        public static T CreateWidget<T>(APlayerController OwningObject) where T : UUserWidget, IStaticClass
        {
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GetHandle(),
                T.StaticClass().GetHandle(), out var OutValue);

            return OutValue;
        }

        public static T CreateWidget<T>(UGameInstance OwningObject) where T : UUserWidget, IStaticClass
        {
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GetHandle(),
                T.StaticClass().GetHandle(), out var OutValue);

            return OutValue;
        }

        public static T CreateWidget<T>(UWorld OwningObject) where T : UUserWidget, IStaticClass
        {
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GetHandle(),
                T.StaticClass().GetHandle(), out var OutValue);

            return OutValue;
        }

        public static UWorld GWorld
        {
            get
            {
                UnrealImplementation.Unreal_GWorldImplementation(out var value);

                return value;
            }
        }

        public static T Cast<T>(UObject Outer) where T : UObject, IStaticClass
        {
            if (Outer.IsA<T>())
            {
                return Outer as T;
            }

            return null;
        }
    }
}