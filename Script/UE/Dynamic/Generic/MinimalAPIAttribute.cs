using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface)]
    public class MinimalAPIAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}