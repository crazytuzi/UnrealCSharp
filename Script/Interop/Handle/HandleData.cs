using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Interop
{
    public static class HandleData
    {
        private static readonly System.Threading.Lock Lock = new();

        private static readonly Dictionary<nint, GCHandle> Handles = new();

        private static nint Handle;

        private sealed class HandleReference
        {
            public nint Value;

            public int Count;
        }

        private static readonly ConditionalWeakTable<object, HandleReference> ObjectToHandleReference = new();

        [UnmanagedCallersOnly]
        public static void Free(nint InHandle) => FreeImplementation(InHandle);

        public static nint Alloc(object InObject, bool bPinned = false)
        {
            lock (Lock)
            {
                var HandleReference = ObjectToHandleReference.GetValue(InObject, _ =>
                    new HandleReference { Value = ++Handle, Count = 0 });

                HandleReference.Count++;

                if (!Handles.TryGetValue(HandleReference.Value, out _))
                {
                    Handles[HandleReference.Value] =
                        GCHandle.Alloc(InObject, bPinned ? GCHandleType.Pinned : GCHandleType.Normal);
                }

                return HandleReference.Value;
            }
        }

        public static void FreeImplementation(nint InHandle)
        {
            if (InHandle != 0)
            {
                lock (Lock)
                {
                    if (Handles.TryGetValue(InHandle, out var OutHandle))
                    {
                        var Target = OutHandle.Target;

                        if (Target != null)
                        {
                            if (ObjectToHandleReference.TryGetValue(Target, out var OutHandleReference))
                            {
                                if (OutHandleReference.Value == InHandle)
                                {
                                    OutHandleReference.Count--;

                                    if (OutHandleReference.Count > 0)
                                    {
                                        return;
                                    }
                                }
                            }
                        }

                        Handles.Remove(InHandle);

                        OutHandle.Free();
                    }
                }
            }
        }

        public static nint GetHandle(object? InObject)
        {
            if (InObject != null)
            {
                lock (Lock)
                {
                    return ObjectToHandleReference.TryGetValue(InObject, out var OutHandleReference)
                        ? OutHandleReference.Value
                        : 0;
                }
            }

            return 0;
        }

        public static object? GetObject(nint InHandle)
        {
            if (InHandle != 0)
            {
                lock (Lock)
                {
                    return Handles.TryGetValue(InHandle, out var OutHandle) ? OutHandle.Target : null;
                }
            }

            return null;
        }

        public static nint GetObjectPointer(nint InHandle)
        {
            if (GetObject(InHandle) is { } Object)
            {
                return Unsafe.As<object, nint>(ref Object);
            }

            return 0;
        }

        public static unsafe void GetObjectPointers(nint* InHandles, nint* OutObjectPointers, int InLength)
        {
            if (InHandles != null && OutObjectPointers != null)
            {
                for (var Index = 0; Index < InLength; Index++)
                {
                    OutObjectPointers[Index] = GetObjectPointer(InHandles[Index]);
                }
            }
        }

        internal static void Clear()
        {
            lock (Lock)
            {
                foreach (var Handle in Handles)
                {
                    if (Handle.Value.IsAllocated)
                    {
                        Handle.Value.Free();
                    }
                }

                Handles.Clear();

                ObjectToHandleReference.Clear();
            }
        }
    }
}