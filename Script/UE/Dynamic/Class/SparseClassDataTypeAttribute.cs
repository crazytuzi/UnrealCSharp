using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class SparseClassDataTypeAttribute : Attribute
    {
        public SparseClassDataTypeAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}