using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisallowedClassesAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DisallowedClassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}