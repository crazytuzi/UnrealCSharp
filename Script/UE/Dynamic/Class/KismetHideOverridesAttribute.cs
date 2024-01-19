using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class KismetHideOverridesAttribute : UClassAttribute
    {
        public KismetHideOverridesAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}