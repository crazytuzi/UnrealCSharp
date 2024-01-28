using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    public class BlueprintThreadSafeAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}