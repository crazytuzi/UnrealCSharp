using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MapParamAttribute : Attribute
    {
        public MapParamAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}