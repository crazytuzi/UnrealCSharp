using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ProhibitedInterfacesAttribute : Attribute
    {
        public ProhibitedInterfacesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}