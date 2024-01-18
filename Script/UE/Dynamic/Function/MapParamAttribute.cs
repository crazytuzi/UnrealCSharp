using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MapParamAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MapParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MapParamAttribute()
    {
        this.MetaValue = "true";
    }
    }
}