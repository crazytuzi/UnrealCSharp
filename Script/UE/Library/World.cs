using Script.CoreUObject;
using Script.Library;

namespace Script.Engine
{
    public partial class UWorld
    {
        // @TODO
        public T SpawnActor<T>(UClass Class, FTransform Transform) where T : UObject
        {
            WorldImplementation.World_SpawnActorImplementation<T>(this, Class, Transform, out var OutValue);

            return OutValue;
        }
        public T SpawnActor<T>(FTransform Transform) where T : UObject, IStaticClass
        {
            WorldImplementation.World_SpawnActorImplementation<T>(this, T.StaticClass(), Transform, out var OutValue);

            return OutValue;
        }
    }
}