using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IntrinsicAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}