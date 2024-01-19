using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceShowPluginContentAttribute : Attribute
    {
        public ForceShowPluginContentAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}