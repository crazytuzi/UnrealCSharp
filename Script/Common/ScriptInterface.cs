using Script.CoreUObject;

namespace Script.Common
{
    public class TScriptInterface<T> where T : IInterface
    {
        public TScriptInterface()
        {
        }

        public TScriptInterface(UClass InClass) => Value = InClass;

        public UClass Get() => Value;

        private readonly UClass Value;
    }
}