using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ChildCannotTickAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}