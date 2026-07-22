using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public void RemoveFunction(FName InName) =>
            UClassImplementation.UClass_RemoveFunctionImplementation(HandleData.GetHandle(this),
                HandleData.GetHandle(InName));
    }
}