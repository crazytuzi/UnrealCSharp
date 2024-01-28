using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintAutocastAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}