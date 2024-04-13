using System.Collections;
using System.Collections.Generic;
using Script.Library;

namespace Script.CoreUObject
{
    public class TMap<TKey, TValue> : IEnumerable<KeyValuePair<TKey, TValue>>, IGarbageCollectionHandle
    {
        public TMap() => TMapImplementation.TMap_RegisterImplementation(this);

        ~TMap() => TMapImplementation.TMap_UnRegisterImplementation(GarbageCollectionHandle);

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
            TMapImplementation.TMap_EmptyImplementation(GarbageCollectionHandle, InExpectedNumElements);

        public int Num() => TMapImplementation.TMap_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => TMapImplementation.TMap_IsEmptyImplementation(GarbageCollectionHandle);

        public void Add(TKey InKey, TValue InValue) =>
            TMapImplementation.TMap_AddImplementation(GarbageCollectionHandle, InKey, InValue);

        public int Remove(TKey InKey) => TMapImplementation.TMap_RemoveImplementation(GarbageCollectionHandle, InKey);

        public TKey FindKey(TValue InValue) =>
            (TKey)TMapImplementation.TMap_FindKeyImplementation(GarbageCollectionHandle, InValue);

        public TValue Find(TKey InKey) =>
            (TValue)TMapImplementation.TMap_FindImplementation(GarbageCollectionHandle, InKey);

        public bool Contains(TKey InKey) =>
            TMapImplementation.TMap_ContainsImplementation(GarbageCollectionHandle, InKey);

        public TValue this[TKey InKey]
        {
            get => (TValue)TMapImplementation.TMap_GetImplementation(GarbageCollectionHandle, InKey);

            set => TMapImplementation.TMap_SetImplementation(GarbageCollectionHandle, InKey, value);
        }

        private int GetMaxIndex() => TMapImplementation.TMap_GetMaxIndexImplementation(GarbageCollectionHandle);

        private bool IsValidIndex(int InIndex) =>
            TMapImplementation.TMap_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        private TKey GetEnumeratorKey(int InIndex) =>
            (TKey)TMapImplementation.TMap_GetEnumeratorKeyImplementation(GarbageCollectionHandle, InIndex);

        private TValue GetEnumeratorValue(int InIndex) =>
            (TValue)TMapImplementation.TMap_GetEnumeratorValueImplementation(GarbageCollectionHandle, InIndex);

        public nint GarbageCollectionHandle { get; set; }
    }
}