using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class KeywordsAttribute : Attribute
    {
        public KeywordsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}