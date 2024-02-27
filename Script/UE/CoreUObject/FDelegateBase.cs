namespace Script.CoreUObject
{
    public class FDelegateBase : IGarbageCollectionHandle
    {
        public nint GarbageCollectionHandle { get; set; }
    }
}