using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class GuidImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_EqualityImplementation(FGuid A, FGuid B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_InequalityImplementation(FGuid A, FGuid B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_LessThanImplementation(FGuid A, FGuid B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_GreaterThanImplementation(FGuid A, FGuid B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Guid_GetComponentImplementation(FGuid InGuid, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_SetComponentImplementation(FGuid InGuid, Int32 InIndex, UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_LexToStringImplementation(FGuid Value, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_InvalidateImplementation(FGuid Value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_IsValidImplementation(FGuid Value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_ToStringImplementation(FGuid InGuid, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Guid_NewGuidImplementation(out FGuid OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Guid_ParseImplementation(FString GuidString, out FGuid OutGuid);
    }
}