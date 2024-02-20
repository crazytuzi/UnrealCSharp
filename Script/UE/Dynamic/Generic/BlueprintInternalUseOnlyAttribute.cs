using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    public class BlueprintInternalUseOnlyAttribute : Attribute
    {
        public BlueprintInternalUseOnlyAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}