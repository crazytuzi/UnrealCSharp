using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface)]
    public class ConversionRootAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}