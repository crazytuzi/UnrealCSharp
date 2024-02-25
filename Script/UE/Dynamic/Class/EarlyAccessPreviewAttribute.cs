using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class EarlyAccessPreviewAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}