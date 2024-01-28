using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UnsafeDuringActorConstructionAttribute : Attribute
    {
        public UnsafeDuringActorConstructionAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}