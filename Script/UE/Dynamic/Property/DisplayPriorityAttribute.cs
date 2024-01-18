using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayPriorityAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DisplayPriorityAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DisplayPriorityAttribute()
    {
        this.MetaValue = "true";
    }
    }
}