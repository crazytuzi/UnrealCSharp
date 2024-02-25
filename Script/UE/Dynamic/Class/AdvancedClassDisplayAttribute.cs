using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class AdvancedClassDisplayAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}