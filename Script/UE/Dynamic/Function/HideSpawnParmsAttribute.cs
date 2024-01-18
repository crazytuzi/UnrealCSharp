using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HideSpawnParmsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public HideSpawnParmsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HideSpawnParmsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}