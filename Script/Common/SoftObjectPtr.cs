using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSoftObjectPtr<T> where T : UObject
    {
        public TSoftObjectPtr()
        {
        }

        ~TSoftObjectPtr() => SoftObjectPtrImplementation.SoftObjectPtr_UnRegisterImplementation(this);

        public TSoftObjectPtr(T InObject) =>
            SoftObjectPtrImplementation.SoftObjectPtr_RegisterImplementation(this, InObject);

        public static implicit operator TSoftObjectPtr<T>(T InObject) => new TSoftObjectPtr<T>(InObject);

        public T Get()
        {
            SoftObjectPtrImplementation.SoftObjectPtr_GetImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}