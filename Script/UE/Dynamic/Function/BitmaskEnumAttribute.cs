using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BitmaskEnumAttribute : Attribute
    {
        public BitmaskEnumAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}