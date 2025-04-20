using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AttachmentParentAttribute : Attribute
    {
        public AttachmentParentAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}