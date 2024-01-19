using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NativeMakeFuncAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}