using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PasswordFieldAttribute : Attribute
    {
        public PasswordFieldAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}