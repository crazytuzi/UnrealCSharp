using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideViewOptionsAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}