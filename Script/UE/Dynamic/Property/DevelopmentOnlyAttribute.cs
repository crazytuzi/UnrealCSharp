using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DevelopmentOnlyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DevelopmentOnlyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}