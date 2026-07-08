using Script.CoreUObject;
using Script.Library;
using Interop;

namespace Script.Engine
{
    public partial class UWorld
    {
        public T SpawnActor<T>(UClass Class, FTransform Transform, FActorSpawnParameters ActorSpawnParameters = null)
            where T : AActor =>
            UWorldImplementation.UWorld_SpawnActorImplementation<T>(HandleData.GetHandle(this),
                HandleData.GetHandle(Class),
                HandleData.GetHandle(Transform),
                HandleData.GetHandle(ActorSpawnParameters));

        public T SpawnActor<T>(FTransform Transform, FActorSpawnParameters ActorSpawnParameters = null)
            where T : AActor, IStaticClass =>
            SpawnActor<T>(T.StaticClass(), Transform, ActorSpawnParameters);
    }
}