using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NotBlueprintThreadSafeAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}