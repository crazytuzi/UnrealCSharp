using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ClassGroupAttribute : Attribute
    {
        public ClassGroupAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}