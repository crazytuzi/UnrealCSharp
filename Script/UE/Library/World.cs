using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Engine
{
    public partial class UWorld
    {
        public T SpawnActor<T>(UClass Class, FTransform Transform, FActorSpawnParameters ActorSpawnParameters = null)
            where T : AActor
        {
            return WorldImplementation.World_SpawnActorImplementation(GetHandle(),
                Class.GetHandle(),
                Transform.GetHandle(),
                ActorSpawnParameters?.GetHandle() ?? IntPtr.Zero) as T;
        }

        public T SpawnActor<T>(FTransform Transform, FActorSpawnParameters ActorSpawnParameters = null)
            where T : AActor, IStaticClass
        {
            return SpawnActor<T>(T.StaticClass(), Transform, ActorSpawnParameters);
        }
    }
}