using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ExpandEnumAsExecsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ExpandEnumAsExecsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}