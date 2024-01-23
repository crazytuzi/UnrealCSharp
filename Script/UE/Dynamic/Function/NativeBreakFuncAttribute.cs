using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NativeBreakFuncAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}