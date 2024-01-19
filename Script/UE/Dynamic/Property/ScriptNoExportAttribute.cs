using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ScriptNoExportAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}