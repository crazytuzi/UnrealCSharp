using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ConstAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}