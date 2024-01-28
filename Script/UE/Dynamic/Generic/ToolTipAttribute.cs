using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class ToolTipAttribute : Attribute
    {
        public ToolTipAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}