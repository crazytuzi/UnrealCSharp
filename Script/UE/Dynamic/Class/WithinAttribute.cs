using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class WithinAttribute : Attribute
    {
        public WithinAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}