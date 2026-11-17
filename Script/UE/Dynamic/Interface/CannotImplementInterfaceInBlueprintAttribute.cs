using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface)]
    public class CannotImplementInterfaceInBlueprintAttribute : Attribute
    {
        public CannotImplementInterfaceInBlueprintAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}