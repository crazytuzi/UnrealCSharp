using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class LatentAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}