using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class DeprecationMessageAttribute : Attribute
    {
        public DeprecationMessageAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}