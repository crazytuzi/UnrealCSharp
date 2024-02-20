using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum)]
    public class ExperimentalAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}