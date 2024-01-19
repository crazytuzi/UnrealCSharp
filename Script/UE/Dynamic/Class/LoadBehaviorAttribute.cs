using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property)]
    public class LoadBehaviorAttribute : Attribute
    {
        public LoadBehaviorAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}