using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MultipleAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}