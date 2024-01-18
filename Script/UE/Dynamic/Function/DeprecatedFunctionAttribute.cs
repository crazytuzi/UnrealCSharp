using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DeprecatedFunctionAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DeprecatedFunctionAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DeprecatedFunctionAttribute()
    {
        this.MetaValue = "true";
    }
    }
}