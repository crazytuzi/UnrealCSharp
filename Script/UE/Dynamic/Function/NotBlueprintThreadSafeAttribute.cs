using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NotBlueprintThreadSafeAttribute : Attribute
    {
        public string MetaValue { get; set; }

        public NotBlueprintThreadSafeAttribute(string MetaValue)
        {
            this.MetaValue = MetaValue;
        }

        public NotBlueprintThreadSafeAttribute()
        {
            this.MetaValue = "true";
        }
    }
}