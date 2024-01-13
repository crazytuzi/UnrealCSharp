using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSet<T> : IGarbageCollectionHandle, IEnumerable<T>
    {
        public TSet() => SetImplementation.Set_RegisterImplementation(this);

        ~TSet() => SetImplementation.Set_UnRegisterImplementation(GarbageCollectionHandle);

        [Obsolete("It is not supported like UE.", true)]
        public static bool operator ==(TSet<T> A, TSet<T> B) => false;

        [Obsolete("It is not supported like UE.", true)]
        public static bool operator !=(TSet<T> A, TSet<T> B) => false;

        public override bool Equals(object Other) => false;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

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

        public void Empty(int InExpectedNumElements = 0) =>
            SetImplementation.Set_EmptyImplementation(GarbageCollectionHandle, InExpectedNumElements);

        public int Num() => SetImplementation.Set_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => SetImplementation.Set_IsEmptyImplementation(GarbageCollectionHandle);

        public int GetMaxIndex() => SetImplementation.Set_GetMaxIndexImplementation(GarbageCollectionHandle);

        public void Add(T InValue) => SetImplementation.Set_AddImplementation(GarbageCollectionHandle, InValue);

        public int Remove(T InValue) => SetImplementation.Set_RemoveImplementation(GarbageCollectionHandle, InValue);

        public bool Contains(T InValue) => SetImplementation.Set_ContainsImplementation(GarbageCollectionHandle, InValue);

        private bool IsValidIndex(int InIndex) =>
            SetImplementation.Set_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        private T this[int InIndex] => (T)SetImplementation.Set_GetEnumeratorImplementation(GarbageCollectionHandle, InIndex);

        public nint GarbageCollectionHandle { get; set; }
    }
}