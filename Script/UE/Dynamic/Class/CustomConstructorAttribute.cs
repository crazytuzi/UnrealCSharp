using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class CustomConstructorAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}