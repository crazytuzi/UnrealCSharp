using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class OverridingInputPropertyAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public OverridingInputPropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public OverridingInputPropertyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}