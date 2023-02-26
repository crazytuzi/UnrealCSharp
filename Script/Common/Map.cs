using System;
using Script.Reflection.Container;

namespace Script.Common
{
    public class TMap<TKey, TValue>
    {
        public TMap() => MapUtils.Map_Register(this, typeof(TKey), typeof(TValue));

        public TMap(Type InKeyType, Type InValueType)
        {
        }

        ~TMap() => MapUtils.Map_UnRegister(this);

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
    }
}