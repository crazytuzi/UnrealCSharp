using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativeToGameContentDirAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}