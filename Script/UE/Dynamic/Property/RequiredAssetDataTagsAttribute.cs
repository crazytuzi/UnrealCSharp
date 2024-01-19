using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RequiredAssetDataTagsAttribute : Attribute
    {
        public RequiredAssetDataTagsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}