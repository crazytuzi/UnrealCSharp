using Script.CoreUObject;

namespace Script.Common
{
    public class FDelegateBase : IGarbageCollectionHandle
    {
        public nint GarbageCollectionHandle { get; set; }
    }
}