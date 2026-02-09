using System.Collections;
using System.Collections.Generic;
using Script.Library;

namespace Script.CoreUObject
{
    public static class TArray
    {
        public static int INDEX_NONE => TArrayImplementation.TArray_INDEX_NONEImplementation();
    }

    public class TArray<T> : IEnumerable<T>, IGarbageCollectionHandle
    {
        public TArray() => TArrayImplementation.TArray_RegisterImplementation(this, typeof(T));

        ~TArray() => TArrayImplementation.TArray_UnRegisterImplementation(GarbageCollectionHandle);

        public static bool operator ==(TArray<T> A, TArray<T> B)
        {
            if (A is null && B is null)
            {
                return true;
            }

            if (A is null || B is null)
            {
                return false;
            }

            return ReferenceEquals(A, B) ||
                   TArrayImplementation.TArray_IdenticalImplementation(
                       A.GarbageCollectionHandle,
                       B.GarbageCollectionHandle);
        }

        public static bool operator !=(TArray<T> A, TArray<T> B) => !(A == B);

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

        public int GetTypeSize() => TArrayImplementation.TArray_GetTypeSizeImplementation(GarbageCollectionHandle);

        public int GetSlack() => TArrayImplementation.TArray_GetSlackImplementation(GarbageCollectionHandle);

        public bool IsValidIndex(int InIndex) =>
            TArrayImplementation.TArray_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        public int Num() => TArrayImplementation.TArray_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => TArrayImplementation.TArray_IsEmptyImplementation(GarbageCollectionHandle);

        public int Max() => TArrayImplementation.TArray_MaxImplementation(GarbageCollectionHandle);

        public T this[int InIndex]
        {
            get
            {
                unsafe
                {
                    if (typeof(T).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(T)];

                        TArrayImplementation.TArray_GetImplementation(GarbageCollectionHandle, InIndex, ValueBuffer);

                        return *(T*)ValueBuffer;
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        TArrayImplementation.TArray_GetImplementation(GarbageCollectionHandle, InIndex, ValueBuffer);

                        return *(T*)ValueBuffer;
                    }
                }
            }

            set
            {
                unsafe
                {
                    if (typeof(T).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(T)];

                        *(T*)ValueBuffer = value;

                        TArrayImplementation.TArray_SetImplementation(GarbageCollectionHandle, InIndex, ValueBuffer);
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = (value as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        TArrayImplementation.TArray_SetImplementation(GarbageCollectionHandle, InIndex, ValueBuffer);
                    }
                }
            }
        }

        public int Find(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_FindImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_FindImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public int FindLast(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_FindLastImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_FindLastImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public bool Contains(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_ContainsImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_ContainsImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public int AddUninitialized(int InCount = 1) =>
            TArrayImplementation.TArray_AddUninitializedImplementation(GarbageCollectionHandle, InCount);

        public void InsertZeroed(int InIndex, int InCount = 1) =>
            TArrayImplementation.TArray_InsertZeroedImplementation(GarbageCollectionHandle, InIndex, InCount);

        public void InsertDefaulted(int InIndex, int InCount) =>
            TArrayImplementation.TArray_InsertDefaultedImplementation(GarbageCollectionHandle, InIndex, InCount);

        public void RemoveAt(int InIndex, int InCount, bool bAllowShrinking = true) =>
            TArrayImplementation.TArray_RemoveAtImplementation(GarbageCollectionHandle, InIndex, InCount,
                bAllowShrinking);

        public void Reset(int InNewSize = 0) =>
            TArrayImplementation.TArray_ResetImplementation(GarbageCollectionHandle, InNewSize);

        public void Empty(int InSlack = 0) =>
            TArrayImplementation.TArray_EmptyImplementation(GarbageCollectionHandle, InSlack);

        public void SetNum(int InNewNum, bool bAllowShrinking = true) =>
            TArrayImplementation.TArray_SetNumImplementation(GarbageCollectionHandle, InNewNum, bAllowShrinking);

        public int Add(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_AddImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_AddImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public int AddZeroed(int InCount = 1) =>
            TArrayImplementation.TArray_AddZeroedImplementation(GarbageCollectionHandle, InCount);

        public int AddUnique(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_AddUniqueImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_AddUniqueImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public int RemoveSingle(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_RemoveSingleImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_RemoveSingleImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public int Remove(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_RemoveImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TArrayImplementation.TArray_RemoveImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        public void SwapMemory(int InFirstIndexToSwap, int InSecondIndexToSwap) =>
            TArrayImplementation.TArray_SwapMemoryImplementation(GarbageCollectionHandle, InFirstIndexToSwap,
                InSecondIndexToSwap);

        public void Swap(int InFirstIndexToSwap, int InSecondIndexToSwap) =>
            TArrayImplementation.TArray_SwapImplementation(GarbageCollectionHandle, InFirstIndexToSwap,
                InSecondIndexToSwap);

        public nint GarbageCollectionHandle { get; set; }
    }
}