using System.Collections;
using System.Collections.Generic;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TSet<T> : IEnumerable<T>
    {
        public TSet() => TSetImplementation.TSet_RegisterImplementation(this, GetType());

        ~TSet() => TSetImplementation.TSet_UnRegisterImplementation(HandleData.GetHandle(this));

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
            TSetImplementation.TSet_EmptyImplementation(HandleData.GetHandle(this), InExpectedNumElements);

        public int Num() => TSetImplementation.TSet_NumImplementation(HandleData.GetHandle(this));

        public bool IsEmpty() => TSetImplementation.TSet_IsEmptyImplementation(HandleData.GetHandle(this));

        public int GetMaxIndex() => TSetImplementation.TSet_GetMaxIndexImplementation(HandleData.GetHandle(this));

        public void Add(T InValue)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    *(T*)ValueBuffer = InValue;

                    TSetImplementation.TSet_AddImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    TSetImplementation.TSet_AddImplementation(HandleData.GetHandle(this), ValueBuffer);
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

                    return TSetImplementation.TSet_RemoveImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TSetImplementation.TSet_RemoveImplementation(HandleData.GetHandle(this), ValueBuffer);
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

                    return TSetImplementation.TSet_ContainsImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
                else
                {
                    var ValueBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                    return TSetImplementation.TSet_ContainsImplementation(HandleData.GetHandle(this), ValueBuffer);
                }
            }
        }

        private bool IsValidIndex(int InIndex) =>
            TSetImplementation.TSet_IsValidIndexImplementation(HandleData.GetHandle(this), InIndex);

        private T this[int InIndex]
        {
            get
            {
                unsafe
                {
                    if (typeof(T).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(T)];

                        TSetImplementation.TSet_GetEnumeratorImplementation(HandleData.GetHandle(this), InIndex,
                            ValueBuffer);

                        return *(T*)ValueBuffer;
                    }
                    else
                    {
                        return TSetImplementation.TSet_GetEnumeratorCompoundImplementation<T>(
                            HandleData.GetHandle(this), InIndex);
                    }
                }
            }
        }
    }
}