using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DisableSplitPinAttribute : Attribute
    {
        public DisableSplitPinAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}