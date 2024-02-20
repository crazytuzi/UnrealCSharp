using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DefaultConfigAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}