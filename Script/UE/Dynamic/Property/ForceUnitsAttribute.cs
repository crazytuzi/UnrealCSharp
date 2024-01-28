using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceUnitsAttribute : Attribute
    {
        public ForceUnitsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}