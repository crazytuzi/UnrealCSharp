using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class DocumentationPolicyAttribute : Attribute
    {
        public DocumentationPolicyAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}