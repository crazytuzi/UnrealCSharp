using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class AutoExpandCategoriesAttribute : Attribute
    {
        public AutoExpandCategoriesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}