using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditConditionAttribute : Attribute
    {
        public EditConditionAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}