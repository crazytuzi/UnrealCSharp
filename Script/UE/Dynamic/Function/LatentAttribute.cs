using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class LatentAttribute : Attribute
    {
        public LatentAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}