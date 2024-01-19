using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ShowTreeViewAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}