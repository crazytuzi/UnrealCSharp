using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSet<T> : IGCHandle, IEnumerable<T>
    {
        public TSet() => SetImplementation.Set_RegisterImplementation(this);

        ~TSet() => SetImplementation.Set_UnRegisterImplementation(GetHandle());

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator ==(TSet<T> A, TSet<T> B) => false;

        [Obsolete("It is not supported like UE.", true)]
        public static Boolean operator !=(TSet<T> A, TSet<T> B) => false;

        public override Boolean Equals(Object Other) => false;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

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

        public void Empty(Int32 InExpectedNumElements = 0) =>
            SetImplementation.Set_EmptyImplementation(GetHandle(), InExpectedNumElements);

        public Int32 Num() => SetImplementation.Set_NumImplementation(GetHandle());

        public Boolean IsEmpty() => SetImplementation.Set_IsEmptyImplementation(GetHandle());

        public Int32 GetMaxIndex() => SetImplementation.Set_GetMaxIndexImplementation(GetHandle());

        public void Add(T InValue) => SetImplementation.Set_AddImplementation(GetHandle(), InValue);

        public Int32 Remove(T InValue) => SetImplementation.Set_RemoveImplementation(GetHandle(), InValue);

        public Boolean Contains(T InValue) => SetImplementation.Set_ContainsImplementation(GetHandle(), InValue);

        private Boolean IsValidIndex(Int32 InIndex) =>
            SetImplementation.Set_IsValidIndexImplementation(GetHandle(), InIndex);

        private T this[Int32 InIndex] => (T)SetImplementation.Set_GetEnumeratorImplementation(GetHandle(), InIndex);

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