using System;
using Script.Common;
using Script.CoreUObject;
using Script.Engine;
using Script.UMG;

namespace Script.Library
{
    public static class Unreal
    {
        public static T NewObject<T>(UObject Outer,
            UClass Class,
            FName Name = null,
            EObjectFlags Flags = EObjectFlags.RF_NoFlags,
            UObject Template = null,
            Boolean bCopyTransientsFromClassDefaults = false
        ) where T : UObject
        {
            return UnrealImplementation.Unreal_NewObjectImplementation(Outer.GetHandle(),
                Class.GetHandle(),
                Name?.GetHandle() ?? FName.NAME_None.GetHandle(),
                Flags,
                Template?.GetHandle() ?? IntPtr.Zero,
                bCopyTransientsFromClassDefaults) as T;
        }

        public static T NewObject<T>(UObject Outer,
            FName Name = null,
            EObjectFlags Flags = EObjectFlags.RF_NoFlags,
            UObject Template = null,
            Boolean bCopyTransientsFromClassDefaults = false
        ) where T : UObject, IStaticClass
        {
            return NewObject<T>(Outer,
                T.StaticClass(),
                Name,
                Flags,
                Template,
                bCopyTransientsFromClassDefaults);
        }

        public static T DuplicateObject<T>(UObject SourceObject, UObject Outer, FName Name = null) where T : UObject
        {
            return UnrealImplementation.Unreal_DuplicateObjectImplementation(SourceObject.GetHandle(),
                Outer.GetHandle(),
                Name?.GetHandle() ?? FName.NAME_None.GetHandle()) as T;
        }

        public static T LoadObject<T>(UObject Outer,
            FString Name,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null
        ) where T : UObject
        {
            return UnrealImplementation.Unreal_LoadObjectImplementation(Outer.GetHandle(),
                Name?.GetHandle() ?? IntPtr.Zero,
                Filename?.GetHandle() ?? IntPtr.Zero,
                LoadFlags,
                Sandbox?.GetHandle() ?? IntPtr.Zero) as T;
        }

        public static T LoadObject<T>(UObject Outer,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null
        ) where T : UObject
        {
            return LoadObject<T>(Outer,
                Utils.GetPathName(typeof(T)),
                Filename,
                LoadFlags,
                Sandbox);
        }

        public static UClass LoadClass(UObject Outer,
            FString Name = null,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null)
        {
            return UnrealImplementation.Unreal_LoadClassImplementation(Outer.GetHandle(),
                Name?.GetHandle() ?? IntPtr.Zero,
                Filename?.GetHandle() ?? IntPtr.Zero,
                LoadFlags,
                Sandbox?.GetHandle() ?? IntPtr.Zero);
        }

        public static T CreateWidget<T>(UWidget OwningObject) where T : UUserWidget, IStaticClass
        {
            return UnrealImplementation.Unreal_CreateWidgetImplementation(OwningObject.GetHandle(),
                T.StaticClass().GetHandle()) as T;
        }

        public static T CreateWidget<T>(UWidgetTree OwningObject) where T : UUserWidget, IStaticClass
        {
            return UnrealImplementation.Unreal_CreateWidgetImplementation(OwningObject.GetHandle(),
                T.StaticClass().GetHandle()) as T;
        }

        public static T CreateWidget<T>(APlayerController OwningObject) where T : UUserWidget, IStaticClass
        {
            return UnrealImplementation.Unreal_CreateWidgetImplementation(OwningObject.GetHandle(),
                T.StaticClass().GetHandle()) as T;
        }

        public static T CreateWidget<T>(UGameInstance OwningObject) where T : UUserWidget, IStaticClass
        {
            return UnrealImplementation.Unreal_CreateWidgetImplementation(OwningObject.GetHandle(),
                T.StaticClass().GetHandle()) as T;
        }

        public static T CreateWidget<T>(UWorld OwningObject) where T : UUserWidget, IStaticClass
        {
            return UnrealImplementation.Unreal_CreateWidgetImplementation(OwningObject.GetHandle(),
                T.StaticClass().GetHandle()) as T;
        }

        public static UWorld GWorld => UnrealImplementation.Unreal_GWorldImplementation();
    }
}