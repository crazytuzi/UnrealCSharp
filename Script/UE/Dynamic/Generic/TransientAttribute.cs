using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property)]
    public class TransientAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}