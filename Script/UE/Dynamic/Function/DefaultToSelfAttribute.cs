using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DefaultToSelfAttribute : Attribute
    {
        public DefaultToSelfAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}