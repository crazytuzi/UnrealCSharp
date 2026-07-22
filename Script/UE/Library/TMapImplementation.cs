using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static unsafe class TMapImplementation
    {
        private static delegate* unmanaged[Cdecl]<nint, nint, void> __TMap_RegisterImplementation;

        public static void TMap_RegisterImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, Type InType)
        {
            if (__TMap_RegisterImplementation == null)
            {
                __TMap_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_RegisterImplementation");
            }

            __TMap_RegisterImplementation(HandleData.Alloc(InMap), HandleData.Alloc(InType));
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __TMap_UnRegisterImplementation;

        public static void TMap_UnRegisterImplementation(nint InMap)
        {
            if (__TMap_UnRegisterImplementation == null)
            {
                __TMap_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_UnRegisterImplementation");
            }

            __TMap_UnRegisterImplementation(InMap);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, void> __TMap_EmptyImplementation;

        public static void TMap_EmptyImplementation(nint InMap, int InExpectedNumElements)
        {
            if (__TMap_EmptyImplementation == null)
            {
                __TMap_EmptyImplementation = (delegate* unmanaged[Cdecl]<nint, int, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_EmptyImplementation");
            }

            __TMap_EmptyImplementation(InMap, InExpectedNumElements);
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TMap_NumImplementation;

        public static int TMap_NumImplementation(nint InMap)
        {
            if (__TMap_NumImplementation == null)
            {
                __TMap_NumImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_NumImplementation");
            }

            return __TMap_NumImplementation(InMap);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte> __TMap_IsEmptyImplementation;

        public static bool TMap_IsEmptyImplementation(nint InMap)
        {
            if (__TMap_IsEmptyImplementation == null)
            {
                __TMap_IsEmptyImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_IsEmptyImplementation");
            }

            return __TMap_IsEmptyImplementation(InMap) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TMap_GetMaxIndexImplementation;

        public static int TMap_GetMaxIndexImplementation(nint InMap)
        {
            if (__TMap_GetMaxIndexImplementation == null)
            {
                __TMap_GetMaxIndexImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TMapImplementation::TMap_GetMaxIndexImplementation");
            }

            return __TMap_GetMaxIndexImplementation(InMap);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte> __TMap_IsValidIndexImplementation;

        public static bool TMap_IsValidIndexImplementation(nint InMap, int InIndex)
        {
            if (__TMap_IsValidIndexImplementation == null)
            {
                __TMap_IsValidIndexImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TMapImplementation::TMap_IsValidIndexImplementation");
            }

            return __TMap_IsValidIndexImplementation(InMap, InIndex) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void> __TMap_AddImplementation;

        public static void TMap_AddImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer)
        {
            if (__TMap_AddImplementation == null)
            {
                __TMap_AddImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_AddImplementation");
            }

            __TMap_AddImplementation(InMap, InKeyBuffer, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TMap_RemoveImplementation;

        public static int TMap_RemoveImplementation(nint InMap, byte* InKeyBuffer)
        {
            if (__TMap_RemoveImplementation == null)
            {
                __TMap_RemoveImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_RemoveImplementation");
            }

            return __TMap_RemoveImplementation(InMap, InKeyBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte> __TMap_ContainsImplementation;

        public static bool TMap_ContainsImplementation(nint InMap, byte* InKeyBuffer)
        {
            if (__TMap_ContainsImplementation == null)
            {
                __TMap_ContainsImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_ContainsImplementation");
            }

            return __TMap_ContainsImplementation(InMap, InKeyBuffer) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void> __TMap_FindKeyImplementation;

        public static void TMap_FindKeyImplementation(nint InMap, byte* InValueBuffer, byte* ReturnBuffer)
        {
            if (__TMap_FindKeyImplementation == null)
            {
                __TMap_FindKeyImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_FindKeyImplementation");
            }

            __TMap_FindKeyImplementation(InMap, InValueBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void> __TMap_FindImplementation;

        public static void TMap_FindImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer)
        {
            if (__TMap_FindImplementation == null)
            {
                __TMap_FindImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_FindImplementation");
            }

            __TMap_FindImplementation(InMap, InKeyBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void> __TMap_GetImplementation;

        public static void TMap_GetImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer)
        {
            if (__TMap_GetImplementation == null)
            {
                __TMap_GetImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_GetImplementation");
            }

            __TMap_GetImplementation(InMap, InKeyBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void> __TMap_SetImplementation;

        public static void TMap_SetImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer)
        {
            if (__TMap_SetImplementation == null)
            {
                __TMap_SetImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_SetImplementation");
            }

            __TMap_SetImplementation(InMap, InKeyBuffer, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte*, void> __TMap_GetEnumeratorKeyImplementation;

        public static void TMap_GetEnumeratorKeyImplementation(nint InMap, int InIndex, byte* ReturnBuffer)
        {
            if (__TMap_GetEnumeratorKeyImplementation == null)
            {
                __TMap_GetEnumeratorKeyImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TMapImplementation::TMap_GetEnumeratorKeyImplementation");
            }

            __TMap_GetEnumeratorKeyImplementation(InMap, InIndex, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte*, void>
            __TMap_GetEnumeratorValueImplementation;

        public static void TMap_GetEnumeratorValueImplementation(nint InMap, int InIndex, byte* ReturnBuffer)
        {
            if (__TMap_GetEnumeratorValueImplementation == null)
            {
                __TMap_GetEnumeratorValueImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TMapImplementation::TMap_GetEnumeratorValueImplementation");
            }

            __TMap_GetEnumeratorValueImplementation(InMap, InIndex, ReturnBuffer);
        }

        public static TKey TMap_FindKeyCompoundImplementation<TKey>(nint InMap, byte* InValueBuffer)
        {
            if (__TMap_FindKeyImplementation == null)
            {
                __TMap_FindKeyImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_FindKeyImplementation");
            }

            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_FindKeyImplementation(InMap, InValueBuffer, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TKey)HandleData.GetObject(Handle) : default;
        }

        public static TValue TMap_FindCompoundImplementation<TValue>(nint InMap, byte* InKeyBuffer)
        {
            if (__TMap_FindImplementation == null)
            {
                __TMap_FindImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_FindImplementation");
            }

            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_FindImplementation(InMap, InKeyBuffer, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TValue)HandleData.GetObject(Handle) : default;
        }

        public static TValue TMap_GetCompoundImplementation<TValue>(nint InMap, byte* InKeyBuffer)
        {
            if (__TMap_GetImplementation == null)
            {
                __TMap_GetImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TMapImplementation::TMap_GetImplementation");
            }

            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_GetImplementation(InMap, InKeyBuffer, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TValue)HandleData.GetObject(Handle) : default;
        }

        public static TKey TMap_GetEnumeratorKeyCompoundImplementation<TKey>(nint InMap, int InIndex)
        {
            if (__TMap_GetEnumeratorKeyImplementation == null)
            {
                __TMap_GetEnumeratorKeyImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TMapImplementation::TMap_GetEnumeratorKeyImplementation");
            }

            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_GetEnumeratorKeyImplementation(InMap, InIndex, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TKey)HandleData.GetObject(Handle) : default;
        }

        public static TValue TMap_GetEnumeratorValueCompoundImplementation<TValue>(nint InMap, int InIndex)
        {
            if (__TMap_GetEnumeratorValueImplementation == null)
            {
                __TMap_GetEnumeratorValueImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TMapImplementation::TMap_GetEnumeratorValueImplementation");
            }

            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TMap_GetEnumeratorValueImplementation(InMap, InIndex, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (TValue)HandleData.GetObject(Handle) : default;
        }
    }
}