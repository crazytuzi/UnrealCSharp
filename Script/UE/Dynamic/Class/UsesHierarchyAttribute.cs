using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class UsesHierarchyAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public UsesHierarchyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}