using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ComponentWrapperClassAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}