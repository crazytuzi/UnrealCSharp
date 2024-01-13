using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TMap<TKey, TValue> : IGarbageCollectionHandle, IEnumerable<KeyValuePair<TKey, TValue>>
    {
        public TMap() => MapImplementation.Map_RegisterImplementation(this);

        ~TMap() => MapImplementation.Map_UnRegisterImplementation(GarbageCollectionHandle);

        [Obsolete("It is not supported like UE.", true)]
        public static bool operator ==(TMap<TKey, TValue> A, TMap<TKey, TValue> B) => false;

        [Obsolete("It is not supported like UE.", true)]
        public static bool operator !=(TMap<TKey, TValue> A, TMap<TKey, TValue> B) => false;

        public override bool Equals(object Other) => false;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

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

        public void Empty(int InExpectedNumElements = 0) =>
            MapImplementation.Map_EmptyImplementation(GarbageCollectionHandle, InExpectedNumElements);

        public int Num() => MapImplementation.Map_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => MapImplementation.Map_IsEmptyImplementation(GarbageCollectionHandle);

        public void Add(TKey InKey, TValue InValue) =>
            MapImplementation.Map_AddImplementation(GarbageCollectionHandle, InKey, InValue);

        public int Remove(TKey InKey) => MapImplementation.Map_RemoveImplementation(GarbageCollectionHandle, InKey);

        public TKey FindKey(TValue InValue) => (TKey)MapImplementation.Map_FindKeyImplementation(GarbageCollectionHandle, InValue);

        public TValue Find(TKey InKey) => (TValue)MapImplementation.Map_FindImplementation(GarbageCollectionHandle, InKey);

        public bool Contains(TKey InKey) => MapImplementation.Map_ContainsImplementation(GarbageCollectionHandle, InKey);

        public TValue this[TKey InKey]
        {
            get => (TValue)MapImplementation.Map_GetImplementation(GarbageCollectionHandle, InKey);

            set => MapImplementation.Map_SetImplementation(GarbageCollectionHandle, InKey, value);
        }

        private int GetMaxIndex() => MapImplementation.Map_GetMaxIndexImplementation(GarbageCollectionHandle);

        private bool IsValidIndex(int InIndex) =>
            MapImplementation.Map_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        private TKey GetEnumeratorKey(int InIndex) =>
            (TKey)MapImplementation.Map_GetEnumeratorKeyImplementation(GarbageCollectionHandle, InIndex);

        private TValue GetEnumeratorValue(int InIndex) =>
            (TValue)MapImplementation.Map_GetEnumeratorValueImplementation(GarbageCollectionHandle, InIndex);

        public nint GarbageCollectionHandle { get; set; }
    }
}