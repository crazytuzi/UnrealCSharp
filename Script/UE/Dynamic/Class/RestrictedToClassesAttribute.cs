using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class RestrictedToClassesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public RestrictedToClassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public RestrictedToClassesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}