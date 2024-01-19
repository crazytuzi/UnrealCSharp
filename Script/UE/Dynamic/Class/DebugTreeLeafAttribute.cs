using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DebugTreeLeafAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}