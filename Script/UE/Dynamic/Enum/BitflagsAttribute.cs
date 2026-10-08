using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Enum)]
    public class BitflagsAttribute : Attribute
    {
        public BitflagsAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}