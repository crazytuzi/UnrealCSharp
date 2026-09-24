using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ShowWorldContextPinAttribute : Attribute
    {
        public ShowWorldContextPinAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}