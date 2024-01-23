using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LinearDeltaSensitivityAttribute : Attribute
    {
        public LinearDeltaSensitivityAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}