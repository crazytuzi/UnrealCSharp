using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class LatentInfoAttribute : Attribute
    {
        public LatentInfoAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}