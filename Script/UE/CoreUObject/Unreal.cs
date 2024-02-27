using Script.Engine;
using Script.Library;
using Script.UMG;

namespace Script.CoreUObject
{
    public static class Unreal
    {
        public static T NewObject<T>(UObject Outer,
            UClass Class,
            FName Name = null,
            EObjectFlags Flags = EObjectFlags.RF_NoFlags,
            UObject Template = null,
            bool bCopyTransientsFromClassDefaults = false
        ) where T : UObject =>
            UnrealImplementation.Unreal_NewObjectImplementation<T>(Outer.GarbageCollectionHandle,
                Class.GarbageCollectionHandle,
                Name?.GarbageCollectionHandle ?? FName.NAME_None.GarbageCollectionHandle,
                Flags,
                Template?.GarbageCollectionHandle ?? nint.Zero,
                bCopyTransientsFromClassDefaults);

        public static T NewObject<T>(UObject Outer,
            FName Name = null,
            EObjectFlags Flags = EObjectFlags.RF_NoFlags,
            UObject Template = null,
            bool bCopyTransientsFromClassDefaults = false
        ) where T : UObject, IStaticClass =>
            NewObject<T>(Outer,
                T.StaticClass(),
                Name,
                Flags,
                Template,
                bCopyTransientsFromClassDefaults);

        public static T DuplicateObject<T>(UObject SourceObject, UObject Outer, FName Name = null) where T : UObject =>
            UnrealImplementation.Unreal_DuplicateObjectImplementation<T>(SourceObject.GarbageCollectionHandle,
                Outer.GarbageCollectionHandle,
                Name?.GarbageCollectionHandle ?? FName.NAME_None.GarbageCollectionHandle);

        public static T LoadObject<T>(UObject Outer,
            FString Name,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null
        ) where T : UObject =>
            UnrealImplementation.Unreal_LoadObjectImplementation<T>(Outer.GarbageCollectionHandle,
                Name?.GarbageCollectionHandle ?? nint.Zero,
                Filename?.GarbageCollectionHandle ?? nint.Zero,
                LoadFlags,
                Sandbox?.GarbageCollectionHandle ?? nint.Zero);

        public static T LoadObject<T>(UObject Outer,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null
        ) where T : UObject =>
            LoadObject<T>(Outer,
                Utils.GetPathName(typeof(T)),
                Filename,
                LoadFlags,
                Sandbox);

        public static UClass LoadClass(UObject Outer,
            FString Name = null,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null) =>
            UnrealImplementation.Unreal_LoadClassImplementation(Outer.GarbageCollectionHandle,
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

        public static UWorld GWorld => UnrealImplementation.Unreal_GWorldImplementation();
    }
}