using Script.Dynamic;
using Script.UMG;
using Script.CoreUObject;

namespace Script.CoreUObject
{
    [UClass]
    public partial class UDynamicUserWidget : UUserWidget
    {
        public UDynamicUserWidget()
        {
        }

        [Override]
        public override void Construct()
        {
            base.Construct();
        }

        [Override]
        public override void Destruct()
        {
            base.Destruct();
        }
    }
}