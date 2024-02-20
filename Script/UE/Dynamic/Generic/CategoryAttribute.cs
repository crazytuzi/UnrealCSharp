using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class CategoryAttribute : Attribute
    {
        public CategoryAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}