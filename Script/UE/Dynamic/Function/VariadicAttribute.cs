using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class VariadicAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}