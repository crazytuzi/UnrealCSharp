using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class NotPlaceableAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}