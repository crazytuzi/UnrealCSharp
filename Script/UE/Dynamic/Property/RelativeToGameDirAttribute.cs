using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativeToGameDirAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}