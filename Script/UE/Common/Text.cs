using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FText : IGarbageCollectionHandle
    {
        public FText()
        {
        }

        ~FText() => TextImplementation.Text_UnRegisterImplementation(GarbageCollectionHandle);

        public FText(string InValue) => TextImplementation.Text_RegisterImplementation(this, InValue);

        public static implicit operator FText(string InValue) => new(InValue);

        public static bool operator ==(FText A, FText B) =>
            TextImplementation.Text_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(FText A, FText B) =>
            !TextImplementation.Text_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as FText;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() => TextImplementation.Text_ToStringImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}