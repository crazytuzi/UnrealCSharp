using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property)]
    public class EditorConfigAttribute : Attribute
    {
        public EditorConfigAttribute()
        {
            Value = "true";
        }

        public EditorConfigAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}