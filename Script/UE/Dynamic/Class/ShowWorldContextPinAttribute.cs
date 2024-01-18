using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ShowWorldContextPinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ShowWorldContextPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ShowWorldContextPinAttribute()
    {
        this.MetaValue = "true";
    }
    }
}