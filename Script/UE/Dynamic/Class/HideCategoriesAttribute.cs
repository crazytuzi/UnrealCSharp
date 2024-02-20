using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HideCategoriesAttribute : Attribute
    {
        public HideCategoriesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}