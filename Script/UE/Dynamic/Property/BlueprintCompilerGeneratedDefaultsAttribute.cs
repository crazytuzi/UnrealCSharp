using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintCompilerGeneratedDefaultsAttribute : Attribute
    {
        public BlueprintCompilerGeneratedDefaultsAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}