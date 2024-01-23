using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DataTablePinAttribute : Attribute
    {
        public DataTablePinAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}