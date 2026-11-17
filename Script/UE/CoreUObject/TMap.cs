using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TMap<TKey, TValue> : IEnumerable<KeyValuePair<TKey, TValue>>, IDisposable
    {
        private const int EnumeratorChunkSize = 256;

        public TMap() => TMapImplementation.TMap_RegisterImplementation(this, GetType());

        ~TMap() => Dispose();

        private bool bIsDisposed;

        public void Dispose()
        {
            if (!bIsDisposed)
            {
                bIsDisposed = true;

                TMapImplementation.TMap_UnRegisterImplementation(HandleData.GetHandle(this));
            }

            GC.SuppressFinalize(this);
        }

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            var Handle = HandleData.GetHandle(this);

            var KeySize = TMapImplementation.TMap_GetKeyTypeSizeImplementation(Handle);

            var ValueSize = TMapImplementation.TMap_GetValueTypeSizeImplementation(Handle);

            if (typeof(TKey).IsValueType && typeof(TValue).IsValueType &&
                KeySize == Unsafe.SizeOf<TKey>() && ValueSize == Unsafe.SizeOf<TValue>())
            {
                var PairSize = KeySize + ValueSize;

                var Buffer = new byte[EnumeratorChunkSize * PairSize];

                var Index = 0;

                while (true)
                {
                    var Count = GetPairs(Handle, Index, EnumeratorChunkSize, Buffer, out var NextIndex);

                    for (var PairIndex = 0; PairIndex < Count; PairIndex++)
                    {
                        var Offset = PairIndex * PairSize;

                        yield return new KeyValuePair<TKey, TValue>(
                            Unsafe.ReadUnaligned<TKey>(ref Buffer[Offset]),
                            Unsafe.ReadUnaligned<TValue>(ref Buffer[Offset + KeySize]));
                    }

                    if (Count < EnumeratorChunkSize)
                    {
                        yield break;
                    }

                    Index = NextIndex;
                }
            }

            for (var Index = 0; Index < GetMaxIndex(Handle); Index++)
            {
                if (IsValidIndex(Handle, Index))
                {
                    yield return new KeyValuePair<TKey, TValue>(GetEnumeratorKey(Handle, Index),
                        GetEnumeratorValue(Handle, Index));
                }
            }
        }

        private static unsafe int GetPairs(nint InHandle, int InIndex, int InCount, byte[] InBuffer,
            out int OutNextIndex)
        {
            fixed (byte* Buffer = InBuffer)
            {
                var NextIndex = 0;

                var Count = TMapImplementation.TMap_GetPairsImplementation(InHandle, InIndex, InCount,
                    Buffer, InBuffer.Length, &NextIndex);

                OutNextIndex = NextIndex;

                return Count;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Empty(int InExpectedNumElements = 0) =>
            TMapImplementation.TMap_EmptyImplementation(HandleData.GetHandle(this), InExpectedNumElements);

        public int Num() => TMapImplementation.TMap_NumImplementation(HandleData.GetHandle(this));

        public bool IsEmpty() => TMapImplementation.TMap_IsEmptyImplementation(HandleData.GetHandle(this));

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

                        TMapImplementation.TMap_AddImplementation(HandleData.GetHandle(this), KeyBuffer, ValueBuffer);
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(TKey)];

                        *(TKey*)KeyBuffer = InKey;

                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                        TMapImplementation.TMap_AddImplementation(HandleData.GetHandle(this), KeyBuffer, ValueBuffer);
                    }
                }
                else
                {
                    if (typeof(TValue).IsValueType)
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                        var ValueBuffer = stackalloc byte[sizeof(TValue)];

                        *(TValue*)ValueBuffer = InValue;

                        TMapImplementation.TMap_AddImplementation(HandleData.GetHandle(this), KeyBuffer, ValueBuffer);
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                        TMapImplementation.TMap_AddImplementation(HandleData.GetHandle(this), KeyBuffer, ValueBuffer);
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

                    return TMapImplementation.TMap_RemoveImplementation(HandleData.GetHandle(this), KeyBuffer);
                }
                else
                {
                    var KeyBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                    return TMapImplementation.TMap_RemoveImplementation(HandleData.GetHandle(this), KeyBuffer);
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

                        TMapImplementation.TMap_FindKeyImplementation(HandleData.GetHandle(this), ValueBuffer,
                            ReturnBuffer);

                        return *(TKey*)ReturnBuffer;
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(TValue)];

                        *(TValue*)ValueBuffer = InValue;

                        return TMapImplementation.TMap_FindKeyCompoundImplementation<TKey>(
                            HandleData.GetHandle(this), ValueBuffer);
                    }
                }
                else
                {
                    if (typeof(TKey).IsValueType)
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                        var ReturnBuffer = stackalloc byte[sizeof(TKey)];

                        TMapImplementation.TMap_FindKeyImplementation(HandleData.GetHandle(this), ValueBuffer,
                            ReturnBuffer);

                        return *(TKey*)ReturnBuffer;
                    }
                    else
                    {
                        var ValueBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)ValueBuffer = HandleData.GetHandle((object)InValue);

                        return TMapImplementation.TMap_FindKeyCompoundImplementation<TKey>(
                            HandleData.GetHandle(this), ValueBuffer);
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

                        TMapImplementation.TMap_FindImplementation(HandleData.GetHandle(this), KeyBuffer, ReturnBuffer);

                        return *(TValue*)ReturnBuffer;
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(TKey)];

                        *(TKey*)KeyBuffer = InKey;

                        return TMapImplementation.TMap_FindCompoundImplementation<TValue>(
                            HandleData.GetHandle(this), KeyBuffer);
                    }
                }
                else
                {
                    if (typeof(TValue).IsValueType)
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                        var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                        TMapImplementation.TMap_FindImplementation(HandleData.GetHandle(this), KeyBuffer, ReturnBuffer);

                        return *(TValue*)ReturnBuffer;
                    }
                    else
                    {
                        var KeyBuffer = stackalloc byte[sizeof(nint)];

                        *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                        return TMapImplementation.TMap_FindCompoundImplementation<TValue>(
                            HandleData.GetHandle(this), KeyBuffer);
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

                    return TMapImplementation.TMap_ContainsImplementation(HandleData.GetHandle(this), KeyBuffer);
                }
                else
                {
                    var KeyBuffer = stackalloc byte[sizeof(nint)];

                    *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                    return TMapImplementation.TMap_ContainsImplementation(HandleData.GetHandle(this), KeyBuffer);
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

                            TMapImplementation.TMap_GetImplementation(HandleData.GetHandle(this), KeyBuffer,
                                ReturnBuffer);

                            return *(TValue*)ReturnBuffer;
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(TKey)];

                            *(TKey*)KeyBuffer = InKey;

                            return TMapImplementation.TMap_GetCompoundImplementation<TValue>(
                                HandleData.GetHandle(this), KeyBuffer);
                        }
                    }
                    else
                    {
                        if (typeof(TValue).IsValueType)
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                            var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                            TMapImplementation.TMap_GetImplementation(HandleData.GetHandle(this), KeyBuffer,
                                ReturnBuffer);

                            return *(TValue*)ReturnBuffer;
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                            return TMapImplementation.TMap_GetCompoundImplementation<TValue>(
                                HandleData.GetHandle(this), KeyBuffer);
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

                            TMapImplementation.TMap_SetImplementation(HandleData.GetHandle(this), KeyBuffer,
                                ValueBuffer);
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(TKey)];

                            *(TKey*)KeyBuffer = InKey;

                            var ValueBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)ValueBuffer = HandleData.GetHandle((object)value);

                            TMapImplementation.TMap_SetImplementation(HandleData.GetHandle(this), KeyBuffer,
                                ValueBuffer);
                        }
                    }
                    else
                    {
                        if (typeof(TValue).IsValueType)
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                            var ValueBuffer = stackalloc byte[sizeof(TValue)];

                            *(TValue*)ValueBuffer = value;

                            TMapImplementation.TMap_SetImplementation(HandleData.GetHandle(this), KeyBuffer,
                                ValueBuffer);
                        }
                        else
                        {
                            var KeyBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)KeyBuffer = HandleData.GetHandle((object)InKey);

                            var ValueBuffer = stackalloc byte[sizeof(nint)];

                            *(nint*)ValueBuffer = HandleData.GetHandle((object)value);

                            TMapImplementation.TMap_SetImplementation(HandleData.GetHandle(this), KeyBuffer,
                                ValueBuffer);
                        }
                    }
                }
            }
        }

        private int GetMaxIndex(nint InHandle) => TMapImplementation.TMap_GetMaxIndexImplementation(InHandle);

        private bool IsValidIndex(nint InHandle, int InIndex) =>
            TMapImplementation.TMap_IsValidIndexImplementation(InHandle, InIndex);

        private TKey GetEnumeratorKey(nint InHandle, int InIndex)
        {
            unsafe
            {
                if (typeof(TKey).IsValueType)
                {
                    var ReturnBuffer = stackalloc byte[sizeof(TKey)];

                    TMapImplementation.TMap_GetEnumeratorKeyImplementation(InHandle, InIndex, ReturnBuffer);

                    return *(TKey*)ReturnBuffer;
                }
                else
                {
                    return TMapImplementation.TMap_GetEnumeratorKeyCompoundImplementation<TKey>(
                        InHandle, InIndex);
                }
            }
        }

        private TValue GetEnumeratorValue(nint InHandle, int InIndex)
        {
            unsafe
            {
                if (typeof(TValue).IsValueType)
                {
                    var ReturnBuffer = stackalloc byte[sizeof(TValue)];

                    TMapImplementation.TMap_GetEnumeratorValueImplementation(InHandle, InIndex, ReturnBuffer);

                    return *(TValue*)ReturnBuffer;
                }
                else
                {
                    return TMapImplementation.TMap_GetEnumeratorValueCompoundImplementation<TValue>(
                        InHandle, InIndex);
                }
            }
        }
    }
}