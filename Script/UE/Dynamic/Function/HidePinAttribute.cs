using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HidePinAttribute : Attribute
    {
        public HidePinAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}