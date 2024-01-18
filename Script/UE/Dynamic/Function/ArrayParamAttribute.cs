using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayParamAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ArrayParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ArrayParamAttribute()
    {
        this.MetaValue = "true";
    }
    }
}