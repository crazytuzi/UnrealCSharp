using System;

namespace Script.Common
{
    public class FString
    {
        public FString(string InValue) => Value = InValue;

        public static implicit operator FString(string InValue) => new FString(InValue);

        public static Boolean operator ==(FString A, FString B) => A.Value == B.Value;

        public static Boolean operator !=(FString A, FString B) => A.Value != B.Value;

        public override string ToString() => Value;

        private readonly string Value;
    }
}