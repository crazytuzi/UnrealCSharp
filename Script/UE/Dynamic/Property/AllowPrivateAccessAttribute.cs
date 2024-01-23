using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowPrivateAccessAttribute : Attribute
    {
        public AllowPrivateAccessAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}