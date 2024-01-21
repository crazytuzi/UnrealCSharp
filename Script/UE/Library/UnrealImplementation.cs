using System.Runtime.CompilerServices;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class UnrealImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Unreal_NewObjectImplementation<T>(nint Outer,
            nint Class,
            nint Name,
            EObjectFlags Flags,
            nint Template,
            bool bCopyTransientsFromClassDefaults
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Unreal_DuplicateObjectImplementation<T>(nint SourceObject,
            nint Outer,
            nint Name
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Unreal_LoadObjectImplementation<T>(nint Outer,
            nint Name,
            nint Filename,
            ELoadFlags LoadFlags,
            nint Sandbox
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass Unreal_LoadClassImplementation(nint Outer,
            nint Name,
            nint Filename,
            ELoadFlags LoadFlags,
            nint Sandbox
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Unreal_CreateWidgetImplementation<T>(nint OwningObject, nint UserWidgetClass);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UWorld Unreal_GWorldImplementation();
    }
}