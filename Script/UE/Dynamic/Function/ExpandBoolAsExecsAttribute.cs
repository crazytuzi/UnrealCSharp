using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ExpandBoolAsExecsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ExpandBoolAsExecsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ExpandBoolAsExecsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}