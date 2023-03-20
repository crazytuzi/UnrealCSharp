using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSoftClassPtr<T> where T : UObject
    {
        public TSoftClassPtr()
        {
        }

        ~TSoftClassPtr() => SoftClassPtrImplementation.SoftClassPtr_UnRegisterImplementation(this);

        public TSoftClassPtr(UClass InClass) =>
            SoftClassPtrImplementation.SoftClassPtr_RegisterImplementation(this, InClass);

        public static implicit operator TSoftClassPtr<T>(UClass InClass) => new TSoftClassPtr<T>(InClass);

        public UClass Get()
        {
            SoftClassPtrImplementation.SoftClassPtr_GetImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}