using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DeprecatedFunctionAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
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