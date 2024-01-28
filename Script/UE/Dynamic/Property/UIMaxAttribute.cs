using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UIMaxAttribute : Attribute
    {
        public UIMaxAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}