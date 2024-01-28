using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ConfigHierarchyEditableAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}