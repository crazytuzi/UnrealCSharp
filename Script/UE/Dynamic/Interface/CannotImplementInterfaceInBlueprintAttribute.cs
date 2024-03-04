using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class CannotImplementInterfaceInBlueprintAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}