using Script.CoreUObject;
using Script.Engine;
using Interop;

namespace Script.Library
{
    public static partial class UnrealImplementation
    {
        private static unsafe partial nint __Unreal_NewObjectImplementation(nint Outer, nint Class, nint Name, EObjectFlags Flags, nint Template, byte bCopyTransientsFromClassDefaults);

        public static unsafe T Unreal_NewObjectImplementation<T>(nint Outer, nint Class, nint Name, EObjectFlags Flags,
            nint Template, bool bCopyTransientsFromClassDefaults)
        {
            var Handle = __Unreal_NewObjectImplementation(Outer, Class, Name, Flags, Template,
                (byte)(bCopyTransientsFromClassDefaults ? 1 : 0));

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe partial nint __Unreal_DuplicateObjectImplementation(nint SourceObject, nint Outer, nint Name);

        public static unsafe T Unreal_DuplicateObjectImplementation<T>(nint SourceObject, nint Outer, nint Name)
        {
            var Handle = __Unreal_DuplicateObjectImplementation(SourceObject, Outer, Name);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe partial nint __Unreal_LoadObjectImplementation(nint Outer, nint Name, nint Filename, ELoadFlags LoadFlags, nint Sandbox);

        public static unsafe T Unreal_LoadObjectImplementation<T>(nint Outer, nint Name, nint Filename,
            ELoadFlags LoadFlags, nint Sandbox)
        {
            var Handle = __Unreal_LoadObjectImplementation(Outer, Name, Filename, LoadFlags, Sandbox);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe partial nint __Unreal_LoadClassImplementation(nint Outer, nint Name, nint Filename, ELoadFlags LoadFlags, nint Sandbox);

        public static unsafe UClass Unreal_LoadClassImplementation(nint Outer, nint Name, nint Filename,
            ELoadFlags LoadFlags, nint Sandbox)
        {
            var Handle = __Unreal_LoadClassImplementation(Outer, Name, Filename, LoadFlags, Sandbox);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __Unreal_CreateWidgetImplementation(nint OwningObject, nint UserWidgetClass);

        public static unsafe T Unreal_CreateWidgetImplementation<T>(nint OwningObject, nint UserWidgetClass)
        {
            var Handle = __Unreal_CreateWidgetImplementation(OwningObject, UserWidgetClass);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe partial nint __Unreal_GWorldImplementation();

        public static unsafe UWorld Unreal_GWorldImplementation()
        {
            var Handle = __Unreal_GWorldImplementation();

            return Handle != 0 ? (UWorld)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __Unreal_GetTransientPackageImplementation();

        public static unsafe UPackage Unreal_GetTransientPackageImplementation()
        {
            var Handle = __Unreal_GetTransientPackageImplementation();

            return Handle != 0 ? (UPackage)HandleData.GetObject(Handle) : null;
        }
    }
}