using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class CustomizePropertyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public CustomizePropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}