using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisallowedClassesAttribute : Attribute
    {
        public DisallowedClassesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}