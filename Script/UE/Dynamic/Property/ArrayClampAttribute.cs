using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ArrayClampAttribute : Attribute
    {
        public ArrayClampAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}