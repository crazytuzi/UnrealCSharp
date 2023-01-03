using Script.CoreUObject;

namespace Script.Common
{
    public class TSoftObjectPtr<T> where T : UObject
    {
        public TSoftObjectPtr()
        {
        }

        public TSoftObjectPtr(T InObject) => Value = InObject;

        public T Get() => Value;

        private readonly T Value;
    }
}