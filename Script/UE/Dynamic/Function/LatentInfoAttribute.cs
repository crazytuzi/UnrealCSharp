using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class LatentInfoAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public LatentInfoAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public LatentInfoAttribute()
    {
        this.MetaValue = "true";
    }
    }
}