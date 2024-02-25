using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintAutoCastAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}