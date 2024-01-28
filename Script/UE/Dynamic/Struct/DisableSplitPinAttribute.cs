using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DisableSplitPinAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}