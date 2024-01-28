using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class TitlePropertyAttribute : Attribute
    {
        public TitlePropertyAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}