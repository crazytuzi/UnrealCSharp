using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IgnoreCategoryKeywordsInSubclassesAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public IgnoreCategoryKeywordsInSubclassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}