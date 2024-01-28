using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HasNativeBreakAttribute : Attribute
    {
        public HasNativeBreakAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}