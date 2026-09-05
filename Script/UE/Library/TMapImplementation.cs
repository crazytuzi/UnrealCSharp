using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static unsafe partial class TMapImplementation
    {
        private static unsafe partial void __TMap_RegisterImplementation(nint InMap, nint InType);

        public static void TMap_RegisterImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, Type InType)
        {
            __TMap_RegisterImplementation(HandleData.Alloc(InMap), HandleData.Alloc(InType));
        }

        private static unsafe partial void __TMap_UnRegisterImplementation(nint InMap);

        public static void TMap_UnRegisterImplementation(nint InMap)
        {
            __TMap_UnRegisterImplementation(InMap);
        }

        private static unsafe partial void __TMap_EmptyImplementation(nint InMap, int InExpectedNumElements);

        public static void TMap_EmptyImplementation(nint InMap, int InExpectedNumElements)
        {
            __TMap_EmptyImplementation(InMap, InExpectedNumElements);
        }

        private static unsafe partial int __TMap_NumImplementation(nint InMap);

        public static int TMap_NumImplementation(nint InMap)
        {
            return __TMap_NumImplementation(InMap);
        }

        private static unsafe partial byte __TMap_IsEmptyImplementation(nint InMap);

        public static bool TMap_IsEmptyImplementation(nint InMap)
        {
            return __TMap_IsEmptyImplementation(InMap) != 0;
        }

        private static unsafe partial int __TMap_GetMaxIndexImplementation(nint InMap);

        public static int TMap_GetMaxIndexImplementation(nint InMap)
        {
            return __TMap_GetMaxIndexImplementation(InMap);
        }

        private static unsafe partial byte __TMap_IsValidIndexImplementation(nint InMap, int InIndex);

        public static bool TMap_IsValidIndexImplementation(nint InMap, int InIndex)
        {
            return __TMap_IsValidIndexImplementation(InMap, InIndex) != 0;
        }

        private static unsafe partial void __TMap_AddImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer);

        public static void TMap_AddImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer)
        {
            __TMap_AddImplementation(InMap, InKeyBuffer, InValueBuffer);
        }

        private static unsafe partial int __TMap_RemoveImplementation(nint InMap, byte* InKeyBuffer);

        public static int TMap_RemoveImplementation(nint InMap, byte* InKeyBuffer)
        {
            return __TMap_RemoveImplementation(InMap, InKeyBuffer);
        }

        private static unsafe partial byte __TMap_ContainsImplementation(nint InMap, byte* InKeyBuffer);

        public static bool TMap_ContainsImplementation(nint InMap, byte* InKeyBuffer)
        {
            return __TMap_ContainsImplementation(InMap, InKeyBuffer) != 0;
        }

        private static unsafe partial void __TMap_FindKeyImplementation(nint InMap, byte* InValueBuffer, byte* ReturnBuffer);

        public static void TMap_FindKeyImplementation(nint InMap, byte* InValueBuffer, byte* ReturnBuffer)
        {
            __TMap_FindKeyImplementation(InMap, InValueBuffer, ReturnBuffer);
        }

        private static unsafe partial void __TMap_FindImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer);

        public static void TMap_FindImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer)
        {
            __TMap_FindImplementation(InMap, InKeyBuffer, ReturnBuffer);
        }

        private static unsafe partial void __TMap_GetImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer);

        public static void TMap_GetImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer)
        {
            __TMap_GetImplementation(InMap, InKeyBuffer, ReturnBuffer);
        }

        private static unsafe partial void __TMap_SetImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer);

        public static void TMap_SetImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer)
        {
            __TMap_SetImplementation(InMap, InKeyBuffer, InValueBuffer);
        }

        private static unsafe partial void __TMap_GetEnumeratorKeyImplementation(nint InMap, int InIndex, byte* ReturnBuffer);

        public static void TMap_GetEnumeratorKeyImplementation(nint InMap, int InIndex, byte* ReturnBuffer)
        {
            __TMap_GetEnumeratorKeyImplementation(InMap, InIndex, ReturnBuffer);
        }

        private static unsafe partial void __TMap_GetEnumeratorValueImplementation(nint InMap, int InIndex, byte* ReturnBuffer);

        public static void TMap_GetEnumeratorValueImplementation(nint InMap, int InIndex, byte* ReturnBuffer)
        {
            __TMap_GetEnumeratorValueImplementation(InMap, InIndex, ReturnBuffer);
        }

        public static TKey TMap_FindKeyCompoundImplementation<TKey>(nint InMap, byte* InValueBuffer)
        {
            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_FindKeyImplementation(InMap, InValueBuffer, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TKey)HandleData.GetObject(Handle) : default;
        }

        public static TValue TMap_FindCompoundImplementation<TValue>(nint InMap, byte* InKeyBuffer)
        {
            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_FindImplementation(InMap, InKeyBuffer, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TValue)HandleData.GetObject(Handle) : default;
        }

        public static TValue TMap_GetCompoundImplementation<TValue>(nint InMap, byte* InKeyBuffer)
        {
            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_GetImplementation(InMap, InKeyBuffer, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TValue)HandleData.GetObject(Handle) : default;
        }

        public static TKey TMap_GetEnumeratorKeyCompoundImplementation<TKey>(nint InMap, int InIndex)
        {
            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_GetEnumeratorKeyImplementation(InMap, InIndex, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TKey)HandleData.GetObject(Handle) : default;
        }

        public static TValue TMap_GetEnumeratorValueCompoundImplementation<TValue>(nint InMap, int InIndex)
        {
            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_GetEnumeratorValueImplementation(InMap, InIndex, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TValue)HandleData.GetObject(Handle) : default;
        }
    }
}