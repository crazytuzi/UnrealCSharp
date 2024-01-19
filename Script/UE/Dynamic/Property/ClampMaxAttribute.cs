using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ClampMaxAttribute : Attribute
    {
        public ClampMaxAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}