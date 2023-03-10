using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TLazyObjectPtr<T> where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        ~TLazyObjectPtr() => LazyObjectPtrImplementation.LazyObjectPtr_UnRegisterImplementation(this);

        public TLazyObjectPtr(T InObject) =>
            LazyObjectPtrImplementation.LazyObjectPtr_RegisterImplementation(this, InObject);

        public static implicit operator TLazyObjectPtr<T>(T InObject) => new TLazyObjectPtr<T>(InObject);

        public T Get()
        {
            LazyObjectPtrImplementation.LazyObjectPtr_GetImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}