using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DeprecatedNodeAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}