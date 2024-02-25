using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class NoExportAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}