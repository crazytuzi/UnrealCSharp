using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class ScriptNameAttribute : Attribute
    {
        public ScriptNameAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}