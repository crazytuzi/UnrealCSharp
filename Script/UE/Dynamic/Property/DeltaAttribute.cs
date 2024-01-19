using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DeltaAttribute : Attribute
    {
        public DeltaAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}