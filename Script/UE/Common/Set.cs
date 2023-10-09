using System;
using Script.Reflection.Container;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;

namespace Script.Common
{
    public class TSet<T> : IGCHandle, IEnumerable<T>
    {
        public TSet() => SetUtils.Set_Register(this);

        public TSet(Type InValue)
        {
        }

        ~TSet() => SetUtils.Set_UnRegister(GetHandle());

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator ==(TSet<T> A, TSet<T> B) => false;

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator !=(TSet<T> A, TSet<T> B) => false;

        public IEnumerator<T> GetEnumerator()
        {
            for (var Index = 0; Index < Num(); Index++)
            {
                if (IsValidIndex(Index))
                {
                    yield return this[Index];
                }
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            for (var Index = 0; Index < Num(); Index++)
            {
                if (IsValidIndex(Index))
                {
                    yield return this[Index];
                }
            }
        }

        public void Empty(Int32 InExpectedNumElements = 0) => SetUtils.Set_Empty(GetHandle(), InExpectedNumElements);

        public Int32 Num() => SetUtils.Set_Num(GetHandle());

        public Int32 GetMaxIndex() => SetUtils.Set_GetMaxIndex(GetHandle());

        public void Add(T InValue) => SetUtils.Set_Add(GetHandle(), InValue);

        public Int32 Remove(T InValue) => SetUtils.Set_Remove(GetHandle(), InValue);

        public Boolean Contains(T InValue) => SetUtils.Set_Contains(GetHandle(), InValue);

        private Boolean IsValidIndex(Int32 InIndex) => SetUtils.Set_IsValidIndex(GetHandle(), InIndex);

        private T this[Int32 InIndex] => SetUtils.Set_GetEnumerator<T>(GetHandle(), InIndex);

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