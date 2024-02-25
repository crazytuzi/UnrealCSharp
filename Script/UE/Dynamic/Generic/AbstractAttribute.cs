using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class AbstractAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}