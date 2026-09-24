using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NotBlueprintThreadSafeAttribute : Attribute
    {
        public NotBlueprintThreadSafeAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}