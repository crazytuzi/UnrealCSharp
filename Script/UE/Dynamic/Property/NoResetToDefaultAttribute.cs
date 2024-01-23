using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoResetToDefaultAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}