using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MultipleAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MultipleAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MultipleAttribute()
    {
        this.MetaValue = "true";
    }
    }
}