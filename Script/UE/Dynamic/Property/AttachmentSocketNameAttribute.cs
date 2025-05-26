using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AttachmentSocketNameAttribute : Attribute
    {
        public AttachmentSocketNameAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}