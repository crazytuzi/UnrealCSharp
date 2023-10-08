using System;

namespace Script.Common
{
    public class FText
    {
        public FText(string InValue) => Value = InValue;

        public static implicit operator FText(string InValue) => new FText(InValue);

        public static Boolean operator ==(FText A, FText B) => A.Value == B.Value;

        public static Boolean operator !=(FText A, FText B) => A.Value != B.Value;

        public override string ToString() => Value;

        private readonly string Value;
    }
}