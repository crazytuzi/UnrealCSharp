using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptConstantHostAttribute : Attribute
    {
        public ScriptConstantHostAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}