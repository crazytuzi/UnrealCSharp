using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BitmaskAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}