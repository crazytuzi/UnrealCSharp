using System;
using Script.Engine;
using Script.Library;
using Script.UMG;

namespace Script.CoreUObject
{
    public static class Unreal
    {
        public static T NewObject<T>(UObject Outer = null,
            UClass Class = null,
            FName Name = null,
            EObjectFlags Flags = EObjectFlags.RF_NoFlags,
            UObject Template = null,
            bool bCopyTransientsFromClassDefaults = false
        ) where T : UObject, IStaticClass =>
            UnrealImplementation.Unreal_NewObjectImplementation<T>(
                Outer?.GarbageCollectionHandle ?? nint.Zero,
                Class?.GarbageCollectionHandle ?? T.StaticClass().GarbageCollectionHandle,
                Name?.GarbageCollectionHandle ?? FName.NAME_None.GarbageCollectionHandle,
                Flags,
                Template?.GarbageCollectionHandle ?? nint.Zero,
                bCopyTransientsFromClassDefaults);

        public static T DuplicateObject<T>(UObject SourceObject, UObject Outer = null, FName Name = null)
            where T : UObject =>
            UnrealImplementation.Unreal_DuplicateObjectImplementation<T>(
                SourceObject?.GarbageCollectionHandle ?? nint.Zero,
                Outer?.GarbageCollectionHandle ?? nint.Zero,
                Name?.GarbageCollectionHandle ?? FName.NAME_None.GarbageCollectionHandle);

        public static T LoadObject<T>(UObject Outer = null,
            FString Name = null,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null
        ) where T : UObject =>
            UnrealImplementation.Unreal_LoadObjectImplementation<T>(
                Outer?.GarbageCollectionHandle ?? nint.Zero,
                Name?.GarbageCollectionHandle ?? new FString(Utils.GetPathName(typeof(T))).GarbageCollectionHandle,
                Filename?.GarbageCollectionHandle ?? nint.Zero,
                LoadFlags,
                Sandbox?.GarbageCollectionHandle ?? nint.Zero);

        public static UClass LoadClass(UObject Outer,
            FString Name,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null) =>
            UnrealImplementation.Unreal_LoadClassImplementation(
                Outer?.GarbageCollectionHandle ?? nint.Zero,
                Name?.GarbageCollectionHandle ?? nint.Zero,
                Filename?.GarbageCollectionHandle ?? nint.Zero,
                LoadFlags,
                Sandbox?.GarbageCollectionHandle ?? nint.Zero);

        public static T CreateWidget<T>(UWidget OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public static T CreateWidget<T>(UWidgetTree OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public static T CreateWidget<T>(APlayerController OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public static T CreateWidget<T>(UGameInstance OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public static T CreateWidget<T>(UWorld OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(OwningObject.GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public static UEnum StaticEnum<T>() where T : Enum
        {
            return LoadObject<UEnum>(null, Utils.GetPathName(typeof(T)));
        }

        public static UWorld GWorld => UnrealImplementation.Unreal_GWorldImplementation();
    }
}