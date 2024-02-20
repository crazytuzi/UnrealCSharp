using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class PrioritizeCategoriesAttribute : Attribute
    {
        public PrioritizeCategoriesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}