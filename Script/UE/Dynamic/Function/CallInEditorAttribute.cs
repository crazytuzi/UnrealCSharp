using System;
using Script.Common;
namespace Script.Dynamic
{
	[AttributeUsage(AttributeTargets.Method)]
	public class CallInEditorAttribute : Attribute
	{
		private string MetaValue;
		public string DisplayValue
		{
			get { return MetaValue; }
			set { MetaValue = value; }
		}
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