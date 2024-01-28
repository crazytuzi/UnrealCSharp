using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LatentCallbackTargetAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}