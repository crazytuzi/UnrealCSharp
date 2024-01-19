using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayTypeDependentParamsAttribute : Attribute
    {
        public ArrayTypeDependentParamsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}