using System;
using System.Collections;
using Script.Reflection.Container;

namespace Script.Engine
{
    public class TArray<T> : IEnumerable
    {
        public TArray() => ArrayUtils.RegisterArray(this, typeof(T));

        protected TArray(Type InValue)
        {
        }

        ~TArray() => ArrayUtils.UnRegisterArray(this);

        public IEnumerator GetEnumerator()
        {
            for (var Index = 0; Index < Num(); Index++)
            {
                yield return this[Index];
            }
        }

        public Int32 GetTypeSize() => ArrayUtils.Array_GetTypeSize(this);

        public Int32 GetSlack() => ArrayUtils.Array_GetSlack(this);

        public Boolean IsValidIndex() => ArrayUtils.Array_IsValidIndex(this);

        public Int32 Num() => ArrayUtils.Array_Num(this);

        public Int32 Max() => ArrayUtils.Array_Max(this);

        public T this[Int32 InIndex]
        {
            get => ArrayUtils.Array_Get(this, InIndex);

            set => ArrayUtils.Array_Set(this, InIndex, value);
        }

        public Int32 Find(T InValue) => ArrayUtils.Array_Find(this, InValue);

        public Int32 FindLast(T InValue) => ArrayUtils.Array_FindLast(this, InValue);

        public Boolean Contains(T InValue) => ArrayUtils.Array_Contains(this, InValue);

        public Int32 AddUninitialized(Int32 InCount = 1) => ArrayUtils.Array_AddUninitialized(this, InCount);

        public void InsertZeroed(Int32 InIndex, Int32 InCount = 1) =>
            ArrayUtils.Array_InsertZeroed(this, InIndex, InCount);

        public void InsertDefaulted(Int32 InIndex, Int32 InCount) =>
            ArrayUtils.Array_InsertDefaulted(this, InIndex, InCount);

        public void RemoveAt(Int32 InIndex, Int32 InCount, Boolean bAllowShrinking = true) =>
            ArrayUtils.Array_RemoveAt(this, InIndex, InCount, bAllowShrinking);

        public void Reset(Int32 InNewSize = 0) => ArrayUtils.Array_Reset(this, InNewSize);

        public void Empty(Int32 InSlack = 0) => ArrayUtils.Array_Empty(this, InSlack);

        public void SetNum(Int32 InNewNum, Boolean bAllowShrinking = true) =>
            ArrayUtils.Array_SetNum(this, InNewNum, bAllowShrinking);

        public Int32 Add(T InValue) => ArrayUtils.Array_Add(this, InValue);

        public Int32 AddZeroed(Int32 InCount = 1) => ArrayUtils.Array_AddZeroed(this, InCount);

        public Int32 AddUnique(T InValue) => ArrayUtils.Array_AddUnique(this, InValue);

        public Int32 RemoveSingle(T InValue) => ArrayUtils.Array_RemoveSingle(this, InValue);

        public Int32 Remove(T InValue) => ArrayUtils.Array_Remove(this, InValue);

        public void SwapMemory(Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayUtils.Array_SwapMemory(this, InFirstIndexToSwap, InSecondIndexToSwap);

        public void Swap(Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayUtils.Array_Swap(this, InFirstIndexToSwap, InSecondIndexToSwap);
    }
}