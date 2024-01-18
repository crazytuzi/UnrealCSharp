using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MapValueParamAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MapValueParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MapValueParamAttribute()
    {
        this.MetaValue = "true";
    }
    }
}