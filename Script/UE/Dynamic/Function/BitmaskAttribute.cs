using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BitmaskAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public BitmaskAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BitmaskAttribute()
    {
        this.MetaValue = "true";
    }
    }
}