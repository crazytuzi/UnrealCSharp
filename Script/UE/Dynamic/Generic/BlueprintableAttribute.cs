using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum | AttributeTargets.Interface)]
    public class BlueprintableAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}