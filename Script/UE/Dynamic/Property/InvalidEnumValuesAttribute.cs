using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class InvalidEnumValuesAttribute : Attribute
    {
        public InvalidEnumValuesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}