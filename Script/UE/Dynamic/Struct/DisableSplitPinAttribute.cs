using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DisableSplitPinAttribute : UStructAttribute
    {
    public string MetaValue { get; set; }
    public DisableSplitPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DisableSplitPinAttribute()
    {
        this.MetaValue = "true";
    }
    }
}