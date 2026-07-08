using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class UObjectImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __UObject_IdenticalImplementation;

        public static unsafe bool UObject_IdenticalImplementation(nint InA, nint InB)
        {
            if (__UObject_IdenticalImplementation == null)
            {
                __UObject_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_IdenticalImplementation");
            }

            return __UObject_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<byte*, nint> __UObject_StaticClassImplementation;

        public static unsafe UClass UObject_StaticClassImplementation(string InClassName)
        {
            if (__UObject_StaticClassImplementation == null)
            {
                __UObject_StaticClassImplementation = (delegate* unmanaged[Cdecl]<byte*, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_StaticClassImplementation");
            }

            nint Handle;

            var UTF8 = InClassName != null ? Encoding.UTF8.GetBytes(InClassName + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                Handle = __UObject_StaticClassImplementation(Ptr);
            }

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __UObject_GetClassImplementation;

        public static unsafe UClass UObject_GetClassImplementation(nint InObject)
        {
            if (__UObject_GetClassImplementation == null)
            {
                __UObject_GetClassImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_GetClassImplementation");
            }

            var Handle = __UObject_GetClassImplementation(InObject);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __UObject_GetNameImplementation;

        public static unsafe string UObject_GetNameImplementation(nint InObject)
        {
            if (__UObject_GetNameImplementation == null)
            {
                __UObject_GetNameImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_GetNameImplementation");
            }

            var Handle = __UObject_GetNameImplementation(InObject);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, byte> __UObject_IsValidImplementation;

        public static unsafe bool UObject_IsValidImplementation(nint InObject)
        {
            if (__UObject_IsValidImplementation == null)
            {
                __UObject_IsValidImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_IsValidImplementation");
            }

            return __UObject_IsValidImplementation(InObject) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __UObject_IsAImplementation;

        public static unsafe bool UObject_IsAImplementation(nint InObject, nint SomeBase)
        {
            if (__UObject_IsAImplementation == null)
            {
                __UObject_IsAImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod("Script.Library.UObjectImplementation::UObject_IsAImplementation");
            }

            return __UObject_IsAImplementation(InObject, SomeBase) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __UObject_AddToRootImplementation;

        public static unsafe void UObject_AddToRootImplementation(nint InObject)
        {
            if (__UObject_AddToRootImplementation == null)
            {
                __UObject_AddToRootImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_AddToRootImplementation");
            }

            __UObject_AddToRootImplementation(InObject);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __UObject_RemoveFromRootImplementation;

        public static unsafe void UObject_RemoveFromRootImplementation(nint InObject)
        {
            if (__UObject_RemoveFromRootImplementation == null)
            {
                __UObject_RemoveFromRootImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_RemoveFromRootImplementation");
            }

            __UObject_RemoveFromRootImplementation(InObject);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, byte> __UObject_IsRootedImplementation;

        public static unsafe bool UObject_IsRootedImplementation(nint InObject)
        {
            if (__UObject_IsRootedImplementation == null)
            {
                __UObject_IsRootedImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_IsRootedImplementation");
            }

            return __UObject_IsRootedImplementation(InObject) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, byte> __UObject_AddReferenceImplementation;

        public static unsafe bool UObject_AddReferenceImplementation(nint InObject)
        {
            if (__UObject_AddReferenceImplementation == null)
            {
                __UObject_AddReferenceImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_AddReferenceImplementation");
            }

            return __UObject_AddReferenceImplementation(InObject) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, byte> __UObject_RemoveReferenceImplementation;

        public static unsafe bool UObject_RemoveReferenceImplementation(nint InObject)
        {
            if (__UObject_RemoveReferenceImplementation == null)
            {
                __UObject_RemoveReferenceImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UObjectImplementation::UObject_RemoveReferenceImplementation");
            }

            return __UObject_RemoveReferenceImplementation(InObject) != 0;
        }
    }
}