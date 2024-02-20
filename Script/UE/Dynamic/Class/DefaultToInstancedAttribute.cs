using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DefaultToInstancedAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}