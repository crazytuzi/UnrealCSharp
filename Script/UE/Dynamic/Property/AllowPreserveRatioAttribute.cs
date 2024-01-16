using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowPreserveRatioAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public AllowPreserveRatioAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}