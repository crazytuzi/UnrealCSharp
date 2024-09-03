using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface)]
    public class CannotImplementInterfaceInBlueprintAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}