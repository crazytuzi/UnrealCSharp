using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MustImplementAttribute : Attribute
    {
        public MustImplementAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}