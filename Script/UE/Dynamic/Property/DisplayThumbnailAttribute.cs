using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayThumbnailAttribute : Attribute
    {
        public DisplayThumbnailAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}