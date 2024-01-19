using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class UsesHierarchyAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}