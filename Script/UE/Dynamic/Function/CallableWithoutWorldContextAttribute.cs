using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CallableWithoutWorldContextAttribute : Attribute
    {
        public CallableWithoutWorldContextAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}