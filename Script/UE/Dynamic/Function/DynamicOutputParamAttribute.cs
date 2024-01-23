using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DynamicOutputParamAttribute : Attribute
    {
        public DynamicOutputParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}