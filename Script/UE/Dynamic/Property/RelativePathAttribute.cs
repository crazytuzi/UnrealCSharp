using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativePathAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}