using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class AutoCollapseCategoriesAttribute : Attribute
    {
        public AutoCollapseCategoriesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}