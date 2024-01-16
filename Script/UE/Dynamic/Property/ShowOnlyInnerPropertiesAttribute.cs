using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ShowOnlyInnerPropertiesAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ShowOnlyInnerPropertiesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}