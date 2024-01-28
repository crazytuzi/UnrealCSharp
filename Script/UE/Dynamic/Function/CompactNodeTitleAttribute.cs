using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CompactNodeTitleAttribute : Attribute
    {
        public CompactNodeTitleAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}