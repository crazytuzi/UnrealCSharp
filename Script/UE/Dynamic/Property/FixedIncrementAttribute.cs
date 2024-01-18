using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class FixedIncrementAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public FixedIncrementAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public FixedIncrementAttribute()
    {
        this.MetaValue = "true";
    }
    }
}