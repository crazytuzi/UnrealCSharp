using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RequiredInputAttribute : Attribute
    {
        public RequiredInputAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}