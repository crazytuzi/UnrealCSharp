using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HiddenByDefaultAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}