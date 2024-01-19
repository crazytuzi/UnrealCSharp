using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UIMinAttribute : Attribute
    {
        public UIMinAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}