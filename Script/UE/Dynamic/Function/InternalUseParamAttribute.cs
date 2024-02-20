using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class InternalUseParamAttribute : Attribute
    {
        public InternalUseParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}