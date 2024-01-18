using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class SetParamAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public SetParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public SetParamAttribute()
    {
        this.MetaValue = "true";
    }
    }
}