using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ProhibitedInterfacesAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public ProhibitedInterfacesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ProhibitedInterfacesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}