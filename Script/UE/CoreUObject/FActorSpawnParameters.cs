using Script.Library;

namespace Script.CoreUObject
{
    public partial class FActorSpawnParameters
    {
        public bool bNoFail
        {
            get => FActorSpawnParametersImplementation
                .FActorSpawnParameters_GetbNoFailImplementation(GarbageCollectionHandle);

            set => FActorSpawnParametersImplementation
                .FActorSpawnParameters_SetbNoFailImplementation(GarbageCollectionHandle, value);
        }

        public bool bDeferConstruction
        {
            get => FActorSpawnParametersImplementation
                .FActorSpawnParameters_GetbDeferConstructionImplementation(GarbageCollectionHandle);

            set => FActorSpawnParametersImplementation
                .FActorSpawnParameters_SetbDeferConstructionImplementation(GarbageCollectionHandle, value);
        }

        public bool bAllowDuringConstructionScript
        {
            get => FActorSpawnParametersImplementation
                .FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation(GarbageCollectionHandle);

            set => FActorSpawnParametersImplementation
                .FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation(GarbageCollectionHandle, value);
        }
    }
}