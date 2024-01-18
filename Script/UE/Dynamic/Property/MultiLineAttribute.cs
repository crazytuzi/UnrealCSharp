using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MultiLineAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MultiLineAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MultiLineAttribute()
    {
        this.MetaValue = "true";
    }
    }
}