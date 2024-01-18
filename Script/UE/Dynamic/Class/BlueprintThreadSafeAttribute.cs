using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class BlueprintThreadSafeAttribute : Attribute
    {
    public string MetaValue { get; set; }
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