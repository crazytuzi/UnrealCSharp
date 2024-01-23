using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class DisplayNameAttribute : Attribute
    {
        public DisplayNameAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}