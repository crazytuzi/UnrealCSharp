using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public static class TArray
    {
        public static int INDEX_NONE => ArrayImplementation.Array_INDEX_NONEImplementation();
    }

    public class TArray<T> : IGarbageCollectionHandle, IEnumerable<T>
    {
        public TArray() => ArrayImplementation.Array_RegisterImplementation(this);

        ~TArray() => ArrayImplementation.Array_UnRegisterImplementation(GarbageCollectionHandle);

        public static bool operator ==(TArray<T> A, TArray<T> B) =>
            ArrayImplementation.Array_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TArray<T> A, TArray<T> B) =>
            !ArrayImplementation.Array_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TArray<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public IEnumerator<T> GetEnumerator()
        {
            for (var Index = 0; Index < Num(); Index++)
            {
                yield return this[Index];
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            for (var Index = 0; Index < Num(); Index++)
            {
                yield return this[Index];
            }
        }

        public int GetTypeSize() => ArrayImplementation.Array_GetTypeSizeImplementation(GarbageCollectionHandle);

        public int GetSlack() => ArrayImplementation.Array_GetSlackImplementation(GarbageCollectionHandle);

        public bool IsValidIndex(int InIndex) =>
            ArrayImplementation.Array_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        public int Num() => ArrayImplementation.Array_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => ArrayImplementation.Array_IsEmptyImplementation(GarbageCollectionHandle);

        public int Max() => ArrayImplementation.Array_MaxImplementation(GarbageCollectionHandle);

        public T this[int InIndex]
        {
            get => (T)ArrayImplementation.Array_GetImplementation(GarbageCollectionHandle, InIndex);

            set => ArrayImplementation.Array_SetImplementation(GarbageCollectionHandle, InIndex, value);
        }

        public int Find(T InValue) => ArrayImplementation.Array_FindImplementation(GarbageCollectionHandle, InValue);

        public int FindLast(T InValue) =>
            ArrayImplementation.Array_FindLastImplementation(GarbageCollectionHandle, InValue);

        public bool Contains(T InValue) =>
            ArrayImplementation.Array_ContainsImplementation(GarbageCollectionHandle, InValue);

        public int AddUninitialized(int InCount = 1) =>
            ArrayImplementation.Array_AddUninitializedImplementation(GarbageCollectionHandle, InCount);

        public void InsertZeroed(int InIndex, int InCount = 1) =>
            ArrayImplementation.Array_InsertZeroedImplementation(GarbageCollectionHandle, InIndex, InCount);

        public void InsertDefaulted(int InIndex, int InCount) =>
            ArrayImplementation.Array_InsertDefaultedImplementation(GarbageCollectionHandle, InIndex, InCount);

        public void RemoveAt(int InIndex, int InCount, bool bAllowShrinking = true) =>
            ArrayImplementation.Array_RemoveAtImplementation(GarbageCollectionHandle, InIndex, InCount,
                bAllowShrinking);

        public void Reset(int InNewSize = 0) =>
            ArrayImplementation.Array_ResetImplementation(GarbageCollectionHandle, InNewSize);

        public void Empty(int InSlack = 0) =>
            ArrayImplementation.Array_EmptyImplementation(GarbageCollectionHandle, InSlack);

        public void SetNum(int InNewNum, bool bAllowShrinking = true) =>
            ArrayImplementation.Array_SetNumImplementation(GarbageCollectionHandle, InNewNum, bAllowShrinking);

        public int Add(T InValue) => ArrayImplementation.Array_AddImplementation(GarbageCollectionHandle, InValue);

        public int AddZeroed(int InCount = 1) =>
            ArrayImplementation.Array_AddZeroedImplementation(GarbageCollectionHandle, InCount);

        public int AddUnique(T InValue) =>
            ArrayImplementation.Array_AddUniqueImplementation(GarbageCollectionHandle, InValue);

        public int RemoveSingle(T InValue) =>
            ArrayImplementation.Array_RemoveSingleImplementation(GarbageCollectionHandle, InValue);

        public int Remove(T InValue) =>
            ArrayImplementation.Array_RemoveImplementation(GarbageCollectionHandle, InValue);

        public void SwapMemory(int InFirstIndexToSwap, int InSecondIndexToSwap) =>
            ArrayImplementation.Array_SwapMemoryImplementation(GarbageCollectionHandle, InFirstIndexToSwap,
                InSecondIndexToSwap);

        public void Swap(int InFirstIndexToSwap, int InSecondIndexToSwap) =>
            ArrayImplementation.Array_SwapImplementation(GarbageCollectionHandle, InFirstIndexToSwap,
                InSecondIndexToSwap);

        public nint GarbageCollectionHandle { get; set; }
    }
}