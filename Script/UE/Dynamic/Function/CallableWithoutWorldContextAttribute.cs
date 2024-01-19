using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CallableWithoutWorldContextAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}