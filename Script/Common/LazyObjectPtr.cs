using Script.CoreUObject;

namespace Script.Common
{
    public class TLazyObjectPtr<T> where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        public TLazyObjectPtr(T InObject) => Value = InObject;

        public T Get() => Value;

        private readonly T Value;
    }
}