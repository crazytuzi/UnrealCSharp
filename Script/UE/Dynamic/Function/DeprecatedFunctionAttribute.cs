using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DeprecatedFunctionAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}