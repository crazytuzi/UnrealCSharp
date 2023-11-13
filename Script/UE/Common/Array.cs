using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Reflection.Container;

namespace Script.Common
{
    public class TArray<T> : IGCHandle, IEnumerable<T>
    {
        public TArray() => ArrayUtils.Array_Register(this);

        ~TArray() => ArrayUtils.Array_UnRegister(GetHandle());

        public static Boolean operator ==(TArray<T> A, TArray<T> B) =>
            ArrayUtils.Array_Identical(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(TArray<T> A, TArray<T> B) =>
            !ArrayUtils.Array_Identical(A.GetHandle(), B.GetHandle());

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

        public Int32 GetTypeSize() => ArrayUtils.Array_GetTypeSize(GetHandle());

        public Int32 GetSlack() => ArrayUtils.Array_GetSlack(GetHandle());

        public Boolean IsValidIndex() => ArrayUtils.Array_IsValidIndex(GetHandle());

        public Int32 Num() => ArrayUtils.Array_Num(GetHandle());

        public Int32 Max() => ArrayUtils.Array_Max(GetHandle());

        public T this[Int32 InIndex]
        {
            get => ArrayUtils.Array_Get<T>(GetHandle(), InIndex);

            set => ArrayUtils.Array_Set(GetHandle(), InIndex, value);
        }

        public Int32 Find(T InValue) => ArrayUtils.Array_Find(GetHandle(), InValue);

        public Int32 FindLast(T InValue) => ArrayUtils.Array_FindLast(GetHandle(), InValue);

        public Boolean Contains(T InValue) => ArrayUtils.Array_Contains(GetHandle(), InValue);

        public Int32 AddUninitialized(Int32 InCount = 1) => ArrayUtils.Array_AddUninitialized(GetHandle(), InCount);

        public void InsertZeroed(Int32 InIndex, Int32 InCount = 1) =>
            ArrayUtils.Array_InsertZeroed(GetHandle(), InIndex, InCount);

        public void InsertDefaulted(Int32 InIndex, Int32 InCount) =>
            ArrayUtils.Array_InsertDefaulted(GetHandle(), InIndex, InCount);

        public void RemoveAt(Int32 InIndex, Int32 InCount, Boolean bAllowShrinking = true) =>
            ArrayUtils.Array_RemoveAt(GetHandle(), InIndex, InCount, bAllowShrinking);

        public void Reset(Int32 InNewSize = 0) => ArrayUtils.Array_Reset(GetHandle(), InNewSize);

        public void Empty(Int32 InSlack = 0) => ArrayUtils.Array_Empty(GetHandle(), InSlack);

        public void SetNum(Int32 InNewNum, Boolean bAllowShrinking = true) =>
            ArrayUtils.Array_SetNum(GetHandle(), InNewNum, bAllowShrinking);

        public Int32 Add(T InValue) => ArrayUtils.Array_Add(GetHandle(), InValue);

        public Int32 AddZeroed(Int32 InCount = 1) => ArrayUtils.Array_AddZeroed(GetHandle(), InCount);

        public Int32 AddUnique(T InValue) => ArrayUtils.Array_AddUnique(GetHandle(), InValue);

        public Int32 RemoveSingle(T InValue) => ArrayUtils.Array_RemoveSingle(GetHandle(), InValue);

        public Int32 Remove(T InValue) => ArrayUtils.Array_Remove(GetHandle(), InValue);

        public void SwapMemory(Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayUtils.Array_SwapMemory(GetHandle(), InFirstIndexToSwap, InSecondIndexToSwap);

        public void Swap(Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayUtils.Array_Swap(GetHandle(), InFirstIndexToSwap, InSecondIndexToSwap);

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