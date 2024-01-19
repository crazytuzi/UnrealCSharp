using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class ShortTooltipAttribute : Attribute
    {
        public ShortTooltipAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}