using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IgnoreCategoryKeywordsInSubclassesAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}