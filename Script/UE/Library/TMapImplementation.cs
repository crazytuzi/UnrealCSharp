using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TMapImplementation
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
        public static extern void TMap_AddImplementation(nint InMap, object InKey, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TMap_RemoveImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TMap_FindKeyImplementation(nint InMap, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TMap_FindImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TMap_ContainsImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TMap_GetImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TMap_SetImplementation(nint InMap, object InKey, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TMap_GetMaxIndexImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TMap_IsValidIndexImplementation(nint InMap, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TMap_GetEnumeratorKeyImplementation(nint InMap, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TMap_GetEnumeratorValueImplementation(nint InMap, int InIndex);
    }
}