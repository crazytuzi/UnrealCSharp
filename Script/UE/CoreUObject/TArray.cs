using System.Collections;
using System.Collections.Generic;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public static class TArray
    {
        public static int INDEX_NONE => TArrayImplementation.TArray_INDEX_NONEImplementation();
    }

    public class TArray<T> : IEnumerable<T>
    {
        public TArray() => TArrayImplementation.TArray_RegisterImplementation(this, GetType());

        ~TArray() => TArrayImplementation.TArray_UnRegisterImplementation(HandleData.GetHandle(this));

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
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TArray<T> A, TArray<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TArray<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

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

        public int GetTypeSize() => TArrayImplementation.TArray_GetTypeSizeImplementation(HandleData.GetHandle(this));

        public int GetSlack() => TArrayImplementation.TArray_GetSlackImplementation(HandleData.GetHandle(this));

        public bool IsValidIndex(int InIndex) =>
            TArrayImplementation.TArray_IsValidIndexImplementation(HandleData.GetHandle(this), InIndex);

        public int Num() => TArrayImplementation.TArray_NumImplementation(HandleData.GetHandle(this));

        public bool IsEmpty() => TArrayImplementation.TArray_IsEmptyImplementation(HandleData.GetHandle(this));

        public int Max() => TArrayImplementation.TArray_MaxImplementation(HandleData.GetHandle(this));

        public T this[int InIndex]
        {
            get
            {
                unsafe
                {
                    if (typeof(T).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(T)];

                        TArrayImplementation.TArray_GetImplementation(HandleData.GetHandle(this), InIndex, ValueBuffer);

                        return *(T*)ValueBuffer;
                    }
                    else
                    {
                        return TArrayImplementation.TArray_GetCompoundImplementation<T>(
                            HandleData.GetHandle(this), InIndex);
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

                        TArrayImplementation.TArray_SetImplementation(HandleData.GetHandle(this), InIndex, ValueBuffer);
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = HandleData.GetHandle((object)value);

                        TArrayImplementation.TArray_SetImplementation(HandleData.GetHandle(this), InIndex, ValueBuffer);
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

                    return TArrayImplementation.TArray_FindImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_FindImplementation(HandleData.GetHandle(this), ValueBuffer);
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

                    return TArrayImplementation.TArray_FindLastImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_FindLastImplementation(HandleData.GetHandle(this), ValueBuffer);
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

                    return TArrayImplementation.TArray_ContainsImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_ContainsImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
            }
        }

        public int AddUninitialized(int InCount = 1) =>
            TArrayImplementation.TArray_AddUninitializedImplementation(HandleData.GetHandle(this), InCount);

        public void InsertZeroed(int InIndex, int InCount = 1) =>
            TArrayImplementation.TArray_InsertZeroedImplementation(HandleData.GetHandle(this), InIndex, InCount);

        public void InsertDefaulted(int InIndex, int InCount) =>
            TArrayImplementation.TArray_InsertDefaultedImplementation(HandleData.GetHandle(this), InIndex, InCount);

        public void RemoveAt(int InIndex, int InCount, bool bAllowShrinking = true) =>
            TArrayImplementation.TArray_RemoveAtImplementation(HandleData.GetHandle(this), InIndex, InCount,
                bAllowShrinking);

        public void Reset(int InNewSize = 0) =>
            TArrayImplementation.TArray_ResetImplementation(HandleData.GetHandle(this), InNewSize);

        public void Empty(int InSlack = 0) =>
            TArrayImplementation.TArray_EmptyImplementation(HandleData.GetHandle(this), InSlack);

        public void SetNum(int InNewNum, bool bAllowShrinking = true) =>
            TArrayImplementation.TArray_SetNumImplementation(HandleData.GetHandle(this), InNewNum, bAllowShrinking);

        public int Add(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_AddImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_AddImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
            }
        }

        public int AddZeroed(int InCount = 1) =>
            TArrayImplementation.TArray_AddZeroedImplementation(HandleData.GetHandle(this), InCount);

        public int AddUnique(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    return TArrayImplementation.TArray_AddUniqueImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_AddUniqueImplementation(HandleData.GetHandle(this), ValueBuffer);
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

                    return TArrayImplementation.TArray_RemoveSingleImplementation(HandleData.GetHandle(this),
                        ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_RemoveSingleImplementation(HandleData.GetHandle(this),
                        ValueBuffer);
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

                    return TArrayImplementation.TArray_RemoveImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TArrayImplementation.TArray_RemoveImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
            }
        }

        public void SwapMemory(int InFirstIndexToSwap, int InSecondIndexToSwap) =>
            TArrayImplementation.TArray_SwapMemoryImplementation(HandleData.GetHandle(this), InFirstIndexToSwap,
                InSecondIndexToSwap);

        public void Swap(int InFirstIndexToSwap, int InSecondIndexToSwap) =>
            TArrayImplementation.TArray_SwapImplementation(HandleData.GetHandle(this), InFirstIndexToSwap,
                InSecondIndexToSwap);
    }
}