using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayParamAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}