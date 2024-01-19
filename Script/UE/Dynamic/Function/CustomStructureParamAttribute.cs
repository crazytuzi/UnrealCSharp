using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CustomStructureParamAttribute : Attribute
    {
        public CustomStructureParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}