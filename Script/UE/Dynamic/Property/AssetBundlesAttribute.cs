using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AssetBundlesAttribute : Attribute
    {
        public AssetBundlesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}