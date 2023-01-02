using Script.CoreUObject;

namespace Script.Common
{
    public class TWeakObjectPtr<T> where T : UObject
    {
        public TWeakObjectPtr()
        {
        }

        public TWeakObjectPtr(T InObject) => Value = InObject;

        public T Get() => Value;

        private readonly T Value;
    }
}