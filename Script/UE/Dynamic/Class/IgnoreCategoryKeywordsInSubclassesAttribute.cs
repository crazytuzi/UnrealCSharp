using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IgnoreCategoryKeywordsInSubclassesAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public IgnoreCategoryKeywordsInSubclassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public IgnoreCategoryKeywordsInSubclassesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}