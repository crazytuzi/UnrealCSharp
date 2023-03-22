using System;
using System.Collections;
using System.Collections.Generic;
using Script.Reflection.Container;

namespace Script.Common
{
    public class TMap<TKey, TValue> : IEnumerable<KeyValuePair<TKey, TValue>>
    {
        public TMap() => MapUtils.Map_Register(this);

        public TMap(Type InKeyType, Type InValueType)
        {
        }

        ~TMap() => MapUtils.Map_UnRegister(this);

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

        public void Empty(Int32 InExpectedNumElements = 0) => MapUtils.Map_Empty(this, InExpectedNumElements);

        public Int32 Num() => MapUtils.Map_Num(this);

        public void Add(TKey InKey, TValue InValue) => MapUtils.Map_Add(this, InKey, InValue);

        public Int32 Remove(TKey InKey) => MapUtils.Map_Remove(this, InKey);

        public TKey FindKey(TValue InValue) => MapUtils.Map_FindKey(this, InValue);

        public TValue Find(TKey InKey) => MapUtils.Map_Find(this, InKey);

        public Boolean Contains(TKey InKey) => MapUtils.Map_Contains(this, InKey);

        public TValue this[TKey InKey]
        {
            get => MapUtils.Map_Get(this, InKey);

            set => MapUtils.Map_Set(this, InKey, value);
        }

        private Int32 GetMaxIndex() => MapUtils.Map_GetMaxIndex(this);

        private Boolean IsValidIndex(Int32 InIndex) => MapUtils.Map_IsValidIndex(this, InIndex);

        private TKey GetEnumeratorKey(Int32 InIndex) => MapUtils.Map_GetEnumeratorKey(this, InIndex);

        private TValue GetEnumeratorValue(Int32 InIndex) => MapUtils.Map_GetEnumeratorValue(this, InIndex);
    }
}