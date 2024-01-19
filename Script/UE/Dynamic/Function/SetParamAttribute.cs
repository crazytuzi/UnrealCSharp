using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class SetParamAttribute : Attribute
    {
        public SetParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}