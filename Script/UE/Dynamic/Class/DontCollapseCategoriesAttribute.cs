using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DontCollapseCategoriesAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}