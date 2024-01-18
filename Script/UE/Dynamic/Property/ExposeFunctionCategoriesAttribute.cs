using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExposeFunctionCategoriesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ExposeFunctionCategoriesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ExposeFunctionCategoriesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}