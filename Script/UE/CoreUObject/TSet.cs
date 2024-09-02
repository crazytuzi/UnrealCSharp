using System.Collections;
using System.Collections.Generic;
using Script.Library;

namespace Script.CoreUObject
{
    public class TSet<T> : IEnumerable<T>, IGarbageCollectionHandle
    {
        public TSet() => TSetImplementation.TSet_RegisterImplementation(this);

        ~TSet() => TSetImplementation.TSet_UnRegisterImplementation(GarbageCollectionHandle);

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

        public void Add(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    TSetImplementation.TSet_AddImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    TSetImplementation.TSet_AddImplementation(GarbageCollectionHandle, ValueBuffer);
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

                    return TSetImplementation.TSet_RemoveImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TSetImplementation.TSet_RemoveImplementation(GarbageCollectionHandle, ValueBuffer);
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

                    return TSetImplementation.TSet_ContainsImplementation(GarbageCollectionHandle, ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TSetImplementation.TSet_ContainsImplementation(GarbageCollectionHandle, ValueBuffer);
                }
            }
        }

        private bool IsValidIndex(int InIndex) =>
            TSetImplementation.TSet_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        private T this[int InIndex]
        {
            get
            {
                unsafe
                {
                    if (typeof(T).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(T)];

                        TSetImplementation.TSet_GetEnumeratorImplementation(GarbageCollectionHandle, InIndex,
                            ValueBuffer);

                        return *(T*)ValueBuffer;
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        TSetImplementation.TSet_GetEnumeratorImplementation(GarbageCollectionHandle, InIndex,
                            ValueBuffer);

                        return *(T*)ValueBuffer;
                    }
                }
            }
        }

        public nint GarbageCollectionHandle { get; set; }
    }
}