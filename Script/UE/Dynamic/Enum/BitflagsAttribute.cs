using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Enum)]
    public class BitflagsAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}