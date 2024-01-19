using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UnitsAttribute : Attribute
    {
        public UnitsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}