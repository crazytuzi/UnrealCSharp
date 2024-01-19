using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class SliderExponentAttribute : Attribute
    {
        public SliderExponentAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}