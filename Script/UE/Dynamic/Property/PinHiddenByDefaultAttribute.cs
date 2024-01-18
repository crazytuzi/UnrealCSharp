using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PinHiddenByDefaultAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public PinHiddenByDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public PinHiddenByDefaultAttribute()
    {
        this.MetaValue = "true";
    }
    }
}