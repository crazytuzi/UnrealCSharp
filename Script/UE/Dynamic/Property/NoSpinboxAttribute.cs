using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoSpinboxAttribute : Attribute
    {
        public NoSpinboxAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}