using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IsBlueprintBaseAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public IsBlueprintBaseAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public IsBlueprintBaseAttribute()
    {
        this.MetaValue = "true";
    }
    }
}