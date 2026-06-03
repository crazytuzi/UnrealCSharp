#if UE_5_6_OR_LATER
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class FAnsiStringImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FAnsiString_RegisterImplementation(FAnsiString InString, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FAnsiString_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FAnsiString_UnRegisterImplementation(nint InString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FAnsiString_ToStringImplementation(nint InString);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, void> __FAnsiString_RegisterImplementation;

        public static unsafe void FAnsiString_RegisterImplementation(FAnsiString InString, string InValue)
        {
            if (__FAnsiString_RegisterImplementation == null)
            {
                __FAnsiString_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_RegisterImplementation");
            }

            var Handle = HandleData.AllocImplementation(InString);

            InString.GarbageCollectionHandle = Handle;

            var UTF8 = InValue != null ? System.Text.Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FAnsiString_RegisterImplementation(Handle, Ptr);
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __FAnsiString_IdenticalImplementation;

        public static unsafe bool FAnsiString_IdenticalImplementation(nint InA, nint InB)
        {
            if (__FAnsiString_IdenticalImplementation == null)
            {
                __FAnsiString_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_IdenticalImplementation");
            }

            return __FAnsiString_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __FAnsiString_UnRegisterImplementation;

        public static unsafe void FAnsiString_UnRegisterImplementation(nint InString)
        {
            if (__FAnsiString_UnRegisterImplementation == null)
            {
                __FAnsiString_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_UnRegisterImplementation");
            }

            __FAnsiString_UnRegisterImplementation(InString);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __FAnsiString_ToStringImplementation;

        public static unsafe string FAnsiString_ToStringImplementation(nint InString)
        {
            if (__FAnsiString_ToStringImplementation == null)
            {
                __FAnsiString_ToStringImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_ToStringImplementation");
            }

            var Handle = __FAnsiString_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
#endif
    }
}
#endif