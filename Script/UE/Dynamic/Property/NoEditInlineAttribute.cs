using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoEditInlineAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}