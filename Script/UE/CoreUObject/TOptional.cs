#if UE_5_3_OR_LATER
using Script.Library;

namespace Script.CoreUObject
{
    public class TOptional<T> : IGarbageCollectionHandle
    {
        public TOptional() => TOptionalImplementation.TOptional_Register1Implementation(this);

        public TOptional(T InObject) => TOptionalImplementation.TOptional_Register2Implementation(this, InObject);

        ~TOptional() => TOptionalImplementation.TOptional_UnRegisterImplementation(GarbageCollectionHandle);

        public static bool operator ==(TOptional<T> A, TOptional<T> B) =>
            Utils.EqualsTo(A, B, TOptionalImplementation.TOptional_IdenticalImplementation);

        public static bool operator !=(TOptional<T> A, TOptional<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TOptional<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public void Reset() => TOptionalImplementation.TOptional_ResetImplementation(GarbageCollectionHandle);

        public bool IsSet() => TOptionalImplementation.TOptional_IsSetImplementation(GarbageCollectionHandle);

        public T Get() => (T)TOptionalImplementation.TOptional_GetImplementation(GarbageCollectionHandle);

        public void Set(T InValue) =>
            TOptionalImplementation.TOptional_SetImplementation(GarbageCollectionHandle, InValue);

        public nint GarbageCollectionHandle { get; set; }
    }
}
#endif