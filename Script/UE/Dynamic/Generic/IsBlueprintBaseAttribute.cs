using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface)]
    public class IsBlueprintBaseAttribute : Attribute
    {
        public IsBlueprintBaseAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}