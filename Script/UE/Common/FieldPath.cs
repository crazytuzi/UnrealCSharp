using Script.Reflection.Property;

namespace Script.Common
{
    public class TFieldPath<T> where T : FField
    {
        public TFieldPath()
        {
        }

        public TFieldPath(T InObject) => Value = InObject;

        public T Get() => Value;

        private readonly T Value;
    }
}