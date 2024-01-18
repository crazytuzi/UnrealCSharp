using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property)]
    public class LoadBehaviorAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public LoadBehaviorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public LoadBehaviorAttribute()
    {
        this.MetaValue = "true";
    }
    }
}