using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowedClassesAttribute : Attribute
    {
        public AllowedClassesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}