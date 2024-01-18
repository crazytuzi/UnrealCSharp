using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CustomStructureParamAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public CustomStructureParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public CustomStructureParamAttribute()
    {
        this.MetaValue = "true";
    }
    }
}