using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HidePinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public HidePinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HidePinAttribute()
    {
        this.MetaValue = "true";
    }
    }
}