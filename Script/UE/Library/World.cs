using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Engine
{
    public partial class UWorld
    {
        // @TODO
        public T SpawnActor<T>(UClass Class, FTransform Transform, AActor Owner = null, APawn Instigator = null,
            ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod.Undefined)
            where T : UObject
        {
            WorldImplementation.World_SpawnActorImplementation<T>(GetHandle(), Class.GetHandle(), Transform,
                Owner?.GetHandle() ?? IntPtr.Zero, Instigator?.GetHandle() ?? IntPtr.Zero, CollisionHandlingOverride,
                out var OutValue);

            return OutValue;
        }

        public T SpawnActor<T>(FTransform Transform, AActor Owner = null, APawn Instigator = null,
            ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod.Undefined)
            where T : UObject, IStaticClass
        {
            WorldImplementation.World_SpawnActorImplementation<T>(GetHandle(), T.StaticClass().GetHandle(), Transform,
                Owner?.GetHandle() ?? IntPtr.Zero, Instigator?.GetHandle() ?? IntPtr.Zero, CollisionHandlingOverride,
                out var OutValue);

            return OutValue;
        }
    }
}