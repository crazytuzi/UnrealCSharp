using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NeedsLatentFixupAttribute : Attribute
    {
        public NeedsLatentFixupAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}