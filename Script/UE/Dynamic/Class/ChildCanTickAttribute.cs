using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ChildCanTickAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public ChildCanTickAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ChildCanTickAttribute()
    {
        this.MetaValue = "true";
    }
    }
}