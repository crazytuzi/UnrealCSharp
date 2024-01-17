using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class KismetHideOverridesAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public KismetHideOverridesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}