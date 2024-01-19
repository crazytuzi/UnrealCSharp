using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ChildCanTickAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}