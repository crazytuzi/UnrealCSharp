using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExposeFunctionCategoriesAttribute : Attribute
    {
        public ExposeFunctionCategoriesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}