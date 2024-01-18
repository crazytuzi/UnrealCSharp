using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class KismetHideOverridesAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public KismetHideOverridesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public KismetHideOverridesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}