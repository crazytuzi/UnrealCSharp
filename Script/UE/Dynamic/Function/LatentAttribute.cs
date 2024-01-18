using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class LatentAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public LatentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public LatentAttribute()
    {
        this.MetaValue = "true";
    }
    }
}