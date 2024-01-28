using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PinShownByDefaultAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}