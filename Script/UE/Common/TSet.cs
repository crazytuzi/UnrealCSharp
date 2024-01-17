﻿using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSet<T> : IEnumerable<T>, IGarbageCollectionHandle
    {
        public TSet() => TSetImplementation.TSet_RegisterImplementation(this);

        ~TSet() => TSetImplementation.TSet_UnRegisterImplementation(GarbageCollectionHandle);

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
            TSetImplementation.TSet_EmptyImplementation(GarbageCollectionHandle, InExpectedNumElements);

        public int Num() => TSetImplementation.TSet_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => TSetImplementation.TSet_IsEmptyImplementation(GarbageCollectionHandle);

        public int GetMaxIndex() => TSetImplementation.TSet_GetMaxIndexImplementation(GarbageCollectionHandle);

        public void Add(T InValue) => TSetImplementation.TSet_AddImplementation(GarbageCollectionHandle, InValue);

        public int Remove(T InValue) => TSetImplementation.TSet_RemoveImplementation(GarbageCollectionHandle, InValue);

        public bool Contains(T InValue) =>
            TSetImplementation.TSet_ContainsImplementation(GarbageCollectionHandle, InValue);

        private bool IsValidIndex(int InIndex) =>
            TSetImplementation.TSet_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        private T this[int InIndex] =>
            (T)TSetImplementation.TSet_GetEnumeratorImplementation(GarbageCollectionHandle, InIndex);

        public nint GarbageCollectionHandle { get; set; }
    }
}