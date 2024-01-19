using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowPreserveRatioAttribute : Attribute
    {
        public AllowPreserveRatioAttribute()
        {
            Value = "true";
        }

        public AllowPreserveRatioAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}