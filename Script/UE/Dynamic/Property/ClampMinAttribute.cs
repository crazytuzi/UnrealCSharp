using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ClampMinAttribute : Attribute
    {
        public ClampMinAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}