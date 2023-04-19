using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TWeakObjectPtr<T> where T : UObject
    {
        public TWeakObjectPtr()
        {
        }

        ~TWeakObjectPtr() => WeakObjectPtrImplementation.WeakObjectPtr_UnRegisterImplementation(this);

        public TWeakObjectPtr(T InObject) =>
            WeakObjectPtrImplementation.WeakObjectPtr_RegisterImplementation(this, InObject);

        public static implicit operator TWeakObjectPtr<T>(T InObject) => new TWeakObjectPtr<T>(InObject);

        public T Get()
        {
            WeakObjectPtrImplementation.WeakObjectPtr_GetImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}