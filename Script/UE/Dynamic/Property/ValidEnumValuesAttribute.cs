using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ValidEnumValuesAttribute : Attribute
    {
        public ValidEnumValuesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}