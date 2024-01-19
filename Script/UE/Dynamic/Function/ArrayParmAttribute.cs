using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayParmAttribute : Attribute
    {
        public ArrayParmAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}