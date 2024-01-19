using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ShowOnlyInnerPropertiesAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}