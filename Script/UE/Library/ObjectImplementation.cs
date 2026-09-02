using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class UObjectImplementation
    {
        private static unsafe partial byte __UObject_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool UObject_IdenticalImplementation(nint InA, nint InB)
        {
            return __UObject_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial nint __UObject_StaticClassImplementation(byte* InClassName);

        public static unsafe UClass UObject_StaticClassImplementation(string InClassName)
        {
            nint Handle;

            var UTF8 = InClassName != null ? Encoding.UTF8.GetBytes(InClassName + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                Handle = __UObject_StaticClassImplementation(Ptr);
            }

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __UObject_GetClassImplementation(nint InObject);

        public static unsafe UClass UObject_GetClassImplementation(nint InObject)
        {
            var Handle = __UObject_GetClassImplementation(InObject);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __UObject_GetNameImplementation(nint InObject);

        public static unsafe string UObject_GetNameImplementation(nint InObject)
        {
            var Handle = __UObject_GetNameImplementation(InObject);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial byte __UObject_IsValidImplementation(nint InObject);

        public static unsafe bool UObject_IsValidImplementation(nint InObject)
        {
            return __UObject_IsValidImplementation(InObject) != 0;
        }

        private static unsafe partial byte __UObject_IsAImplementation(nint InObject, nint SomeBase);

        public static unsafe bool UObject_IsAImplementation(nint InObject, nint SomeBase)
        {
            return __UObject_IsAImplementation(InObject, SomeBase) != 0;
        }

        private static unsafe partial void __UObject_AddToRootImplementation(nint InObject);

        public static unsafe void UObject_AddToRootImplementation(nint InObject)
        {
            __UObject_AddToRootImplementation(InObject);
        }

        private static unsafe partial void __UObject_RemoveFromRootImplementation(nint InObject);

        public static unsafe void UObject_RemoveFromRootImplementation(nint InObject)
        {
            __UObject_RemoveFromRootImplementation(InObject);
        }

        private static unsafe partial byte __UObject_IsRootedImplementation(nint InObject);

        public static unsafe bool UObject_IsRootedImplementation(nint InObject)
        {
            return __UObject_IsRootedImplementation(InObject) != 0;
        }

        private static unsafe partial byte __UObject_AddReferenceImplementation(nint InObject);

        public static unsafe bool UObject_AddReferenceImplementation(nint InObject)
        {
            return __UObject_AddReferenceImplementation(InObject) != 0;
        }

        private static unsafe partial byte __UObject_RemoveReferenceImplementation(nint InObject);

        public static unsafe bool UObject_RemoveReferenceImplementation(nint InObject)
        {
            return __UObject_RemoveReferenceImplementation(InObject) != 0;
        }
    }
}