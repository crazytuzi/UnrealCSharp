using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AlwaysAsPinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AlwaysAsPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AlwaysAsPinAttribute()
    {
        this.MetaValue = "true";
    }
    }
}