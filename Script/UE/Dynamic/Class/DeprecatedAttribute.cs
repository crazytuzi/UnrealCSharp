using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DeprecatedAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}