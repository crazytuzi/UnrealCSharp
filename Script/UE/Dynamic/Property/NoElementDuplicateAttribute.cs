using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoElementDuplicateAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public NoElementDuplicateAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public NoElementDuplicateAttribute()
    {
        this.MetaValue = "true";
    }
    }
}