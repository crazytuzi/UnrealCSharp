using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class GetOptionsAttribute : Attribute
    {
        public GetOptionsAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}