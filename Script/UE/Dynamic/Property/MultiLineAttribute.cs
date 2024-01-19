using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MultiLineAttribute : Attribute
    {
        public MultiLineAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}