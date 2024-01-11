using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TMap<TKey, TValue> : IGCHandle, IEnumerable<KeyValuePair<TKey, TValue>>
    {
        public TMap() => MapImplementation.Map_RegisterImplementation(this);

        ~TMap() => MapImplementation.Map_UnRegisterImplementation(GCHandle);

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator ==(TMap<TKey, TValue> A, TMap<TKey, TValue> B) => false;

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator !=(TMap<TKey, TValue> A, TMap<TKey, TValue> B) => false;

        public override Boolean Equals(Object Other) => false;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            for (var Index = 0; Index < GetMaxIndex(); Index++)
            {
                if (IsValidIndex(Index))
                {
                    yield return new KeyValuePair<TKey, TValue>(GetEnumeratorKey(Index), GetEnumeratorValue(Index));
                }
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Empty(Int32 InExpectedNumElements = 0) =>
            MapImplementation.Map_EmptyImplementation(GCHandle, InExpectedNumElements);

        public Int32 Num() => MapImplementation.Map_NumImplementation(GCHandle);

        public Boolean IsEmpty() => MapImplementation.Map_IsEmptyImplementation(GCHandle);

        public void Add(TKey InKey, TValue InValue) =>
            MapImplementation.Map_AddImplementation(GCHandle, InKey, InValue);

        public Int32 Remove(TKey InKey) => MapImplementation.Map_RemoveImplementation(GCHandle, InKey);

        public TKey FindKey(TValue InValue) => (TKey)MapImplementation.Map_FindKeyImplementation(GCHandle, InValue);

        public TValue Find(TKey InKey) => (TValue)MapImplementation.Map_FindImplementation(GCHandle, InKey);

        public Boolean Contains(TKey InKey) => MapImplementation.Map_ContainsImplementation(GCHandle, InKey);

        public TValue this[TKey InKey]
        {
            get => (TValue)MapImplementation.Map_GetImplementation(GCHandle, InKey);

            set => MapImplementation.Map_SetImplementation(GCHandle, InKey, value);
        }

        private Int32 GetMaxIndex() => MapImplementation.Map_GetMaxIndexImplementation(GCHandle);

        private Boolean IsValidIndex(Int32 InIndex) =>
            MapImplementation.Map_IsValidIndexImplementation(GCHandle, InIndex);

        private TKey GetEnumeratorKey(Int32 InIndex) =>
            (TKey)MapImplementation.Map_GetEnumeratorKeyImplementation(GCHandle, InIndex);

        private TValue GetEnumeratorValue(Int32 InIndex) =>
            (TValue)MapImplementation.Map_GetEnumeratorValueImplementation(GCHandle, InIndex);

        public unsafe void SetHandle(void* InGCHandle)
        {
            GCHandle = new IntPtr(InGCHandle);
        }

        public IntPtr GetHandle()
        {
            return GCHandle;
        }

        private IntPtr GCHandle;
    }
}