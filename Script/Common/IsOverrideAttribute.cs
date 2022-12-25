using System;

namespace Script.Common
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    public class IsOverrideAttribute : Attribute
    {
        public IsOverrideAttribute(Boolean InIsOverride) => IsOverride = InIsOverride;

        public Boolean IsOverride { get; set; }
    }
}