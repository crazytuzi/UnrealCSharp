using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class EditInlineNewAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}