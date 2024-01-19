using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DeprecatedPropertyAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}