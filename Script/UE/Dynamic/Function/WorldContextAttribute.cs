using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class WorldContextAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public WorldContextAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public WorldContextAttribute()
    {
        this.MetaValue = "true";
    }
    }
}