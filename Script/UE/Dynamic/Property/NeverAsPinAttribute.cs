using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NeverAsPinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public NeverAsPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public NeverAsPinAttribute()
    {
        this.MetaValue = "true";
    }
    }
}