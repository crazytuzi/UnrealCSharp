using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ShowWorldContextPinAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}