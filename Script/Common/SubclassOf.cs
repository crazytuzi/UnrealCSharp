using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSubclassOf<T> where T : UObject
    {
        public TSubclassOf()
        {
        }

        ~TSubclassOf() => SubclassOfImplementation.SubclassOf_UnRegisterImplementation(this);

        public TSubclassOf(UClass InClass) => Value = InClass;

        public static implicit operator TSubclassOf<T>(UClass InClass)
        {
            var SubclassOf = new TSubclassOf<T>(InClass);

            SubclassOfImplementation.SubclassOf_RegisterImplementation(SubclassOf, InClass);

            return SubclassOf;
        }

        public UClass Get() => Value;

        private readonly UClass Value;
    }
}