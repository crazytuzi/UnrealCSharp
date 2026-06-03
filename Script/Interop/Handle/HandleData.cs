using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Interop
{
    public static class HandleData
    {
        private static readonly Dictionary<nint, GCHandle> Entities = new();

        private static nint Identity;

        private sealed class IdentityComparer : IEqualityComparer<object>
        {
            bool IEqualityComparer<object>.Equals(object? A, object? B) => ReferenceEquals(A, B);

            public int GetHashCode(object InObject) => RuntimeHelpers.GetHashCode(InObject);
        }

        private sealed class IdentityReference
        {
            public nint Value;

            public int Count;
        }

        private static readonly Dictionary<object, IdentityReference> ObjectToIdentityReference =
            new(new IdentityComparer());

        [UnmanagedCallersOnly]
        public static nint Alloc(nint InObjectPtr, int bPinned)
        {
            if (InObjectPtr != 0)
            {
                var Handle = GCHandle.FromIntPtr(InObjectPtr);

                if (Handle.IsAllocated)
                {
                    var Target = Handle.Target;

                    if (Target != null)
                    {
                        return AllocImplementation(Target, bPinned != 0);
                    }
                }
            }

            return 0;
        }

        [UnmanagedCallersOnly]
        public static nint AllocWeakRef(nint InObjectPtr, int bTrackResurrection)
        {
            if (InObjectPtr != 0)
            {
                var Handle = GCHandle.FromIntPtr(InObjectPtr);

                if (Handle.IsAllocated)
                {
                    var Target = Handle.Target;

                    if (Target != null)
                    {
                        var NewIdentity = ++Identity;

                        Entities[NewIdentity] = GCHandle.Alloc(
                            Target,
                            bTrackResurrection != 0
                                ? GCHandleType.WeakTrackResurrection
                                : GCHandleType.Weak);

                        return NewIdentity;
                    }
                }
            }

            return 0;
        }

        [UnmanagedCallersOnly]
        public static nint GetTarget(nint InHandle)
        {
            if (InHandle != 0)
            {
                if (Entities.TryGetValue(InHandle, out var OutHandle))
                {
                    if (OutHandle is { IsAllocated: true, Target: not null })
                    {
                        return GCHandle.ToIntPtr(OutHandle);
                    }
                }
            }

            return 0;
        }

        [UnmanagedCallersOnly]
        public static void Free(nint InHandle) => FreeImplementation(InHandle);

        public static nint AllocImplementation(object InObject, bool bPinned = false)
        {
            if (ObjectToIdentityReference.TryGetValue(InObject, out var OutIdentityReference))
            {
                OutIdentityReference.Count++;

                return OutIdentityReference.Value;
            }

            var NewIdentity = ++Identity;

            var Handle = GCHandle.Alloc(InObject, bPinned ? GCHandleType.Pinned : GCHandleType.Normal);

            Entities[NewIdentity] = Handle;

            ObjectToIdentityReference[InObject] = new IdentityReference { Value = NewIdentity, Count = 1 };

            return NewIdentity;
        }

        public static void FreeImplementation(nint InHandle)
        {
            if (InHandle != 0)
            {
                if (Entities.TryGetValue(InHandle, out var OutHandle) && OutHandle.IsAllocated)
                {
                    var Target = OutHandle.Target;

                    if (Target != null)
                    {
                        if (ObjectToIdentityReference.TryGetValue(Target, out var OutIdentityReference))
                        {
                            if (OutIdentityReference.Value == InHandle)
                            {
                                OutIdentityReference.Count--;

                                if (OutIdentityReference.Count > 0)
                                {
                                    return;
                                }

                                ObjectToIdentityReference.Remove(Target);
                            }
                        }
                    }
                }

                if (Entities.Remove(InHandle, out var RemovedHandle))
                {
                    if (RemovedHandle.IsAllocated)
                    {
                        RemovedHandle.Free();
                    }
                }
            }
        }

        public static object? GetObject(nint InHandle)
        {
            if (InHandle != 0)
            {
                if (Entities.TryGetValue(InHandle, out var OutHandle))
                {
                    return OutHandle.Target;
                }
            }

            return null;
        }

        internal static GCHandle GetHandle(nint InHandle)
        {
            if (InHandle != 0)
            {
                if (Entities.TryGetValue(InHandle, out var OutHandle))
                {
                    return OutHandle;
                }
            }

            return default;
        }

        internal static nint AddEntity(GCHandle InHandle)
        {
            var NewIdentity = ++Identity;

            Entities[NewIdentity] = InHandle;

            return NewIdentity;
        }

        internal static void Clear()
        {
            foreach (var Entity in Entities)
            {
                if (Entity.Value.IsAllocated)
                {
                    Entity.Value.Free();
                }
            }

            Entities.Clear();

            ObjectToIdentityReference.Clear();
        }
    }
}