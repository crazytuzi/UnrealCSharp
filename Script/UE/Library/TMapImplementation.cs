using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static unsafe class TMapImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_RegisterImplementation<TKey, TValue>(TMap<TKey, TValue> InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_UnRegisterImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_EmptyImplementation(nint InMap, int InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TMap_NumImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TMap_IsEmptyImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_AddImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TMap_RemoveImplementation(nint InMap, byte* InKeyBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_FindKeyImplementation(nint InMap, byte* InValueBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_FindImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TMap_ContainsImplementation(nint InMap, byte* InKeyBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_GetImplementation(nint InMap, byte* InKeyBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_SetImplementation(nint InMap, byte* InKeyBuffer, byte* InValueBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TMap_GetMaxIndexImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TMap_IsValidIndexImplementation(nint InMap, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_GetEnumeratorKeyImplementation(nint InMap, int InIndex, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_GetEnumeratorValueImplementation(nint InMap, int InIndex, byte* ReturnBuffer);
    }
}