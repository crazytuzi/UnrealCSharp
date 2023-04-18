namespace Script.Common
{
    public class FString
    {
        public FString(string InValue) => Value = InValue;

        public static implicit operator FString(string InValue) => new FString(InValue);

        public override string ToString() => Value;

        private readonly string Value;
    }
}