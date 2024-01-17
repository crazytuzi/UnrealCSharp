using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DeprecatedPropertyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DeprecatedPropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}