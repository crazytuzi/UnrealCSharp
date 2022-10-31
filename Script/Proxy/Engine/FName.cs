namespace Script.Engine
{
    public class FName
    {
        public FName(string InValue) => Value = InValue;

        public static implicit operator FName(string InValue) => new FName(InValue);

        public override string ToString() => Value;

        private readonly string Value;
    }
}