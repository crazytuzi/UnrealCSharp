using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DynamicOutputParamAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DynamicOutputParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DynamicOutputParamAttribute()
    {
        this.MetaValue = "true";
    }
    }
}