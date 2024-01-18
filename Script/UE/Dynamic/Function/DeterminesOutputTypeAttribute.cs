using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DeterminesOutputTypeAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DeterminesOutputTypeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DeterminesOutputTypeAttribute()
    {
        this.MetaValue = "true";
    }
    }
}