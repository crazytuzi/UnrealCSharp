using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HideAssetPickerAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}