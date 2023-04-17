namespace Script.Common
{
    public class FText
    {
        public FText(string InValue) => Value = InValue;

        public static implicit operator FText(string InValue) => new FText(InValue);

        public override string ToString() => Value;

        private readonly string Value;
    }
}