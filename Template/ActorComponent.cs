using Script.CoreUObject;
using Script.Engine;

namespace Script.Engine
{
	[Override]
	public partial class UActorComponent
	{
		private UActorComponent()
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