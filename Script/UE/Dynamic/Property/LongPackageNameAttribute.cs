using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LongPackageNameAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}