using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExposeFunctionCategoriesAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ExposeFunctionCategoriesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}