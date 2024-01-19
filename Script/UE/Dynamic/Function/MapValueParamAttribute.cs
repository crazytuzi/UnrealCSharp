using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MapValueParamAttribute : Attribute
    {
        public MapValueParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}