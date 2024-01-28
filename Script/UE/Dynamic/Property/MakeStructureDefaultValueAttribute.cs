using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MakeStructureDefaultValueAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}