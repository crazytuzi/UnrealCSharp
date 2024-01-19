using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DevelopmentOnlyAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}