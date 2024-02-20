using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ConfigDoNotCheckDefaultsAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}