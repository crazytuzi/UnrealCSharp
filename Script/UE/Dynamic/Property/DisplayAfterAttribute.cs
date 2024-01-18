using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayAfterAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DisplayAfterAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DisplayAfterAttribute()
    {
        this.MetaValue = "true";
    }
    }
}