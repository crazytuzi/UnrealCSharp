using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DefaultValueAttribute : Attribute
    {
        public DefaultValueAttribute(string InValue)
        {
            Value = InValue;
        }

        public DefaultValueAttribute(bool InValue)
        {
            Value = InValue.ToString();
        }

        public DefaultValueAttribute(int InValue)
        {
            Value = InValue.ToString();
        }

        public DefaultValueAttribute(long InValue)
        {
            Value = InValue.ToString();
        }

        public DefaultValueAttribute(byte InValue)
        {
            Value = InValue.ToString();
        }

        public DefaultValueAttribute(float InValue)
        {
            Value = InValue.ToString(System.Globalization.CultureInfo.InvariantCulture);
        }

        public DefaultValueAttribute(double InValue)
        {
            Value = InValue.ToString(System.Globalization.CultureInfo.InvariantCulture);
        }

        private string Value { get; set; }
    }
}