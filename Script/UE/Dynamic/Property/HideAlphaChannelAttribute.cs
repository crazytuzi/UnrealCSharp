using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideAlphaChannelAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}