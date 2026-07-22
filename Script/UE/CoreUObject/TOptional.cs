#if UE_5_3_OR_LATER
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TOptional<T>
    {
        public TOptional() => TOptionalImplementation.TOptional_Register1Implementation(this, GetType());

        public TOptional(T InObject) =>
            TOptionalImplementation.TOptional_Register2Implementation(this, InObject, GetType());

        ~TOptional() => TOptionalImplementation.TOptional_UnRegisterImplementation(HandleData.GetHandle(this));

        public static bool operator ==(TOptional<T> A, TOptional<T> B)
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
                   TOptionalImplementation.TOptional_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TOptional<T> A, TOptional<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TOptional<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public void Reset() => TOptionalImplementation.TOptional_ResetImplementation(HandleData.GetHandle(this));

        public bool IsSet() => TOptionalImplementation.TOptional_IsSetImplementation(HandleData.GetHandle(this));

        public T Get() => (T)TOptionalImplementation.TOptional_GetImplementation(HandleData.GetHandle(this));

        public void Set(T InValue) =>
            TOptionalImplementation.TOptional_SetImplementation(HandleData.GetHandle(this), InValue);
    }
}
#endif