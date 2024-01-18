using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class InlineEditConditionToggleAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public InlineEditConditionToggleAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public InlineEditConditionToggleAttribute()
    {
        this.MetaValue = "true";
    }
    }
}