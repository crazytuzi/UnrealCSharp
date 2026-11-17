using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ShowOnlyInnerPropertiesAttribute : Attribute
    {
        public ShowOnlyInnerPropertiesAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}