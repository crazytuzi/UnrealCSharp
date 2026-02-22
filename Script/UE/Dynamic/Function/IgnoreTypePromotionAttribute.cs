using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class IgnoreTypePromotionAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}