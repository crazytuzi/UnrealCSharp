using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ConversionRootAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}