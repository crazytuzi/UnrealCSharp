using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DeprecatedNodeAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DeprecatedNodeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DeprecatedNodeAttribute()
    {
        this.MetaValue = "true";
    }
    }
}