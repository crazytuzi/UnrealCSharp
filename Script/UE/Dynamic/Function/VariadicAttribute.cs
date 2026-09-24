using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class VariadicAttribute : Attribute
    {
        public VariadicAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}