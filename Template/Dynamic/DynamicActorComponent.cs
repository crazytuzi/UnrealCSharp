using Script.Dynamic;
using Script.Engine;
using Script.CoreUObject;

namespace Script.CoreUObject
{
	[UClass]
	public partial class UMyActorComponent : UActorComponent
	{
		public UMyActorComponent()
		{
		}

		[Override]
		public override void ReceiveBeginPlay()
		{
			base.ReceiveBeginPlay();
		}

		[Override]
		public override void ReceiveEndPlay(EEndPlayReason EndPlayReason)
		{
			base.ReceiveEndPlay(EndPlayReason);
		}
	}
}