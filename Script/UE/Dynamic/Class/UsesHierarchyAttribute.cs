using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class UsesHierarchyAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public UsesHierarchyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public UsesHierarchyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}