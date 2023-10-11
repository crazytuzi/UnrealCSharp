using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Reflection.Container;

namespace Script.Common
{
    public class TMap<TKey, TValue> : IGCHandle, IEnumerable<KeyValuePair<TKey, TValue>>
    {
        public TMap() => MapUtils.Map_Register(this);

        public TMap(Type InKeyType, Type InValueType)
        {
        }

        ~TMap() => MapUtils.Map_UnRegister(GCHandle);

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator ==(TMap<TKey, TValue> A, TMap<TKey, TValue> B) => false;

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator !=(TMap<TKey, TValue> A, TMap<TKey, TValue> B) => false;

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

        public void Empty(Int32 InExpectedNumElements = 0) => MapUtils.Map_Empty(GCHandle, InExpectedNumElements);

        public Int32 Num() => MapUtils.Map_Num(GCHandle);

        public void Add(TKey InKey, TValue InValue) => MapUtils.Map_Add(GCHandle, InKey, InValue);

        public Int32 Remove(TKey InKey) => MapUtils.Map_Remove<TKey, TValue>(GCHandle, InKey);

        public TKey FindKey(TValue InValue) => MapUtils.Map_FindKey<TKey, TValue>(GCHandle, InValue);

        public TValue Find(TKey InKey) => MapUtils.Map_Find<TKey, TValue>(GCHandle, InKey);

        public Boolean Contains(TKey InKey) => MapUtils.Map_Contains<TKey, TValue>(GCHandle, InKey);

        public TValue this[TKey InKey]
        {
            get => MapUtils.Map_Get<TKey, TValue>(GCHandle, InKey);

            set => MapUtils.Map_Set(GCHandle, InKey, value);
        }

        private Int32 GetMaxIndex() => MapUtils.Map_GetMaxIndex(GCHandle);

        private Boolean IsValidIndex(Int32 InIndex) => MapUtils.Map_IsValidIndex(GCHandle, InIndex);

        private TKey GetEnumeratorKey(Int32 InIndex) => MapUtils.Map_GetEnumeratorKey<TKey, TValue>(GCHandle, InIndex);

        private TValue GetEnumeratorValue(Int32 InIndex) =>
            MapUtils.Map_GetEnumeratorValue<TKey, TValue>(GCHandle, InIndex);

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