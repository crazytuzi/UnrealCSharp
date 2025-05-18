﻿using Script.Library;

namespace Script.CoreUObject
{
    public class FText : IGarbageCollectionHandle
    {
        public FText()
        {
        }

        ~FText() => FTextImplementation.FText_UnRegisterImplementation(GarbageCollectionHandle);

        public FText(string InValue) => FTextImplementation.FText_RegisterImplementation(this, InValue);

        public static implicit operator FText(string InValue) => new(InValue);

        public static bool operator ==(FText A, FText B) =>
            Utils.EqualsTo(A, B, FTextImplementation.FText_IdenticalImplementation);

        public static bool operator !=(FText A, FText B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FText;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() => FTextImplementation.FText_ToStringImplementation(GarbageCollectionHandle);

        public static FText CreateFrom(string InBuffer, string InTextNamespace = null, string InPackageNamespace = null,
            bool bRequiresQuotes = false) =>
            FTextImplementation.FText_CreateFromBufferImplementation(InBuffer, InTextNamespace, InPackageNamespace,
                bRequiresQuotes);

        public nint GarbageCollectionHandle { get; set; }
    }
}