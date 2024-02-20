using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HideDropdownAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}