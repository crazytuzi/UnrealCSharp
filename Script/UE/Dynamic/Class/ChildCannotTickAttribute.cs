using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ChildCannotTickAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ChildCannotTickAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ChildCannotTickAttribute()
    {
        this.MetaValue = "true";
    }
    }
}