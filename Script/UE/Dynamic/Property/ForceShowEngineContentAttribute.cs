using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceShowEngineContentAttribute : Attribute
    {
        public ForceShowEngineContentAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}