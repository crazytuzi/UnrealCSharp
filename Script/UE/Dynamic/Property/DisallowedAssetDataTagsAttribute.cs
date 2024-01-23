using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisallowedAssetDataTagsAttribute : Attribute
    {
        public DisallowedAssetDataTagsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}