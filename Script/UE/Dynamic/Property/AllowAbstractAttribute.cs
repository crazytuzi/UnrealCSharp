using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowAbstractAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public AllowAbstractAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}