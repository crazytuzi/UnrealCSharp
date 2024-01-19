using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DeterminesOutputTypeAttribute : Attribute
    {
        public DeterminesOutputTypeAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}