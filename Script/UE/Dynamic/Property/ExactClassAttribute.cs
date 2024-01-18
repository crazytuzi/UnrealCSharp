using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExactClassAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ExactClassAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ExactClassAttribute()
    {
        this.MetaValue = "true";
    }
    }
}