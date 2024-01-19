using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ExpandEnumAsExecsAttribute : Attribute
    {
        public ExpandEnumAsExecsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}