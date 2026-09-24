using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintBaseOnlyAttribute : Attribute
    {
        public BlueprintBaseOnlyAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}