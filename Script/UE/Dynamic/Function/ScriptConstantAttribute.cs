using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptConstantAttribute : Attribute
    {
        public ScriptConstantAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}