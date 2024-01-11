using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class UnrealImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Unreal_NewObjectImplementation(IntPtr Outer,
            IntPtr Class,
            IntPtr Name,
            EObjectFlags Flags,
            IntPtr Template,
            Boolean bCopyTransientsFromClassDefaults
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Unreal_DuplicateObjectImplementation(IntPtr SourceObject,
            IntPtr Outer,
            IntPtr Name
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Unreal_LoadObjectImplementation(IntPtr Outer,
            IntPtr Name,
            IntPtr Filename,
            ELoadFlags LoadFlags,
            IntPtr Sandbox
        );

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass Unreal_LoadClassImplementation(IntPtr Outer, IntPtr Name,
            IntPtr Filename,
            ELoadFlags LoadFlags,
            IntPtr Sandbox);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Unreal_CreateWidgetImplementation(IntPtr OwningObject, IntPtr UserWidgetClass);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UWorld Unreal_GWorldImplementation();
    }
}