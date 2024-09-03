using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum | AttributeTargets.Interface)]
    public class BlueprintTypeAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}