using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintBaseOnlyAttribute : Attribute
    {
        public BlueprintBaseOnlyAttribute()
        {
            Value = "true";
        }

        public BlueprintBaseOnlyAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}