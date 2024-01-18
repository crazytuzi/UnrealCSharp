using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class CustomizePropertyAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public CustomizePropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public CustomizePropertyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}