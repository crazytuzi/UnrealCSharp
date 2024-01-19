using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class AutoCreateRefTermAttribute : Attribute
    {
        public AutoCreateRefTermAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}