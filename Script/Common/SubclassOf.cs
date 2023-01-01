using Script.CoreUObject;

namespace Script.Common
{
    public class TSubclassOf<T> where T : UObject
    {
        public TSubclassOf()
        {
        }

        public TSubclassOf(UClass InClass) => Value = InClass;

        public UClass Get() => Value;

        private readonly UClass Value;
    }
}