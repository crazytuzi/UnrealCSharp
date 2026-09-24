using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintAutoCastAttribute : Attribute
    {
        public BlueprintAutoCastAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}