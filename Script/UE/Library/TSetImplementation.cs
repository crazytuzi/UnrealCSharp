using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static unsafe partial class TSetImplementation
    {
        private static unsafe partial void __TSet_RegisterImplementation(nint InSet, nint InType);

        public static void TSet_RegisterImplementation<T>(TSet<T> InSet, Type InType)
        {
            __TSet_RegisterImplementation(HandleData.Alloc(InSet), HandleData.Alloc(InType));
        }

        private static unsafe partial void __TSet_UnRegisterImplementation(nint InSet);

        public static void TSet_UnRegisterImplementation(nint InSet)
        {
            __TSet_UnRegisterImplementation(InSet);
        }

        private static unsafe partial void __TSet_EmptyImplementation(nint InSet, int InExpectedNumElements);

        public static void TSet_EmptyImplementation(nint InSet, int InExpectedNumElements)
        {
            __TSet_EmptyImplementation(InSet, InExpectedNumElements);
        }

        private static unsafe partial int __TSet_NumImplementation(nint InSet);

        public static int TSet_NumImplementation(nint InSet)
        {
            return __TSet_NumImplementation(InSet);
        }

        private static unsafe partial byte __TSet_IsEmptyImplementation(nint InSet);

        public static bool TSet_IsEmptyImplementation(nint InSet)
        {
            return __TSet_IsEmptyImplementation(InSet) != 0;
        }

        private static unsafe partial int __TSet_GetMaxIndexImplementation(nint InSet);

        public static int TSet_GetMaxIndexImplementation(nint InSet)
        {
            return __TSet_GetMaxIndexImplementation(InSet);
        }

        private static unsafe partial byte __TSet_IsValidIndexImplementation(nint InSet, int InIndex);

        public static bool TSet_IsValidIndexImplementation(nint InSet, int InIndex)
        {
            return __TSet_IsValidIndexImplementation(InSet, InIndex) != 0;
        }

        private static unsafe partial void __TSet_AddImplementation(nint InSet, byte* InValueBuffer);

        public static void TSet_AddImplementation(nint InSet, byte* InValueBuffer)
        {
            __TSet_AddImplementation(InSet, InValueBuffer);
        }

        private static unsafe partial int __TSet_RemoveImplementation(nint InSet, byte* InValueBuffer);

        public static int TSet_RemoveImplementation(nint InSet, byte* InValueBuffer)
        {
            return __TSet_RemoveImplementation(InSet, InValueBuffer);
        }

        private static unsafe partial byte __TSet_ContainsImplementation(nint InSet, byte* InValueBuffer);

        public static bool TSet_ContainsImplementation(nint InSet, byte* InValueBuffer)
        {
            return __TSet_ContainsImplementation(InSet, InValueBuffer) != 0;
        }

        private static unsafe partial void __TSet_GetEnumeratorImplementation(nint InSet, int InIndex, byte* ReturnBuffer);

        public static void TSet_GetEnumeratorImplementation(nint InSet, int InIndex, byte* ReturnBuffer)
        {
            __TSet_GetEnumeratorImplementation(InSet, InIndex, ReturnBuffer);
        }

        public static T TSet_GetEnumeratorCompoundImplementation<T>(nint InSet, int InIndex)
        {
            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TSet_GetEnumeratorImplementation(InSet, InIndex, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}