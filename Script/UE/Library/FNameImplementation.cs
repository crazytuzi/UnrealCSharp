using System.Text;
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class FNameImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FName_RegisterImplementation(FName InName, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FName_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FName_UnRegisterImplementation(nint InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FName_ToStringImplementation(nint InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FName FName_NAME_NoneImplementation();
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, void> __FName_RegisterImplementation;

        public static unsafe void FName_RegisterImplementation(FName InName, string InValue)
        {
            if (__FName_RegisterImplementation == null)
            {
                __FName_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.FNameImplementation::FName_RegisterImplementation");
            }

            var Handle = HandleData.AllocImplementation(InName);

            InName.GarbageCollectionHandle = Handle;

            var UTF8 = InValue != null ? Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FName_RegisterImplementation(Handle, Ptr);
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __FName_IdenticalImplementation;

        public static unsafe bool FName_IdenticalImplementation(nint InA, nint InB)
        {
            if (__FName_IdenticalImplementation == null)
            {
                __FName_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.FNameImplementation::FName_IdenticalImplementation");
            }

            return __FName_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __FName_UnRegisterImplementation;

        public static unsafe void FName_UnRegisterImplementation(nint InName)
        {
            if (__FName_UnRegisterImplementation == null)
            {
                __FName_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FNameImplementation::FName_UnRegisterImplementation");
            }

            __FName_UnRegisterImplementation(InName);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __FName_ToStringImplementation;

        public static unsafe string FName_ToStringImplementation(nint InName)
        {
            if (__FName_ToStringImplementation == null)
            {
                __FName_ToStringImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod("Script.Library.FNameImplementation::FName_ToStringImplementation");
            }

            var Handle = __FName_ToStringImplementation(InName);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint> __FName_NAME_NoneImplementation;

        public static unsafe FName FName_NAME_NoneImplementation()
        {
            if (__FName_NAME_NoneImplementation == null)
            {
                __FName_NAME_NoneImplementation = (delegate* unmanaged[Cdecl]<nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.FNameImplementation::FName_NAME_NoneImplementation");
            }

            var Handle = __FName_NAME_NoneImplementation();

            return Handle != 0 ? (FName)HandleData.GetObject(Handle) : null;
        }
#endif
    }
}