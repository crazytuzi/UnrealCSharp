using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HasNativeMakeAttribute : Attribute
    {
        public HasNativeMakeAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}