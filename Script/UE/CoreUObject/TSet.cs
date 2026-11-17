using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TSet<T> : IEnumerable<T>, IDisposable
    {
        private const int EnumeratorChunkSize = 256;

        public TSet() => TSetImplementation.TSet_RegisterImplementation(this, GetType());

        ~TSet() => Dispose();

        private bool bIsDisposed;

        public void Dispose()
        {
            if (!bIsDisposed)
            {
                bIsDisposed = true;

                TSetImplementation.TSet_UnRegisterImplementation(HandleData.GetHandle(this));
            }

            GC.SuppressFinalize(this);
        }

        public IEnumerator<T> GetEnumerator()
        {
            var Handle = HandleData.GetHandle(this);

            var ElementSize = TSetImplementation.TSet_GetTypeSizeImplementation(Handle);

            if (typeof(T).IsValueType && ElementSize == Unsafe.SizeOf<T>())
            {
                var Buffer = new byte[EnumeratorChunkSize * ElementSize];

                var Index = 0;

                while (true)
                {
                    var Count = GetElements(Handle, Index, EnumeratorChunkSize, Buffer, out var NextIndex);

                    for (var ElementIndex = 0; ElementIndex < Count; ElementIndex++)
                    {
                        yield return Unsafe.ReadUnaligned<T>(ref Buffer[ElementIndex * ElementSize]);
                    }

                    if (Count < EnumeratorChunkSize)
                    {
                        yield break;
                    }

                    Index = NextIndex;
                }
            }

            for (var Index = 0; Index < TSetImplementation.TSet_GetMaxIndexImplementation(Handle); Index++)
            {
                if (IsValidIndex(Handle, Index))
                {
                    yield return GetValue(Handle, Index);
                }
            }
        }

        private static unsafe int GetElements(nint InHandle, int InIndex, int InCount, byte[] InBuffer,
            out int OutNextIndex)
        {
            fixed (byte* Buffer = InBuffer)
            {
                var NextIndex = 0;

                var Count = TSetImplementation.TSet_GetElementsImplementation(InHandle, InIndex, InCount,
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

        private bool IsValidIndex(nint InHandle, int InIndex) =>
            TSetImplementation.TSet_IsValidIndexImplementation(InHandle, InIndex);

        private T GetValue(nint InHandle, int InIndex)
        {
            unsafe
            {
                if (typeof(T).IsValueType)
                {
                    var ValueBuffer = stackalloc byte[sizeof(T)];

                    TSetImplementation.TSet_GetEnumeratorImplementation(InHandle, InIndex, ValueBuffer);

                    return *(T*)ValueBuffer;
                }
                else
                {
                    return TSetImplementation.TSet_GetEnumeratorCompoundImplementation<T>(InHandle, InIndex);
                }
            }
        }
    }
}