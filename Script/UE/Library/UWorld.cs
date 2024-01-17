using Script.CoreUObject;
using Script.Library;

namespace Script.Engine
{
    public partial class UWorld
    {
        public T SpawnActor<T>(UClass Class, FTransform Transform, FActorSpawnParameters ActorSpawnParameters = null)
            where T : AActor =>
            UWorldImplementation.UWorld_SpawnActorImplementation<T>(GarbageCollectionHandle,
                Class.GarbageCollectionHandle,
                Transform.GarbageCollectionHandle,
                ActorSpawnParameters?.GarbageCollectionHandle ?? nint.Zero);

        public T SpawnActor<T>(FTransform Transform, FActorSpawnParameters ActorSpawnParameters = null)
            where T : AActor, IStaticClass =>
            SpawnActor<T>(T.StaticClass(), Transform, ActorSpawnParameters);
    }
}