using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class WorldContextAttribute : Attribute
    {
        public WorldContextAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}