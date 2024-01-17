using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class BlueprintThreadSafeAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public BlueprintThreadSafeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BlueprintThreadSafeAttribute()
    {
        this.MetaValue = "true";
    }
    }
}