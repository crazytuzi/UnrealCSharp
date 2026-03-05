using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ForceAsFunctionAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}