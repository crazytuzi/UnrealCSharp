using System;
using System.Collections;
using System.Collections.Generic;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public static class TArray
    {
        public static Int32 INDEX_NONE => ArrayImplementation.Array_INDEX_NONEImplementation();
    }

    public class TArray<T> : IGCHandle, IEnumerable<T>
    {
        public TArray() => ArrayImplementation.Array_RegisterImplementation(this);

        ~TArray() => ArrayImplementation.Array_UnRegisterImplementation(GetHandle());

        public static Boolean operator ==(TArray<T> A, TArray<T> B) =>
            ArrayImplementation.Array_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TArray<T> A, TArray<T> B) =>
            !ArrayImplementation.Array_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TArray<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

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

        public Int32 GetTypeSize() => ArrayImplementation.Array_GetTypeSizeImplementation(GetHandle());

        public Int32 GetSlack() => ArrayImplementation.Array_GetSlackImplementation(GetHandle());

        public Boolean IsValidIndex(Int32 InIndex) =>
            ArrayImplementation.Array_IsValidIndexImplementation(GetHandle(), InIndex);

        public Int32 Num() => ArrayImplementation.Array_NumImplementation(GetHandle());

        public Boolean IsEmpty() => ArrayImplementation.Array_IsEmptyImplementation(GetHandle());

        public Int32 Max() => ArrayImplementation.Array_MaxImplementation(GetHandle());

        public T this[Int32 InIndex]
        {
            get => (T)ArrayImplementation.Array_GetImplementation(GetHandle(), InIndex);

            set => ArrayImplementation.Array_SetImplementation(GetHandle(), InIndex, value);
        }

        public Int32 Find(T InValue) => ArrayImplementation.Array_FindImplementation(GetHandle(), InValue);

        public Int32 FindLast(T InValue) => ArrayImplementation.Array_FindLastImplementation(GetHandle(), InValue);

        public Boolean Contains(T InValue) => ArrayImplementation.Array_ContainsImplementation(GetHandle(), InValue);

        public Int32 AddUninitialized(Int32 InCount = 1) =>
            ArrayImplementation.Array_AddUninitializedImplementation(GetHandle(), InCount);

        public void InsertZeroed(Int32 InIndex, Int32 InCount = 1) =>
            ArrayImplementation.Array_InsertZeroedImplementation(GetHandle(), InIndex, InCount);

        public void InsertDefaulted(Int32 InIndex, Int32 InCount) =>
            ArrayImplementation.Array_InsertDefaultedImplementation(GetHandle(), InIndex, InCount);

        public void RemoveAt(Int32 InIndex, Int32 InCount, Boolean bAllowShrinking = true) =>
            ArrayImplementation.Array_RemoveAtImplementation(GetHandle(), InIndex, InCount, bAllowShrinking);

        public void Reset(Int32 InNewSize = 0) => ArrayImplementation.Array_ResetImplementation(GetHandle(), InNewSize);

        public void Empty(Int32 InSlack = 0) => ArrayImplementation.Array_EmptyImplementation(GetHandle(), InSlack);

        public void SetNum(Int32 InNewNum, Boolean bAllowShrinking = true) =>
            ArrayImplementation.Array_SetNumImplementation(GetHandle(), InNewNum, bAllowShrinking);

        public Int32 Add(T InValue) => ArrayImplementation.Array_AddImplementation(GetHandle(), InValue);

        public Int32 AddZeroed(Int32 InCount = 1) =>
            ArrayImplementation.Array_AddZeroedImplementation(GetHandle(), InCount);

        public Int32 AddUnique(T InValue) => ArrayImplementation.Array_AddUniqueImplementation(GetHandle(), InValue);

        public Int32 RemoveSingle(T InValue) =>
            ArrayImplementation.Array_RemoveSingleImplementation(GetHandle(), InValue);

        public Int32 Remove(T InValue) => ArrayImplementation.Array_RemoveImplementation(GetHandle(), InValue);

        public void SwapMemory(Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayImplementation.Array_SwapMemoryImplementation(GetHandle(), InFirstIndexToSwap, InSecondIndexToSwap);

        public void Swap(Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayImplementation.Array_SwapImplementation(GetHandle(), InFirstIndexToSwap, InSecondIndexToSwap);

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