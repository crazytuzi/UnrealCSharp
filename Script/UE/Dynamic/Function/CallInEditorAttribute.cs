using System;
using Script.Common;
namespace Script.Dynamic
{
	[AttributeUsage(AttributeTargets.Method)]
	public class CallInEditorAttribute : Attribute
	{
		public string MetaValue { get; set; }
		public CallInEditorAttribute ()
		{
			this.MetaValue = "true";
		}
		public CallInEditorAttribute (string value)
		{
			MetaValue = value;
		}
	}
}