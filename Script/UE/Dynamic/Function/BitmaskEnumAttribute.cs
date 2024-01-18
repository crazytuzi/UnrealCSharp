using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BitmaskEnumAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public BitmaskEnumAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BitmaskEnumAttribute()
    {
        this.MetaValue = "true";
    }
    }
}