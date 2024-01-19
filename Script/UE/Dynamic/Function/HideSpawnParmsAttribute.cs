using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HideSpawnParmsAttribute : Attribute
    {
        public HideSpawnParmsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}