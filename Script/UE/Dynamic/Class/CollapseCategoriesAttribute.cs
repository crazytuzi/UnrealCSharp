using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class CollapseCategoriesAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}