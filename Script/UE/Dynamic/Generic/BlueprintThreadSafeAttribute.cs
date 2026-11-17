using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    public class BlueprintThreadSafeAttribute : Attribute
    {
        public BlueprintThreadSafeAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}