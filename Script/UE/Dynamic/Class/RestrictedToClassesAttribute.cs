using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class RestrictedToClassesAttribute : Attribute
    {
        public RestrictedToClassesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}