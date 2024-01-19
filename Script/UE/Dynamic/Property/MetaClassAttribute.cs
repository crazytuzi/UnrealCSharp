using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MetaClassAttribute : Attribute
    {
        public MetaClassAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}