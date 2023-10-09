using System;

namespace Script.Common
{
    public class FName
    {
        public FName(string InValue) => Value = InValue;

        public static implicit operator FName(string InValue) => new FName(InValue);

        public static Boolean operator ==(FName A, FName B) => A.Value == B.Value;

        public static Boolean operator !=(FName A, FName B) => A.Value != B.Value;

        public override string ToString() => Value;

        private readonly string Value;
    }
}