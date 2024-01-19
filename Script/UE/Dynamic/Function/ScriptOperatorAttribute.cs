using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptOperatorAttribute : Attribute
    {
        public ScriptOperatorAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}