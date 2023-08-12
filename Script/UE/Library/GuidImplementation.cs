using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class GuidImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_LessThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_GreaterThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Guid_GetComponentImplementation(IntPtr InGuid, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_SetComponentImplementation(IntPtr InGuid, Int32 InIndex, UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_LexToStringImplementation(FGuid Value, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_InvalidateImplementation(IntPtr Value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_IsValidImplementation(IntPtr Value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_ToStringImplementation(IntPtr InGuid, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_NewGuidImplementation(out FGuid OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_ParseImplementation(FString GuidString, out FGuid OutGuid);
    }
}