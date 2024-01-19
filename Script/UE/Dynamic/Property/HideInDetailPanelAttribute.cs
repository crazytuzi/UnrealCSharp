using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideInDetailPanelAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}