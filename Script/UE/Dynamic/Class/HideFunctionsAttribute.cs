using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HideFunctionsAttribute : Attribute
    {
        public HideFunctionsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}