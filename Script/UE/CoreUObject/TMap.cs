using System.Collections;
using System.Collections.Generic;
using Script.Library;

namespace Script.CoreUObject
{
    public class TMap<TKey, TValue> : IEnumerable<KeyValuePair<TKey, TValue>>, IGarbageCollectionHandle
    {
        public TMap() => TMapImplementation.TMap_RegisterImplementation(this);

        ~TMap() => TMapImplementation.TMap_UnRegisterImplementation(GarbageCollectionHandle);

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            for (var Index = 0; Index < GetMaxIndex(); Index++)
            {
                if (IsValidIndex(Index))
                {
                    yield return new KeyValuePair<TKey, TValue>(GetEnumeratorKey(Index), GetEnumeratorValue(Index));
                }
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Empty(int InExpectedNumElements = 0) =>
            TMapImplementation.TMap_EmptyImplementation(GarbageCollectionHandle, InExpectedNumElements);

        public int Num() => TMapImplementation.TMap_NumImplementation(GarbageCollectionHandle);

        public bool IsEmpty() => TMapImplementation.TMap_IsEmptyImplementation(GarbageCollectionHandle);

        public void Add(TKey InKey, TValue InValue)
        {
            unsafe
            {
                if (typeof(TKey).IsValueType)
                {
                    if (typeof(TValue).IsValueType)
                    {
                        var KeyBuffer = stackalloc byte[sizeof(TKey)];

                        *(TKey*)KeyBuffer = InKey;

                        var ValueBuffer = stackalloc byte[sizeof(TValue)];

                        *(TValue*)ValueBuffer = InValue;

                        TMapImplementation.TMap_AddImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(TKey)];

                        *(TKey*)KeyBuffer = InKey;

                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        TMapImplementation.TMap_AddImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                    }
                }
                else
                {
                    if (typeof(TValue).IsValueType)
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        var ValueBuffer = stackalloc byte[sizeof(TValue)];

                        *(TValue*)ValueBuffer = InValue;

                        TMapImplementation.TMap_AddImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        TMapImplementation.TMap_AddImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                    }
                }
            }
        }

        public int Remove(TKey InKey)
        {
            unsafe
            {
                if (typeof(TKey).IsValueType)
                {
                    var KeyBuffer = stackalloc byte[sizeof(TKey)];

                    *(TKey*)KeyBuffer = InKey;

                    return TMapImplementation.TMap_RemoveImplementation(GarbageCollectionHandle, KeyBuffer);
                }
                else
                {
                    var KeyBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TMapImplementation.TMap_RemoveImplementation(GarbageCollectionHandle, KeyBuffer);
                }
            }
        }

        public TKey FindKey(TValue InValue)
        {
            unsafe
            {
                if (typeof(TValue).IsValueType)
                {
                    if (typeof(TKey).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(TValue)];

                        *(TValue*)ValueBuffer = InValue;

                        var ReturnBuffer = stackalloc byte[sizeof(TKey)];

                        TMapImplementation.TMap_FindKeyImplementation(GarbageCollectionHandle, ValueBuffer,
                            ReturnBuffer);

                        return *(TKey*)ReturnBuffer;
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(TValue)];

                        *(TValue*)ValueBuffer = InValue;

                        var ReturnBuffer = stackalloc byte[sizeof(nint)];

                        TMapImplementation.TMap_FindKeyImplementation(GarbageCollectionHandle, ValueBuffer,
                            ReturnBuffer);

                        return *(TKey*)ReturnBuffer;
                    }
                }
                else
                {
                    if (typeof(TKey).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        var ReturnBuffer = stackalloc byte[sizeof(TKey)];

                        TMapImplementation.TMap_FindKeyImplementation(GarbageCollectionHandle, ValueBuffer,
                            ReturnBuffer);

                        return *(TKey*)ReturnBuffer;
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = (InValue as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        var ReturnBuffer = stackalloc byte[sizeof(nint)];

                        TMapImplementation.TMap_FindKeyImplementation(GarbageCollectionHandle, ValueBuffer,
                            ReturnBuffer);

                        return *(TKey*)ReturnBuffer;
                    }
                }
            }
        }

        public TValue Find(TKey InKey)
        {
            unsafe
            {
                if (typeof(TKey).IsValueType)
                {
                    if (typeof(TValue).IsValueType)
                    {
                        var KeyBuffer = stackalloc byte[sizeof(TKey)];

                        *(TKey*)KeyBuffer = InKey;

                        var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                        TMapImplementation.TMap_FindImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                        return *(TValue*)ReturnBuffer;
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(TKey)];

                        *(TKey*)KeyBuffer = InKey;

                        var ReturnBuffer = stackalloc byte[sizeof(nint)];

                        TMapImplementation.TMap_FindImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                        return *(TValue*)ReturnBuffer;
                    }
                }
                else
                {
                    if (typeof(TValue).IsValueType)
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                        TMapImplementation.TMap_FindImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                        return *(TValue*)ReturnBuffer;
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                        var ReturnBuffer = stackalloc byte[sizeof(nint)];

                        TMapImplementation.TMap_FindImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                        return *(TValue*)ReturnBuffer;
                    }
                }
            }
        }

        public bool Contains(TKey InKey)
        {
            unsafe
            {
                if (typeof(TKey).IsValueType)
                {
                    var KeyBuffer = stackalloc byte[sizeof(TKey)];

                    *(TKey*)KeyBuffer = InKey;

                    return TMapImplementation.TMap_ContainsImplementation(GarbageCollectionHandle, KeyBuffer);
                }
                else
                {
                    var KeyBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                    return TMapImplementation.TMap_ContainsImplementation(GarbageCollectionHandle, KeyBuffer);
                }
            }
        }

        public TValue this[TKey InKey]
        {
            get
            {
                unsafe
                {
                    if (typeof(TKey).IsValueType)
                    {
                        if (typeof(TValue).IsValueType)
                        {
                            var KeyBuffer = stackalloc byte[sizeof(TKey)];

                            *(TKey*)KeyBuffer = InKey;

                            var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                            TMapImplementation.TMap_GetImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                            return *(TValue*)ReturnBuffer;
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(TKey)];

                            *(TKey*)KeyBuffer = InKey;

                            var ReturnBuffer = stackalloc byte[sizeof(nint)];

                            TMapImplementation.TMap_GetImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                            return *(TValue*)ReturnBuffer;
                        }
                    }
                    else
                    {
                        if (typeof(TValue).IsValueType)
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                            var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                            TMapImplementation.TMap_GetImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                            return *(TValue*)ReturnBuffer;
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                            var ReturnBuffer = stackalloc byte[sizeof(nint)];

                            TMapImplementation.TMap_GetImplementation(GarbageCollectionHandle, KeyBuffer, ReturnBuffer);

                            return *(TValue*)ReturnBuffer;
                        }
                    }
                }
            }

            set
            {
                unsafe
                {
                    if (typeof(TKey).IsValueType)
                    {
                        if (typeof(TValue).IsValueType)
                        {
                            var KeyBuffer = stackalloc byte[sizeof(TKey)];

                            *(TKey*)KeyBuffer = InKey;

                            var ValueBuffer = stackalloc byte[sizeof(TValue)];

                            *(TValue*)ValueBuffer = value;

                            TMapImplementation.TMap_SetImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(TKey)];

                            *(TKey*)KeyBuffer = InKey;

                            var ValueBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)ValueBuffer = (value as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                            TMapImplementation.TMap_SetImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                        }
                    }
                    else
                    {
                        if (typeof(TValue).IsValueType)
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                            var ValueBuffer = stackalloc byte[sizeof(TValue)];

                            *(TValue*)ValueBuffer = value;

                            TMapImplementation.TMap_SetImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = (InKey as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                            var ValueBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)ValueBuffer = (value as IGarbageCollectionHandle)!.GarbageCollectionHandle;

                            TMapImplementation.TMap_SetImplementation(GarbageCollectionHandle, KeyBuffer, ValueBuffer);
                        }
                    }
                }
            }
        }

        private int GetMaxIndex() => TMapImplementation.TMap_GetMaxIndexImplementation(GarbageCollectionHandle);

        private bool IsValidIndex(int InIndex) =>
            TMapImplementation.TMap_IsValidIndexImplementation(GarbageCollectionHandle, InIndex);

        private TKey GetEnumeratorKey(int InIndex)
        {
            unsafe
            {
                if (typeof(TKey).IsValueType)
                {
                    var ReturnBuffer = stackalloc byte[sizeof(TKey)];

                    TMapImplementation.TMap_GetEnumeratorKeyImplementation(GarbageCollectionHandle, InIndex,
                        ReturnBuffer);

                    return *(TKey*)ReturnBuffer;
                }
                else
                {
                    var ReturnBuffer = stackalloc byte[sizeof(nint)];

                    TMapImplementation.TMap_GetEnumeratorKeyImplementation(GarbageCollectionHandle, InIndex,
                        ReturnBuffer);

                    return *(TKey*)ReturnBuffer;
                }
            }
        }

        private TValue GetEnumeratorValue(int InIndex)
        {
            unsafe
            {
                if (typeof(TValue).IsValueType)
                {
                    var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                    TMapImplementation.TMap_GetEnumeratorValueImplementation(GarbageCollectionHandle, InIndex,
                        ReturnBuffer);

                    return *(TValue*)ReturnBuffer;
                }
                else
                {
                    var ReturnBuffer = stackalloc byte[sizeof(nint)];

                    TMapImplementation.TMap_GetEnumeratorValueImplementation(GarbageCollectionHandle, InIndex,
                        ReturnBuffer);

                    return *(TValue*)ReturnBuffer;
                }
            }
        }

        public nint GarbageCollectionHandle { get; set; }
    }
}