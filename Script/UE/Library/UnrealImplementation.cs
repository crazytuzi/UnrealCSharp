using Script.CoreUObject;
using Script.Engine;
using Interop;

namespace Script.Library
{
    public static class UnrealImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, EObjectFlags, nint, byte, nint>
            __Unreal_NewObjectImplementation;

        public static unsafe T Unreal_NewObjectImplementation<T>(nint Outer, nint Class, nint Name, EObjectFlags Flags,
            nint Template, bool bCopyTransientsFromClassDefaults)
        {
            if (__Unreal_NewObjectImplementation == null)
            {
                __Unreal_NewObjectImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint, EObjectFlags, nint, byte, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UnrealImplementation::Unreal_NewObjectImplementation");
            }

            var Handle = __Unreal_NewObjectImplementation(Outer, Class, Name, Flags, Template,
                (byte)(bCopyTransientsFromClassDefaults ? 1 : 0));

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint> __Unreal_DuplicateObjectImplementation;

        public static unsafe T Unreal_DuplicateObjectImplementation<T>(nint SourceObject, nint Outer, nint Name)
        {
            if (__Unreal_DuplicateObjectImplementation == null)
            {
                __Unreal_DuplicateObjectImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UnrealImplementation::Unreal_DuplicateObjectImplementation");
            }

            var Handle = __Unreal_DuplicateObjectImplementation(SourceObject, Outer, Name);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, ELoadFlags, nint, nint>
            __Unreal_LoadObjectImplementation;

        public static unsafe T Unreal_LoadObjectImplementation<T>(nint Outer, nint Name, nint Filename,
            ELoadFlags LoadFlags, nint Sandbox)
        {
            if (__Unreal_LoadObjectImplementation == null)
            {
                __Unreal_LoadObjectImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint, ELoadFlags, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UnrealImplementation::Unreal_LoadObjectImplementation");
            }

            var Handle = __Unreal_LoadObjectImplementation(Outer, Name, Filename, LoadFlags, Sandbox);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, ELoadFlags, nint, nint>
            __Unreal_LoadClassImplementation;

        public static unsafe UClass Unreal_LoadClassImplementation(nint Outer, nint Name, nint Filename,
            ELoadFlags LoadFlags, nint Sandbox)
        {
            if (__Unreal_LoadClassImplementation == null)
            {
                __Unreal_LoadClassImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint, ELoadFlags, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UnrealImplementation::Unreal_LoadClassImplementation");
            }

            var Handle = __Unreal_LoadClassImplementation(Outer, Name, Filename, LoadFlags, Sandbox);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint> __Unreal_CreateWidgetImplementation;

        public static unsafe T Unreal_CreateWidgetImplementation<T>(nint OwningObject, nint UserWidgetClass)
        {
            if (__Unreal_CreateWidgetImplementation == null)
            {
                __Unreal_CreateWidgetImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UnrealImplementation::Unreal_CreateWidgetImplementation");
            }

            var Handle = __Unreal_CreateWidgetImplementation(OwningObject, UserWidgetClass);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint> __Unreal_GWorldImplementation;

        public static unsafe UWorld Unreal_GWorldImplementation()
        {
            if (__Unreal_GWorldImplementation == null)
            {
                __Unreal_GWorldImplementation = (delegate* unmanaged[Cdecl]<nint>)
                    MethodBridge.GetMethod("Script.Library.UnrealImplementation::Unreal_GWorldImplementation");
            }

            var Handle = __Unreal_GWorldImplementation();

            return Handle != 0 ? (UWorld)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint> __Unreal_GetTransientPackageImplementation;

        public static unsafe UPackage Unreal_GetTransientPackageImplementation()
        {
            if (__Unreal_GetTransientPackageImplementation == null)
            {
                __Unreal_GetTransientPackageImplementation = (delegate* unmanaged[Cdecl]<nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UnrealImplementation::Unreal_GetTransientPackageImplementation");
            }

            var Handle = __Unreal_GetTransientPackageImplementation();

            return Handle != 0 ? (UPackage)HandleData.GetObject(Handle) : null;
        }
    }
}