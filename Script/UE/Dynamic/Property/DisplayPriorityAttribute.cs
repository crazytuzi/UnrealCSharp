using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayPriorityAttribute : Attribute
    {
        public DisplayPriorityAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}