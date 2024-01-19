using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintCompilerGeneratedDefaultsAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}