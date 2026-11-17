using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class IgnoreForMemberInitializationTestAttribute : Attribute
    {
        public IgnoreForMemberInitializationTestAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}