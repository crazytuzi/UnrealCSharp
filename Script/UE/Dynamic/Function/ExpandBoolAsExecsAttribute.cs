using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ExpandBoolAsExecsAttribute : Attribute
    {
        public ExpandBoolAsExecsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}