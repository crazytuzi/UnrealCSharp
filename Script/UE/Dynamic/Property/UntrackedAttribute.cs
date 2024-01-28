using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UntrackedAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}