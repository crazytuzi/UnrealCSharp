using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PinShownByDefaultAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public PinShownByDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public PinShownByDefaultAttribute()
    {
        this.MetaValue = "true";
    }
    }
}