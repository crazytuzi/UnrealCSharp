using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public partial class FActorSpawnParameters
    {
        public bool bNoFail
        {
            get => FActorSpawnParametersImplementation
                .FActorSpawnParameters_GetbNoFailImplementation(HandleData.GetHandle(this));

            set => FActorSpawnParametersImplementation
                .FActorSpawnParameters_SetbNoFailImplementation(HandleData.GetHandle(this), value);
        }

        public bool bDeferConstruction
        {
            get => FActorSpawnParametersImplementation
                .FActorSpawnParameters_GetbDeferConstructionImplementation(HandleData.GetHandle(this));

            set => FActorSpawnParametersImplementation
                .FActorSpawnParameters_SetbDeferConstructionImplementation(HandleData.GetHandle(this), value);
        }

        public bool bAllowDuringConstructionScript
        {
            get => FActorSpawnParametersImplementation
                .FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation(HandleData.GetHandle(this));

            set => FActorSpawnParametersImplementation
                .FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation(HandleData.GetHandle(this),
                    value);
        }
    }
}