using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class PerObjectConfigAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}