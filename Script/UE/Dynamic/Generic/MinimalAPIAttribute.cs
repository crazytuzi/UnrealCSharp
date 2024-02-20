using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class MinimalAPIAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}