using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class FilePathFilterAttribute : Attribute
    {
        public FilePathFilterAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}