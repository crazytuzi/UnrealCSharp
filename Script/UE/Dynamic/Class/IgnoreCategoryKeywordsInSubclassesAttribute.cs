using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IgnoreCategoryKeywordsInSubclassesAttribute : Attribute
    {
        public IgnoreCategoryKeywordsInSubclassesAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}