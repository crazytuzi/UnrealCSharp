using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class CustomThunkTemplatesAttribute : Attribute
    {
        public CustomThunkTemplatesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}