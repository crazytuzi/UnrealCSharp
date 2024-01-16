using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RequiredInputAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public RequiredInputAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}