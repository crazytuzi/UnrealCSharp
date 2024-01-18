using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayTypeDependentParamsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ArrayTypeDependentParamsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ArrayTypeDependentParamsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}