using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MapKeyParamAttribute : Attribute
    {
        public MapKeyParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}