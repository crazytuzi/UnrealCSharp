using System;
using Script.Engine;
using Script.Library;
using Script.UMG;
using Interop;

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
                HandleData.GetHandle(Outer) != 0
                    ? HandleData.GetHandle(Outer)
                    : HandleData.GetHandle(GetTransientPackage()),
                HandleData.GetHandle(Class) != 0 ? HandleData.GetHandle(Class) : HandleData.GetHandle(T.StaticClass()),
                HandleData.GetHandle(Name) != 0 ? HandleData.GetHandle(Name) : HandleData.GetHandle(FName.NAME_None),
                Flags,
                HandleData.GetHandle(Template),
                bCopyTransientsFromClassDefaults);

        public static T DuplicateObject<T>(UObject SourceObject, UObject Outer = null, FName Name = null)
            where T : UObject =>
            UnrealImplementation.Unreal_DuplicateObjectImplementation<T>(
                HandleData.GetHandle(SourceObject),
                HandleData.GetHandle(Outer),
                HandleData.GetHandle(Name) != 0 ? HandleData.GetHandle(Name) : HandleData.GetHandle(FName.NAME_None));

        public static T LoadObject<T>(UObject Outer = null,
            FString Name = null,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null
        ) where T : UObject =>
            UnrealImplementation.Unreal_LoadObjectImplementation<T>(
                HandleData.GetHandle(Outer),
                HandleData.GetHandle(Name) != 0
                    ? HandleData.GetHandle(Name)
                    : HandleData.GetHandle(new FString(Utils.GetPathName(typeof(T)))),
                HandleData.GetHandle(Filename),
                LoadFlags,
                HandleData.GetHandle(Sandbox));

        public static UClass LoadClass(UObject Outer,
            FString Name,
            FString Filename = null,
            ELoadFlags LoadFlags = ELoadFlags.LOAD_None,
            UPackageMap Sandbox = null) =>
            UnrealImplementation.Unreal_LoadClassImplementation(
                HandleData.GetHandle(Outer),
                HandleData.GetHandle(Name),
                HandleData.GetHandle(Filename),
                LoadFlags,
                HandleData.GetHandle(Sandbox));

        public static T CreateWidget<T>(UWidget OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(HandleData.GetHandle(OwningObject),
                HandleData.GetHandle(T.StaticClass()));

        public static T CreateWidget<T>(UWidgetTree OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(HandleData.GetHandle(OwningObject),
                HandleData.GetHandle(T.StaticClass()));

        public static T CreateWidget<T>(APlayerController OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(HandleData.GetHandle(OwningObject),
                HandleData.GetHandle(T.StaticClass()));

        public static T CreateWidget<T>(UGameInstance OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(HandleData.GetHandle(OwningObject),
                HandleData.GetHandle(T.StaticClass()));

        public static T CreateWidget<T>(UWorld OwningObject) where T : UUserWidget, IStaticClass =>
            UnrealImplementation.Unreal_CreateWidgetImplementation<T>(HandleData.GetHandle(OwningObject),
                HandleData.GetHandle(T.StaticClass()));

        public static UEnum StaticEnum<T>() where T : Enum
        {
            return LoadObject<UEnum>(null, Utils.GetPathName(typeof(T)));
        }

        public static UWorld GWorld => UnrealImplementation.Unreal_GWorldImplementation();

        public static UPackage GetTransientPackage() => UnrealImplementation.Unreal_GetTransientPackageImplementation();
    }
}