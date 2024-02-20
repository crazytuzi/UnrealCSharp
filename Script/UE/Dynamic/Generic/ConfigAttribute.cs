using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property)]
    public class ConfigAttribute : Attribute
    {
        public ConfigAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}