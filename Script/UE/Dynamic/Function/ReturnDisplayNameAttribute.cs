using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ReturnDisplayNameAttribute : Attribute
    {
        public ReturnDisplayNameAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}